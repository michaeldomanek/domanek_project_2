# domanek_project_2

## Aufgabenstellung

Netzwerk‐basiertes RobotGame wie robowiki mit zentralem Server.

## Spiel

Das Spiel ist eine abgeänderte Version von [robowiki](https://robowiki.net/wiki/Main_Page).

Die Ressourcen für das Spiel wurden von [robocode](https://github.com/robo-code/robocode) verwendet.

## Verwendung

Usage: ./robo-server [OPTIONS]

| Option                   | Typ [Bereich]=Standartwert    | Beschreibung                                 |
| ------------------------ | ----------------------------- | -------------------------------------------- |
| -h,--help                | FLAG                          | Print this help message and exit             |
| -w,--width               | UINT:INT in [500 - 1500]=950  | width and height of the window               |
| --bullet-speed           | FLOAT:INT in [1 - 50]=6       | the speed of the bullets                     |
| --bullet-damage          | FLOAT=20                      | the damage of the bullets                    |
| --bullet-size            | UINT:INT in [1 - 10]=3        | the size of the bullets in pixel             |
| --robot-speed            | FLOAT:FLOAT in [0.5 - 10]=2   | the speed of the robots                      |
| --health                 | FLOAT:POSITIVE=100            | the health of the robots                     |
| --robot-rotation         | FLOAT:FLOAT in [0.5 - 3.5]=1  | the roation speed of the robots              |
| --turret-rotation        | FLOAT:FLOAT in [0.5 - 5]=1.5  | the turret roation speed of the robots       |
| -f,--fire-countdown      | INT:POSITIVE=500              | the time after a robot can shoot again in ms |
| -m,--max-players         | UINT:INT in [2 - 4]=4         | the maximum players of the game              |
| -p,--port                | UINT=1113                     | port to connect to                           |
| -s,--not-shoot-and-move  | FLAG                          | Robot can not shoot while it is moving       |
| -j,--json-config         | TEXT:FILE                     | JSON Configuration for port, max-player, ... |

## verwendete Software
* [asio](https://think-async.com/Asio/)
* [CLI11](https://github.com/CLIUtils/CLI11)
* [fmt](https://github.com/fmtlib/fmt)
* [json](https://github.com/nlohmann/json)
* [spdlog](https://github.com/gabime/spdlog)

* [protocol-buffers](https://developers.google.com/protocol-buffers/)
* [gRPC](http://www.grpc.io/)

* [sfml](https://github.com/SFML/SFML)
