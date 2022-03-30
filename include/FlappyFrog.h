#include <string>

#include <Box2D/Box2D.h>
#include "ip_connection.h"
#include "bricklet_rgb_led_button.h"

struct Connection {
    std::string host;
    int port;
    std::string uid;
};

class FlappyFrog {
    private:
        Connection connection;
        const int SCREEN_WIDTH{640};
        const int SCREEN_HEIGHT{480};
        const int PIX2METR{32};

        b2World* world;
        b2Body* body;

        const b2Vec2& FlappyFrog::screen2world(const b2Vec2&);
        const b2Vec2& FlappyFrog::world2screen(const b2Vec2&);

        IPConnection ipcon;
        RGBLEDButton rlb;
    public:
        FlappyFrog(const Connection);
        int connect();
        int loop();
        ~FlappyFrog();
};
