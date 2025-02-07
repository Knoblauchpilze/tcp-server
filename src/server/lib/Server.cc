

#include "Server.hh"
#include <TimeUtils.hh>

namespace echo {

Server::Server()
  : core::CoreObject("server")
{
  setService("server");
  initialize();
}

void Server::run(const int port)
{
  debug("Starting server...");
  setup(port);

  activeRunLoop();

  debug("Shutting down server...");
  shutdown();
}

void Server::requestStop()
{
  m_running.store(false);
  std::unique_lock lock(m_runningLocker);
  m_runningNotifier.notify_one();
}

void Server::initialize()
{
  /// TODO: Initialize the server.
}

void Server::setup(const int port)
{
  const net::ServerConfig config{.disconnectHandler =
                                   [this](const net::ConnectionId connectionId) {
                                     return onConnectionLost(connectionId);
                                   },
                                 .connectionReadyHandler =
                                   [this](net::ConnectionShPtr connection) {
                                     onConnectionReady(connection);
                                   }};

  m_tcpServer = std::make_shared<net::TcpServer>(m_context, port, config);
  m_tcpServer->start();

  info("Starting listening on port " + std::to_string(m_tcpServer->port()));
  m_context.start();
}

void Server::activeRunLoop()
{
  m_running.store(true);
  bool running{true};

  while (running)
  {
    std::unique_lock lock(m_runningLocker);
    m_runningNotifier.wait(lock, [this] { return !m_running.load(); });

    running = m_running.load();
  }
}

void Server::shutdown()
{
  m_context.stop();
}

void Server::onConnectionLost(const net::ConnectionId connectionId)
{
  if (!m_clientManager->isStillConnected(connectionId))
  {
    m_clientManager->removeConnection(connectionId);
    return;
  }

  const auto data = m_clientManager->tryGetDataForConnection(connectionId);

  if (data.stale)
  {
    debug("Connection " + std::to_string(connectionId) + " is already marked as stale");
    return;
  }

  info("Connection " + std::to_string(connectionId) + " lost, marking as stale");

  m_clientManager->markConnectionAsStale(connectionId);
}

void Server::onConnectionReady(net::ConnectionShPtr connection)
{
  const auto clientId = m_clientManager->registerConnection(connection);
  info("Registered client " + core::str(clientId));
}

} // namespace echo
