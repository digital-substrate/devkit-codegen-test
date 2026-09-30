// Copyright Digital Substrate 2021, All rights reserved

#include "Viper_CommitMutableState.hpp"
#include "Viper_CommitState.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_ServiceRemote.hpp"
#include "Viper_StringHelper.hpp"

#include "service_player_model_remote.hpp"
#include "service_tools_remote.hpp"
#include "Viper_ValueAny.hpp"
#include "Viper_ValueInt64.hpp"

#include "CLI11.hpp"

#include <iostream>

#include "service_demo_attachments.hpp"

using namespace service;

int main(int argc, char * argv[]) {
    CLI::App app{"the client for the service."};
    argv = app.ensure_utf8(argv);

    bool log{};
    app.add_flag("-l", log, "display a log.");

    std::string inetAddress{"127.0.0.1"};
    app.add_option("-a", inetAddress, "AF_INET address.");

    std::string inetPort{"54328"};
    app.add_option("-p", inetPort, "AF_INET port.");

    std::string socketPath{"/tmp/service.sock"};
    CLI::Option const * opt_socketPath = app.add_option("-s", socketPath, "AF_LOCAL socket path.");

    CLI11_PARSE(app, argc, argv)
    Viper::Error::setProcessName(app.get_name());

    try {
        auto const definitions{Viper::Definitions::make()};

        std::shared_ptr<Viper::ServiceRemote> service;
        if (!opt_socketPath->empty()) {
            auto const u8SocketPath{Viper::StringHelper::u8Path(socketPath)};
            service = Viper::ServiceRemote::connect(u8SocketPath, definitions);
        } else {
            service = Viper::ServiceRemote::connect(inetAddress, inetPort, definitions);
        }

        auto const tools{service::tools::Remote{service}};
        if (tools.isAvailable()) {
            auto const r{tools.add(32, 10)};
            std::cout << "add(32,10) -> " << r << '\n';

            service::demo::Vector3 const v1{1, 2, 3};
            service::demo::Vector3 const v2{10, 20, 30};
            auto const rv{tools.addVector(v1, v2)};
            std::cout << "addVector(v1,v2) -> (" << rv.x << "," << rv.y << "," << rv.z << ")" << '\n';

            Viper::Any const five{Viper::ValueAny::make(Viper::ValueInt64::make(5))};
            Viper::Any const three{Viper::ValueAny::make(Viper::ValueInt64::make(3))};
            std::cout << "isGreater(5,3) -> " << tools.isGreater(five, three) << '\n';
        }

        auto const playerModel{service::player_model::Remote{service}};
        if (playerModel.isAvailable()) {
            auto state{Viper::CommitState::make(Viper::CommitId::Invalid(), definitions, {})};
            auto mutableState{Viper::CommitMutableState::make(state)};
            std::string nickname{"the shadow man"};
            auto key{playerModel.create(mutableState, nickname, service::demo::Level::Beginner)};
            std::cout << "key is " << key.description() << '\n';

            if (auto const pk{playerModel.hasPlayer(mutableState, nickname)}) {
                if (auto const property{service::demo::attachments::Player::property::get(mutableState, *pk)}) {
                    std::cout << "nickname=" << property->nickname << ", level=" << static_cast<int>(property->level) << '\n';
                }
            }
        }

        service->close();

    } catch (std::exception const & e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}