cmake_minimum_required(VERSION 3.8)
project(sol_pc8)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

set(msg_files
  "msg/Distances.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
)

add_executable(sensor_simulator src/sensor_simulator.cpp)
ament_target_dependencies(sensor_simulator rclcpp std_msgs)


set(ament_dependencies
  rclcpp
  std_msgs
  geometry_msgs
)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp)

target_link_libraries(sensor_simulator "${cpp_typesupport_target}")

ament_export_dependencies(rosidl_default_runtime)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

install(TARGETS
 sensor_simulator
DESTINATION lib/${PROJECT_NAME})

ament_package()