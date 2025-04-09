cmake_minimum_required(VERSION 3.28)

# Project name
project(cttss LANGUAGES CXX)

# Set runtime output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include SFML using FetchContent
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
# Set minimum policy version for dependencies
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
FetchContent_MakeAvailable(SFML)

# Add executable
add_executable(cttss
    main.cpp
    game/game.cpp
    game/network.cpp
    layers/cell.cpp
    layers/layer.cpp
    input/playerInput.cpp
    entities/entities.cpp
    global/globals.cpp
    layers/lightMap.cpp
    ui/ui.cpp
    global/observer.cpp
    global/button.cpp
    Asio/server.cpp
    Asio/tsqueue.cpp
    Asio/connection.cpp
    Asio/client.cpp
)

# Set C++ standard
target_compile_features(cttss PRIVATE cxx_std_17)

# Link SFML libraries
target_link_libraries(cttss PRIVATE SFML::Graphics)