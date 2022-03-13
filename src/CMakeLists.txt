add_executable(Client Client/Client.cpp Client/LoginWindow.cpp Client/NetworkInteraction.cpp Client/ClientWindow.cpp)
set_compile_options(Client)
target_include_directories(Client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Client)
target_link_libraries(Client PRIVATE sfml-graphics sfml-window sfml-network sfml-system sfml-audio tgui)

add_executable(Server Server/Server.cpp)
set_compile_options(Server)
target_include_directories(Server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Server)
target_link_libraries(Server PRIVATE sfml-network tgui)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


