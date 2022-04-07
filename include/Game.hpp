#include <string>
#include <memory>
#include <box2d/box2d.h>
#include <ip_connection.h>
#include <bricklet_rgb_led_button.h>

#include "Frog.hpp"
#include "World.hpp"

class Connection {

public:

    Connection() = default;
    ~Connection() = default;

    std::string host;
    int port;
    std::string uid;


    operator bool() const {
        return !host.empty() && !uid.empty();
    };

};

class Game {

public:

    Game() = default;
    ~Game();

    void addConnection(const Connection);
    int connect();
    int loop();

    static const int SCREEN_WIDTH{640};
    static const int SCREEN_HEIGHT{480};
    static const int PIX2METR{32};
    static const b2Vec2& screen2world(const b2Vec2&);
    static const b2Vec2& world2screen(const b2Vec2&);

    const b2Vec2 initFrogPos{5.0,10.0};

private:
    World world{};
    std::unique_ptr<Frog> frog{std::make_unique<Frog>(initFrogPos, world)};

    Connection connection;
    IPConnection ipcon;
    RGBLEDButton rlb;

};
