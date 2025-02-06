
#include "Server.hh"
#include <CoreException.hh>
#include <functional>
#include <log/Locator.hh>
#include <log/PrefixedLogger.hh>
#include <log/StdLogger.hh>

namespace {
// https://stackoverflow.com/questions/11468414/using-auto-and-lambda-to-handle-signal
std::function<void(int)> sigIntProcessing;

void sigIntInterceptor(const int signal)
{
  sigIntProcessing(signal);
}
} // namespace

int main(int /*argc*/, char ** /*argv*/)
{
  core::log::StdLogger raw;
  raw.setLevel(core::log::Severity::DEBUG);
  core::log::PrefixedLogger logger("server", "main");
  core::log::Locator::provide(&raw);

  try
  {
    bsgo::Server server;
    sigIntProcessing = [&server](const int /*signal*/) { server.requestStop(); };
    // https://en.cppreference.com/w/cpp/utility/program/signal
    std::signal(SIGINT, sigIntInterceptor);

    constexpr auto DEFAULT_SERVER_PORT = 60000;
    server.run(DEFAULT_SERVER_PORT);
  }
  catch (const core::CoreException &e)
  {
    logger.error("Caught internal exception while setting up application", e.what());
    return EXIT_FAILURE;
  }
  catch (const std::exception &e)
  {
    logger.error("Caught internal exception while setting up application", e.what());
    return EXIT_FAILURE;
  }
  catch (...)
  {
    logger.error("Unexpected error while setting up application");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
