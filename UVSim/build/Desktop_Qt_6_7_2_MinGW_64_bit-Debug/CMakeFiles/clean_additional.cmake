# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\UVSim_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\UVSim_autogen.dir\\ParseCache.txt"
  "UVSim_autogen"
  )
endif()
