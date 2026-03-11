# CMakeList.txt : CMake project for RayTracing, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (RayTracing "RayTracing.cpp" "RayTracing.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracing PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
