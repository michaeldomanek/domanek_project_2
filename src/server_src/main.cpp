#include "bullet.h"
#include "window.h"
#include "robot.h"
#include "robotConfiguration.h"
#include "robotProperties.h"
#include "bulletConfiguration.h"
#include "base64.h"

#include "robotProperties.pb.h"
#include "grpcServer.h"

#include "asio.hpp"
#include "CLI11.hpp"
#include <SFML/Graphics.hpp>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/fmt/fmt.h"
#include "spdlog/fmt/bundled/color.h"

#include <vector>
#include <math.h>
#include <random>
#include <thread>


using namespace std;
using namespace asio;
using namespace asio::ip;

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    CLI::App app("Robotgame");

    unsigned int width{950};
    app.add_option("-w,--width", width, "width and height of the window", true)->check(CLI::Range(500, 1500));

    float bulletSpeed{6};
    app.add_option("--bullet-speed", bulletSpeed, "the speed of the bullets", true)->check(CLI::Range(1, 50));

    float bulletDamage{20};
    app.add_option("--bullet-damage", bulletDamage, "the damage of the bullets", true);

    unsigned int bulletSize{3};
    app.add_option("--bullet-size", bulletSize, "the size of the bullets in px", true)->check(CLI::Range(1, 10));

    float robotSpeed{2};
    app.add_option("--robot-speed", robotSpeed, "the speed of the robots", true)->check(CLI::Range(0.5f, 10.0f));

    float health{100};
    app.add_option("--health", health, "the health of the robots", true)->check(CLI::PositiveNumber);

    float robotRotation{1};
    app.add_option("--robot-rotation", robotRotation, "the robot roation speed of the robots", true)->check(CLI::Range(0.5f, 3.5f));

    float turretRotation{1.5};
    app.add_option("--turret-rotation", turretRotation, "the turret roation speed of the robots", true)->check(CLI::Range(0.5f, 5.0f));

    int minFireCountdown{500};
    app.add_option("-f,--fire-countdown", minFireCountdown, "the time after a robot can shoot again in ms", true)->check(CLI::PositiveNumber);

    unsigned int maxPlayers{4};
    app.add_option("-m,--max-players", maxPlayers, "the maximum players of the game", true)->check(CLI::Range(2, 4));

    unsigned short  port{1113};
    app.add_option("-p,--port", port, "port to connect to", true);

    bool canNotShootAndMove{};
    app.add_flag("-s,--not-shoot-and-move", canNotShootAndMove, "Robot can not shoot while it is moving");

    CLI11_PARSE(app, argc, argv);

    auto file_logger = spdlog::rotating_logger_mt("file_logger", "../logs/server.log", 1048576 * 5, 3);
    spdlog::set_default_logger(file_logger);
    spdlog::set_pattern("[%Y %m %d %H:%M:%S,%e] [%l] %v");
    spdlog::set_level(spdlog::level::debug);
    spdlog::flush_on(spdlog::level::debug);

    RobotConfiguration config{robotSpeed, health, robotRotation, turretRotation, minFireCountdown, canNotShootAndMove};
    BulletConfiguration bulletConfig{bulletSpeed, bulletDamage, bulletSize};

    vector<RobotProperties> properties;
    vector<tcp::iostream*> streams;

    for(unsigned int i = 0; i < maxPlayers; i++){
        try {
            io_context ctx;
            tcp::endpoint ep{tcp::v4(), port};
            tcp::acceptor acceptor{ctx, ep};
            
            acceptor.listen();
        
            tcp::iostream* strm{new tcp::iostream(acceptor.accept())};
            string data;
            *strm >> data;
            *strm << i << "\n";
            

            RobotPropertiesMessage rpmsg;
            rpmsg.ParseFromString(Base64::from_base64(data));

            streams.push_back(strm);

            RobotProperties property{rpmsg.name(), sf::Color(rpmsg.color())};
            properties.push_back(property);
            
            
        } catch (asio::system_error& e) {
            return 0;
        }
    }

    Window& window{Window::getInstance(width, maxPlayers, bulletConfig)};

    vector<Robot*> robots;

    for(RobotProperties property: properties) {
        Robot* robo = new Robot(property, config);
        robots.push_back(robo);
        window.addRobot(robo);
    }

    spdlog::info("Game started");
    fmt::print(fmt::fg(fmt::color::lime), "===========GAME STARTED!===========\n");

    Robot_RPC_Server service{robots};
    grpc::ServerBuilder builder;
    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    std::thread grpcServerThread{[&server]{
        server->Wait();
    }};
    grpcServerThread.detach();

    for(const auto strm: streams) {
        (*strm) << "start\n";
    }

    for (auto p : streams) {
        p->clear();
    } 
    streams.clear();

    while (window.isOpen()) {
        window.clear();

        for(Robot* robo: robots) {
            if (!robo->isDead()) {
                robo->performActions();
            }
        }

        window.moveAllBullets();
        window.bulletHit();

        window.handleEvent();
        window.draw();     
        window.display();
    }

    for (auto p : robots) {
        delete p;
    }

    google::protobuf::ShutdownProtobufLibrary();    
}
