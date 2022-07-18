project(logic)

file(GLOB server_SRC CONFIGURE_DEPENDS
  main.cpp
  "include/*"
  "src/*"
)

add_executable(${PROJECT_NAME} ${server_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-audio sfml-network sfml-graphics sfml-window sfml-system PRIVATE common)


