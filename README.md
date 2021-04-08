# domanek_project_2

## Aufgabenstellung

Netzwerk‐basiertes RobotGame wie robowiki mit zentralem Server.

## Spiel

Das Spiel ist eine abgeänderte Version von [robowiki](https://robowiki.net/wiki/Main_Page).

Die Ressourcen für das Spiel wurden von [robocode](https://github.com/robo-code/robocode) verwendet.

Das Spiel beginnt indem man den Game-Serevr startet:

`./robo-server`

Danach startet man in einem neuen Terminal jeweils einen weiteren Client.

1. `./rect-client`
2. `./random-client`
3. `./domanek`
4. `./domanekV2`

In dem CLient kann man dem Roboter folgende Befehle schicken  
- nach vorne fahren / nach hinten fahren / stoppen
- nach links drehen / nach rechts drehen / nicht mehr drehen
- Geschützturm nach links drehen / nach rechts drehen / nicht mehr drehen
- schießen / nicht mehr schießen
- man kann die eigene Position, Rotation und Geschützturmrotation erhalten
- man kann die ID, Name, Position, Rotation und Geschützturmrotation aller Gegnererhalten

Nachdem der Server gestartet wurde, können alle Clients beitreten.
Der Client legt seinen Namen und seine Farbe fest und schickt diese an den Server.
Sobald die maximale Anzahl der Spieler (-m,--max-players) erreicht wurde startet das Spiel.
Alle Clients bekommen ihre ID und die Roboter-Konfiguration.
Diese Konfiguration enhält die Geschwindigkeit, die Lebenspunkte, die Geschützturm- / Roboterrotationsgeschwindikeit, 
in welchem Abstand man schießen kann und ob man während dem Fahren schießen kann.
Das Spiel startet auch gleichzeitig und der RPC-Server wurde erstellt nun kann man die oben erwähten Befehle an den Server schicken.

Der Server startet nicht nur die grafische Oberfläche sondern zeigt auch im Terminal an, wenn Spielen beitreten und wenn Roboter sterben und am Ende wer gewonnen hat.

## einfaches Testen
Für den einfachsten Tests ob alles funktioniert benötigt man 3 Terminals in dem man jeweils einen dieser Befehle ausführt:

1. `./robo-server -m 2`
2. `./test-client`
3. `./test-client`

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

## verwendete Software
* [asio](https://think-async.com/Asio/)
* [CLI11](https://github.com/CLIUtils/CLI11)
* [fmt](https://github.com/fmtlib/fmt)
* [spdlog](https://github.com/gabime/spdlog)

* [protocol-buffers](https://developers.google.com/protocol-buffers/)
* [gRPC](http://www.grpc.io/)

* [sfml](https://github.com/SFML/SFML)
