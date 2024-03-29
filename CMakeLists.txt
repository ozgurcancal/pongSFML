cmake_minimum_required(VERSION 3.0)
project(pong)

set(CMAKE_CXX_STANDARD 20)

if (BUILD_STATIC)
    set(SFML_STATIC_LIBRARIES TRUE)
endif()

# Copy assets directory to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
find_package( SFML 2.5.1 REQUIRED COMPONENTS graphics)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
else()
    set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
    message("\nSFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
    message("Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

include_directories(${PROJECT_SOURCE_DIR}/src/gameObjects)
include_directories(${PROJECT_SOURCE_DIR}/src/commands)
include_directories(${PROJECT_SOURCE_DIR}/src/screens)
include_directories(${PROJECT_SOURCE_DIR}/src/enums)

set(HEADERS ${HEADERS}
	${PROJECT_SOURCE_DIR}/src/commands/command.h
    ${PROJECT_SOURCE_DIR}/src/commands/moveDown.h
    ${PROJECT_SOURCE_DIR}/src/commands/moveUp.h
    ${PROJECT_SOURCE_DIR}/src/commands/moveBall.h
    ${PROJECT_SOURCE_DIR}/src/commands/setSpeed.h
    ${PROJECT_SOURCE_DIR}/src/commands/commandHandler.h
    ${PROJECT_SOURCE_DIR}/src/commands/setDifficulty.h

    ${PROJECT_SOURCE_DIR}/src/gameObjects/gameObjectFactory.h
    ${PROJECT_SOURCE_DIR}/src/gameObjects/paddle.h
    ${PROJECT_SOURCE_DIR}/src/gameObjects/ball.h

    ${PROJECT_SOURCE_DIR}/src/enums/commandType.h
    ${PROJECT_SOURCE_DIR}/src/enums/paddleEnums.h
    ${PROJECT_SOURCE_DIR}/src/enums/gameMode.h

    ${PROJECT_SOURCE_DIR}/src/screens/screen.h
    ${PROJECT_SOURCE_DIR}/src/screens/gameScreen.h
    ${PROJECT_SOURCE_DIR}/src/screens/singlePlayerScreen.h
    ${PROJECT_SOURCE_DIR}/src/screens/multiPlayerScreen.h
    ${PROJECT_SOURCE_DIR}/src/screens/menuScreen.h
    ${PROJECT_SOURCE_DIR}/src/screens/screenManager.h
    ${PROJECT_SOURCE_DIR}/src/screens/optionsScreen.h
    ${PROJECT_SOURCE_DIR}/src/screens/gameOverScreen.h

    ${PROJECT_SOURCE_DIR}/src/gameEngine.h
    ${PROJECT_SOURCE_DIR}/src/inputController.h

)

set(SOURCES ${SOURCES}
    ${PROJECT_SOURCE_DIR}/src/commands/moveDown.cpp
    ${PROJECT_SOURCE_DIR}/src/commands/moveUp.cpp
    ${PROJECT_SOURCE_DIR}/src/commands/moveBall.cpp
    ${PROJECT_SOURCE_DIR}/src/commands/setSpeed.cpp
    ${PROJECT_SOURCE_DIR}/src/commands/commandHandler.cpp
    ${PROJECT_SOURCE_DIR}/src/commands/setDifficulty.cpp

    ${PROJECT_SOURCE_DIR}/src/gameObjects/gameObjectFactory.cpp
    ${PROJECT_SOURCE_DIR}/src/gameObjects/paddle.cpp
    ${PROJECT_SOURCE_DIR}/src/gameObjects/ball.cpp

    ${PROJECT_SOURCE_DIR}/src/screens/gameScreen.cpp
    ${PROJECT_SOURCE_DIR}/src/screens/singlePlayerScreen.cpp
    ${PROJECT_SOURCE_DIR}/src/screens/multiPlayerScreen.cpp
    ${PROJECT_SOURCE_DIR}/src/screens/menuScreen.cpp
    ${PROJECT_SOURCE_DIR}/src/screens/screenManager.cpp
    ${PROJECT_SOURCE_DIR}/src/screens/optionsScreen.cpp
    ${PROJECT_SOURCE_DIR}/src/screens/gameOverScreen.cpp

    ${PROJECT_SOURCE_DIR}/src/gameEngine.cpp
    ${PROJECT_SOURCE_DIR}/src/inputController.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

add_executable(pong ${HEADERS} ${SOURCES})

target_link_libraries(pong PUBLIC sfml-graphics)
