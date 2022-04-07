Simple SDL, SDLImage, Box2d example with Conan
==============================================

Example using SDL, SDLImage, Box2d to create a simple game.

- Install Conan (preferably in a virtual environment)
- Create the application and run the test_package

```bash
pip install conan
conan create . --build=missing --build=mygame
```

Using Xcode IDE
---------------


```bash
conan install . -s build_type=Release --build=missing -o mygame:xcode_ide=True
conan install . -s build_type=Debug --build=missing -o mygame:xcode_ide=True
```

Add xcconfig files generated in conan folder to the Xcode project. Check instructions [here](https://blog.conan.io/2022/03/17/New-conan-release-1-46.html).

Select `conan_config.xcconfig` as config for both configurations.

Build the project in Xcode
