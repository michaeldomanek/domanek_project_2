#pragma once

#include "base64.h"
#include "robotProperties.h"
#include "robotInformation.h"
#include "robotConfiguration.h"

#include "grpcClient.h"
#include "robotProperties.pb.h"

#include "spdlog/fmt/fmt.h"
#include "spdlog/fmt/bundled/color.h"

#include "asio.hpp"
#include <SFML/Graphics.hpp>

#include <string>

using namespace std;
using namespace asio;
using namespace asio::ip;

namespace Game {
    int connectToGame(string port, RobotProperties prop, RobotConfiguration& config) {

        try {
            tcp::iostream strm{"localhost", port};

            if(strm) {
                RobotPropertiesMessage rpmsg;
                rpmsg.set_name(prop.getName());
                rpmsg.set_color(prop.getColor().toInteger());

                strm << Base64::to_base64(rpmsg.SerializeAsString()) << "\n";

                string data;
                getline(strm, data);

                int id{std::stoi(data)};

                getline(strm, data);

                RobotConfigurationMessage rcmsg;
                rcmsg.ParseFromString(Base64::from_base64(data));

                fmt::print("speed. {}\n", rcmsg.speed());

                config = {rcmsg.speed(), rcmsg.health(), rcmsg.robotrotation(), rcmsg.turretrotation(), 
                                            rcmsg.minfirecountdown(), rcmsg.canshootandmove()};

                strm.close();

                google::protobuf::ShutdownProtobufLibrary();

                return id;
            } else {
                fmt::print(fmt::fg(fmt::color::crimson), "Coutld not connect to server!\n");
            }
        } catch (exception& e) {
            fmt::print(fmt::fg(fmt::color::crimson), "Exception: {}\n", e.what());
        }
        return -1;
    }

    Robot_RPC_Client getRobot_RPC_Client(string port, int id) {
        return Robot_RPC_Client(grpc::CreateChannel("localhost:" + port, grpc::InsecureChannelCredentials()), id);
    }
}
