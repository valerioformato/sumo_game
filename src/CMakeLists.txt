find_package(fmt CONFIG)
find_package(spdlog CONFIG)
find_package(docopt CONFIG)

set(GAME_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_subdirectory(ecs)
add_subdirectory(engine)
add_subdirectory(game)

# Generic test that uses conan libs
add_executable(intro ${GAME_SOURCES})
target_link_libraries(
  intro
  PRIVATE project_options
          project_warnings
          docopt::docopt
          fmt::fmt
          spdlog::spdlog)

target_link_system_libraries(
  intro
  PRIVATE
  ftxui::screen
  ftxui::dom
  ftxui::component)

target_include_directories(intro PRIVATE "${CMAKE_SOURCE_DIR}/src" "${CMAKE_BINARY_DIR}/configured_files/include")
