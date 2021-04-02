#include "robotClient.h"

using namespace std;

int main() {
    string port{"1113"};
    string name{"testname"};
    string grpcPort{"50051"};

    RobotProperties properties{name, sf::Color::Blue};

    int id = Game::connectToGame(port, properties);

    if(id >= 0) {
        fmt::print("Game stated! Robot id: {}\n", id);

        Robot_RPC_Client robotClient = Game::getRobot_RPC_Client(grpcPort, id);

        robotClient.moveForward();
        sleep(2);

        while(true) {
            robotClient.moveForward();
            sleep(1);
            robotClient.moveBackward();
            sleep(1);
            robotClient.stopMove();
            sleep(1);
            robotClient.rotateLeft();
            sleep(1);
            robotClient.rotateRight();
            sleep(1);
            robotClient.stopRotate();
            sleep(1);
            robotClient.rotateWeaponLeft();
            sleep(1);
            robotClient.rotateWeaponRight();
            sleep(1);
            robotClient.stopRotateWeapon();
            sleep(1);
            robotClient.startShooting();
            sleep(1);
            robotClient.stopShooting();
            sleep(1);

            sf::Vector2f pos{robotClient.getPosition()};
            fmt::print("x: {} | y: {}\n", pos.x, pos.y);

            float rotation{robotClient.getRotation()};
            fmt::print("rotation: {}\n", rotation);

            float weaponRotation{robotClient.getTurretRotation()};
            fmt::print("weapon rotation: {}\n", weaponRotation);

            for (auto orientation : robotClient.getEnemiesRobotInformations()) {
                fmt::print("id: {} | name: {} | x: {} | y: {} | rotation: {} | weapon rotation: {}\n", 
                    orientation.getID(), orientation.getName(),
                    orientation.getPosition().x, orientation.getPosition().y, 
                    orientation.getRotation(), orientation.getTurretRotation()
                );
            }

            sleep(1);
        }
    }
    google::protobuf::ShutdownProtobufLibrary();
}