# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Sort_app_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Sort_app_autogen.dir\\ParseCache.txt"
  "Sort_app_autogen"
  )
endif()
