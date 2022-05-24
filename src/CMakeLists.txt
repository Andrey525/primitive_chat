add_executable(Client Client/Main.cpp Client/Login.cpp Client/ChatRoom.cpp Client/NetworkInteraction.cpp)
set_compile_options(Client)
target_include_directories(Client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Client PRIVATE sfml-graphics sfml-window sfml-network sfml-system sfml-audio tgui)

add_executable(Server Server/Main.cpp Server/Server.cpp)
set_compile_options(Server)
target_include_directories(Server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Server PRIVATE sfml-graphics sfml-window sfml-network sfml-system tgui)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


