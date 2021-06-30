from conans import ConanFile, CMake


class RequirementsConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "zlib/1.2.11@conan/stable", \
               "libiconv/1.16", \
               "boost/1.75.0", \
               "gtest/1.10.0", \
               "protobuf/3.15.5", \
               "libpq/13.2",
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.definitions["CMAKE_CXX_COMPILER"] = "/usr/bin/g++-10"
        if cmake.build_type == "Release":
            print("verbose: OFF")
            cmake.verbose = False
        else:
            print("verbose: ON")
            cmake.verbose = True
        pack = ""
        if cmake.build_type == "Release":
            pack = "package"
        cmake.configure()
        cmake.build(target=pack)
        cmake.test()
