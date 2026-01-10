set(ROBOTIQ_FT_SOURCES
    robotiq_ft_sensor.c
    # Original Robotiq driver sources (see https://robotiq.com/support)
    vendor/rq_sensor_com.c
    vendor/rq_sensor_state.c
    vendor/Thread/rq_thread.c
    vendor/Thread/mutex.c
)

add_library(robotiq_ft_sensor SHARED ${ROBOTIQ_FT_SOURCES})

target_include_directories(robotiq_ft_sensor
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)

target_link_libraries(robotiq_ft_sensor
  PRIVATE
    pthread
)

target_compile_options(robotiq_ft_sensor
  PRIVATE
    -Wall -Wextra
)

install(
  TARGETS robotiq_ft_sensor
  EXPORT ${PROJECT_NAME}-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)