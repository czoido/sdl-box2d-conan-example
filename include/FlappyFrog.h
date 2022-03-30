#include <string>

#include <Box2D/Box2D.h>
#include "ip_connection.h"
#include "bricklet_rgb_led_button.h"

class Connection {
    public:
        std::string host;
        int port;
        std::string uid;

        Connection() = default;
        ~Connection() = default;

        operator bool() const {
            return !host.empty() && !uid.empty();
        };
};

class FlappyFrog {
    private:
        Connection connection;
        const int SCREEN_WIDTH{640};
        const int SCREEN_HEIGHT{480};
        const int PIX2METR{32};

        b2World* world;
        b2Body* body;

        const b2Vec2& screen2world(const b2Vec2&);
        const b2Vec2& world2screen(const b2Vec2&);

        IPConnection ipcon;
        RGBLEDButton rlb;
    public:
        FlappyFrog(const Connection);
        FlappyFrog();
        int connect();
        int loop();
        ~FlappyFrog();

        FlappyFrog(const FlappyFrog&) = default;
        FlappyFrog& operator=(const FlappyFrog&) = default;
};
