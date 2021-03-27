#include "robotProperties.h"
#include "base64.h"

#include "robotProperties.pb.h"

#include "asio.hpp"
#include <SFML/Graphics.hpp>

#include <string>

using namespace std;
using namespace asio;
using namespace asio::ip;

class Connection {
    private:
    public:
        Connection(string port, RobotProperties prop) {

            tcp::iostream strm{"localhost", port};

            try {
                if (strm) {
                    RobotPropertiesMessage rpmsg;
                    rpmsg.set_name(prop.getName());
                    rpmsg.set_color(prop.getColor().toInteger());

                    strm << Base64::to_base64(rpmsg.SerializeAsString()) << endl;
                    strm.close();

                    google::protobuf::ShutdownProtobufLibrary();
                }
            } catch (asio::system_error& e) {
                // return 0;
            }
        }
};