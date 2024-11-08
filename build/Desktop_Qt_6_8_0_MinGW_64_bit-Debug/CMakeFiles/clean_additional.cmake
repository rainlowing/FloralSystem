# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FloralSystem_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FloralSystem_autogen.dir\\ParseCache.txt"
  "FloralSystem_autogen"
  )
endif()
