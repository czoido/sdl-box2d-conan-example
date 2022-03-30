import os

from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.files import copy


class MygameConan(ConanFile):
    name = "mygame"
    version = "0.1"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "assets/*"

    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("sdl/2.0.20")
        self.requires("sdl_image/2.0.5")
        self.requires("box2d/2.4.1")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "*/mygame*", self.build_folder, os.path.join(self.package_folder, "bin"), keep_path=False)
        copy(self, "assets/image.png", self.source_folder, os.path.join(self.package_folder, "bin"), keep_path=False)
