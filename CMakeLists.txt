# CMakeList.txt : CMake project for agent_simulation, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("agent_simulation")

find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
	include_directories(${SDL2_INCLUDE_DIRS})
else()
	message(STATUS "SDL2 NOT found !")
endif(SDL2_FOUND)

include_directories(include)

# Add source to this project's executable.
# If the OS is Windows use WIN32 to disable a console window being displayed.
if(WIN32)
	add_executable (agent_simulation WIN32 "src/agent_simulation.cpp" "include/agent_simulation.h" "include/simulation.h" "src/simulation.cpp" "include/wall.h" "src/wall.cpp" "include/resource.h" "src/resource.cpp" "include/agent.h" "src/agent.cpp" "include/helper.h" "src/helper.cpp")
else()
	add_executable (agent_simulation "src/agent_simulation.cpp" "include/agent_simulation.h" "include/simulation.h" "src/simulation.cpp" "include/wall.h" "src/wall.cpp" "include/resource.h" "src/resource.cpp")
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET agent_simulation PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

target_link_libraries(agent_simulation ${SDL2_LIBRARIES})
