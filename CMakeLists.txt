cmake_minimum_required(VERSION 3.8)
project(ariel)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
# find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
# find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

include_directories(include/ariel)


set(SOURCES
  src/tanking_control_demo.cpp
  include/ariel/TankingController.cpp
)

add_executable(ariel ${SOURCES})
ament_target_dependencies(ariel rclcpp std_msgs sensor_msgs)

install(TARGETS ariel
  DESTINATION lib/${PROJECT_NAME})

ament_package()
