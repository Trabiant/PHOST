# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\PHOST_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PHOST_autogen.dir\\ParseCache.txt"
  "PHOST_autogen"
  "_deps\\spdlog-build\\CMakeFiles\\spdlog_autogen.dir\\AutogenUsed.txt"
  "_deps\\spdlog-build\\CMakeFiles\\spdlog_autogen.dir\\ParseCache.txt"
  "_deps\\spdlog-build\\spdlog_autogen"
  "_deps\\spdlog-build\\tests\\CMakeFiles\\spdlog-utests_autogen.dir\\AutogenUsed.txt"
  "_deps\\spdlog-build\\tests\\CMakeFiles\\spdlog-utests_autogen.dir\\ParseCache.txt"
  "_deps\\spdlog-build\\tests\\spdlog-utests_autogen"
  )
endif()
