cmake_minimum_required(VERSION 2.8.3)
project(cat_tabletag_detection)


find_package(PCL REQUIRED)
find_package(catkin REQUIRED COMPONENTS
roscpp
cat_common
apriltags
tf
geometry_msgs
std_msgs
message_generation
)
find_package(Boost REQUIRED system filesystem date_time thread)

add_service_files(FILES GetTagPose.srv)

generate_messages(DEPENDENCIES std_msgs)

include_directories(
        include
        ${catkin_INCLUDE_DIRS} 
        ${PCL_INCLUDE_DIRS}
        )
link_directories(${PCL_LIBRARY_DIRS})

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES cat_tabletag_detection
  CATKIN_DEPENDS message_runtime
)
 
## Declare a C++ executable
add_executable(cat_tabletag_detection src/tabletag_detection.cpp src/ApriltagsClass.cpp)
target_link_libraries(cat_tabletag_detection
   ${catkin_LIBRARIES} ${PCL_INCLUDE_DIRS})

add_executable(tpose_srv src/gettagpose_service.cpp src/ApriltagsClass.cpp)
target_link_libraries(tpose_srv ${catkin_LIBRARIES})
add_dependencies(tpose_srv cat_tabletag_detection_gencpp)
