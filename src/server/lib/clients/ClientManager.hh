
#pragma once

#include "Connection.hh"
#include "Uuid.hh"
#include <CoreObject.hh>
#include <memory>
#include <mutex>
#include <optional>
#include <unordered_map>

namespace bsgo {

class ClientManager : public core::CoreObject
{
  public:
  ClientManager();
  ~ClientManager() override = default;

  auto registerConnection(const net::ConnectionShPtr connection) -> Uuid;
  void markConnectionAsStale(const net::ConnectionId connectionId);
  void removeConnection(const net::ConnectionId connectionId);

  /// @brief - Try to retrieve the connection linked to the input client. It can
  /// fail to find one in case the connection is marked as stale in which case we
  /// don't return it as sending data would fail anyway.
  /// @param clientId - the client id for which the connection should be retrieved.
  /// @return - the connection associated to the client if it is not stale.
  auto tryGetConnectionForClient(const Uuid clientId) const -> std::optional<net::ConnectionShPtr>;

  auto getAllConnections() const -> std::vector<net::ConnectionShPtr>;

  struct ConnectionData
  {
    Uuid clientId{};
    bool stale{false};
  };
  auto tryGetDataForConnection(const net::ConnectionId connectionId) -> ConnectionData;
  bool isStillConnected(const net::ConnectionId connectionId) const;

  private:
  static Uuid NEXT_CLIENT_ID;

  struct ClientData
  {
    Uuid clientId{};
    net::ConnectionShPtr connection{};
    bool connectionIsStale{false};
  };

  mutable std::mutex m_locker{};
  std::unordered_map<Uuid, ClientData> m_clients{};
  std::unordered_map<net::ConnectionId, Uuid> m_connectionToClient{};

  auto tryGetClientDataForConnection(const net::ConnectionId connectionId) const
    -> std::optional<ClientData>;
};

using ClientManagerShPtr = std::shared_ptr<ClientManager>;

} // namespace bsgo
