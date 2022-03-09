add_executable(main src/main.cpp)
set_compile_options(main)
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-network sfml-system)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
