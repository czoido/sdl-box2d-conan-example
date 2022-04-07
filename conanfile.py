import os

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.apple import XcodeDeps, XcodeToolchain
from conan.tools.files import copy


class MygameConan(ConanFile):
    name = "mygame"
    version = "0.1"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "assets/*"

    options = {"xcode_ide": [True, False]}
    default_options = {"xcode_ide": False}

    def generate(self):
        if not self.options.xcode_ide:
            tc = CMakeToolchain(self)
            tc.generate()        
            deps = CMakeDeps(self)
            deps.generate()
        else:
            tc = XcodeToolchain(self)
            tc.generate()        
            deps = XcodeDeps(self)
            deps.generate()

    def requirements(self):
        self.requires("sdl/2.0.20")
        self.requires("sdl_image/2.0.5")
        self.requires("box2d/2.4.1")
        self.requires("cli11/2.1.2")
        self.requires("fmt/8.1.1")
        self.requires("tinkerforge-bindings/2.1.32")

    def layout(self):
        if not self.options.xcode_ide:
            cmake_layout(self)
        else:
            self.folders.build = "build"
            self.folders.generators = "conan"

    def build(self):
        if not self.options.xcode_ide:
            cmake = CMake(self)
            cmake.configure()
            cmake.build()

    def package(self):
        if not self.options.xcode_ide:
            copy(self, "mygame*", self.build_folder, os.path.join(self.package_folder, "bin"), keep_path=False)
            copy(self, "assets/frog.png", self.source_folder, os.path.join(self.package_folder, "bin"), keep_path=False)
