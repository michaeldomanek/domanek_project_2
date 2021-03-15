#include "robotProperties.h"

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
                    strm << prop.getName() << endl;
                    strm.close();
                }
            } catch (asio::system_error& e) {
                // return 0;
            }
        }
};