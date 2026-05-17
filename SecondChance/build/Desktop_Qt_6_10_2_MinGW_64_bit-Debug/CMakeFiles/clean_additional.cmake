# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SecondChance_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SecondChance_autogen.dir\\ParseCache.txt"
  "SecondChance_autogen"
  )
endif()
