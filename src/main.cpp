#include "FlappyFrog.h"

#include <CLI/CLI.hpp>
#include "fmt/core.h"

#define VERSION "0.0.0"


int main(int argc, char* argv[])
{
    CLI::App app{"Simple SDL, SDLImage, Box2d example with Conan"};
    app.set_version_flag("-v,--version", std::string(VERSION));

    std::string host = "localhost";
    app.add_option("-j,--host", host, "Host address");
    int port = 4223;
    app.add_option("-p,--port", port, "Port address");
    std::string uid = "XYZ";
    app.add_option("uid", uid, "Device UID");

    CLI11_PARSE(app, argc, argv);
    std::cout << fmt::format("Connecting to device '{uid}' at {host}:{port}",
                             fmt::arg("uid", uid), fmt::arg("host", host), fmt::arg("port", port))
                             << std::endl;
    Connection connection{host, port, uid};
    FlappyFrog game{connection};
    game.connect();
    game.loop();
    return 0;
}
