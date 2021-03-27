#include "connection.h"

#include "CLI11.hpp"
// todo: remvoe cli11 from client

using namespace std;

int main(int argc, char* argv[]) {
    CLI::App app("Robotgame client");

    string port{"1113"};
    app.add_option("-p,--port", port, "port to connect to");

    string name{};
    app.add_option("-n,--name", name, "ingame name")->required();
    
    CLI11_PARSE(app, argc, argv);

    RobotProperties properties{name, sf::Color::Blue};

    Connection c{port, properties};

}