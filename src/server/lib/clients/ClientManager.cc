
#include "ClientManager.hh"

namespace echo {
core::Uuid ClientManager::NEXT_CLIENT_ID{0};

ClientManager::ClientManager()
  : core::CoreObject("manager")
{
  setService("client");
}

auto ClientManager::registerConnection(const net::ConnectionShPtr connection) -> core::Uuid
{
  const std::lock_guard guard(m_locker);

  const ClientData data{.clientId = NEXT_CLIENT_ID, .connection = connection};
  m_clients.emplace(data.clientId, data);
  m_connectionToClient.emplace(connection->id(), data.clientId);

  ++NEXT_CLIENT_ID;

  info("Registered connection " + data.connection->str());

  return data.clientId;
}

void ClientManager::markConnectionAsStale(const core::Uuid connectionId)
{
  const std::lock_guard guard(m_locker);

  const auto maybeClientId = m_connectionToClient.find(connectionId);
  if (maybeClientId == m_connectionToClient.cend())
  {
    error("Failed to mark connection " + std::to_string(connectionId) + " as stale");
  }

  auto &clientData = m_clients.at(maybeClientId->second);
  if (clientData.connectionIsStale)
  {
    error("Failed to mark connection " + core::str(connectionId) + " for disconnection",
          "Client " + core::str(clientData.clientId) + " is already marked as stale");
  }

  clientData.connectionIsStale = true;
}

void ClientManager::removeConnection(const net::ConnectionId connectionId)
{
  const std::lock_guard guard(m_locker);

  const auto maybeClientId = m_connectionToClient.find(connectionId);
  if (maybeClientId == m_connectionToClient.cend())
  {
    error("Failed to unregister connection " + std::to_string(connectionId));
  }

  const auto clientData = m_clients.at(maybeClientId->second);

  m_connectionToClient.erase(connectionId);
  m_clients.erase(clientData.clientId);

  info("Removed connection " + clientData.connection->str());
}

auto ClientManager::tryGetConnectionForClient(const core::Uuid clientId) const
  -> std::optional<net::ConnectionShPtr>
{
  const std::lock_guard guard(m_locker);

  const auto maybeClientData = m_clients.find(clientId);
  if (maybeClientData == m_clients.cend())
  {
    error("Failed to get connection for " + core::str(clientId), "No such client");
  }

  if (maybeClientData->second.connectionIsStale)
  {
    return {};
  }

  return maybeClientData->second.connection;
}

auto ClientManager::getAllConnections() const -> std::vector<net::ConnectionShPtr>
{
  const std::lock_guard guard(m_locker);
  std::vector<net::ConnectionShPtr> out;

  for (const auto &[_, clientData] : m_clients)
  {
    if (!clientData.connectionIsStale)
    {
      out.push_back(clientData.connection);
    }
  }

  return out;
}

auto ClientManager::tryGetDataForConnection(const net::ConnectionId connectionId) -> ConnectionData
{
  ConnectionData out{};

  const auto maybeClientData = tryGetClientDataForConnection(connectionId);
  if (!maybeClientData)
  {
    return out;
  }

  out.clientId = maybeClientData->clientId;
  out.stale    = maybeClientData->connectionIsStale;
  return out;
}

bool ClientManager::isStillConnected(const net::ConnectionId connectionId) const
{
  const auto maybeClientData = tryGetClientDataForConnection(connectionId);
  return maybeClientData.has_value();
}

auto ClientManager::tryGetClientDataForConnection(const net::ConnectionId connectionId) const
  -> std::optional<ClientData>
{
  const std::lock_guard guard(m_locker);

  const auto maybeClientId = m_connectionToClient.find(connectionId);
  if (maybeClientId == m_connectionToClient.cend())
  {
    return {};
  }

  const auto maybeClientData = m_clients.find(maybeClientId->second);
  if (maybeClientData == m_clients.cend())
  {
    error("Failed to get client data for " + std::to_string(connectionId), "No such client");
  }

  return maybeClientData->second;
}

} // namespace echo
