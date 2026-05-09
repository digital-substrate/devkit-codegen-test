#include "CLI11.hpp"
#include "Service_AttachmentFunctionPools.hpp"
#include "Service_Definitions.hpp"
#include "Service_FunctionPools.hpp"
#include "Viper_LoggerConsole.hpp"
#include "Viper_Service.hpp"
#include "Viper_ServiceServer.hpp"
#include "Viper_Socket.hpp"
#include "Viper_StringHelper.hpp"

#include <iostream>

int main(int argc, char * argv[]) {
    CLI::App app{"a server for a service."};
    argv = app.ensure_utf8(argv);

    bool verbose{};
    auto const o_verbose{app.add_flag("-v", verbose, "add the level of verbosity.")};

    std::string inetAddress{"0.0.0.0"};
    app.add_option("-a", inetAddress, "AF_INET address.");

    std::string inetPort{"54328"};
    app.add_option("-p", inetPort, "AF_INET port.");

    std::string socketPath{"/tmp/service.sock"};
    CLI::Option const * opt_socketPath{app.add_option("-s", socketPath, "AF_LOCAL socket path.")};

    CLI11_PARSE(app, argc, argv)
    Viper::Error::setProcessName(app.get_name());

    auto const service{
        Viper::Service::make(
            Service::definitions(),
            {
                Service::FunctionPools::tools(),
            },
            {
                Service::AttachmentFunctionPools::playerModel()
            })
    };

    std::shared_ptr<Viper::Logging> logging;
    std::uint8_t level{};
    if (o_verbose->count() == 1)
        level = Viper::Logging::Critical;
    else if (o_verbose->count() == 2)
        level = Viper::Logging::Info;
    else if (o_verbose->count() == 3) {
        level = Viper::Logging::Debug;
    }

    if (o_verbose->count())
        logging = Viper::LoggerConsole::make(level);

    try {
        std::shared_ptr<Viper::Socket> serverSocket;
        if (!opt_socketPath->empty()) {
            auto const u8SocketPath{Viper::StringHelper::u8Path(socketPath)};
            if (exists(u8SocketPath))
                std::filesystem::remove(u8SocketPath);
            serverSocket = Viper::Socket::makePassiveLocal(u8SocketPath);
        } else {
            serverSocket = Viper::Socket::makePassiveInet(inetAddress, inetPort);
        }

        Viper::ServiceServer::run(serverSocket, service, logging);

    } catch (const std::exception & e) {
        std::cout << "Server Startup Error: " << e.what() << '\n';
    }
}