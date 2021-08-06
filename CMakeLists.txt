cmake_minimum_required(VERSION 3.21)

# Define project leveraging ony C++
project(ResourceEmbed LANGUAGES CXX)

# Specify interface library to provide header file
add_library(ResourceEmbed INTERFACE)
target_include_directories(ResourceEmbed INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Function to recursively embed all resource files in a specified directory
# into a target. The files are embedded as strings into an unordered map, using
# their file paths (relative to the top resource directory) as keys. See
# resource_embed.hpp for usage.
# 
# @param target - execusion target
# @param dir - directory whose resources are embedded
function(rsrcs_embed output_var dir)
  message(STATUS "Collecting resources from ${dir}")

  # Set output variable to resources output file
  set(output ${CMAKE_BINARY_DIR}/resources/resources.cpp)
  set(${output_var} ${output} PARENT_SCOPE)

  # Create empty resources output file
  file(WRITE ${output} "")

  # Append includes, unordered map and namespace to resources output file
  file(APPEND ${output} "#include <string>\n#include <unordered_map>\n")
  file(APPEND ${output} "namespace rsrc {\n")
  file(APPEND ${output} "const extern std::unordered_map<std::string,std::string> __RSRC_MAP__;\n")
  file(APPEND ${output} "const std::unordered_map<std::string,std::string> __RSRC_MAP__ = {\n")

  # Collect resource files recursively
  file(GLOB_RECURSE rsrcs ${dir}/*)

  # Iterate through collected resource files
  foreach(rsrc ${rsrcs})
    # Get relative filepath as identifying name
    cmake_path(RELATIVE_PATH rsrc BASE_DIRECTORY ${dir} OUTPUT_VARIABLE rsrcName)
    message(STATUS "\t${rsrcName}")

    # Read data from resource file as text
    file(READ ${rsrc} rsrcData)

    # Append data to resources output file as a raw string literal
    file(APPEND ${output} "{\n\"${rsrcName}\",")
    file(APPEND ${output} "\nR\"RSRCDELIM(\n")
    file(APPEND ${output} "${rsrcData}")
    file(APPEND ${output} "\n)RSRCDELIM\"\n},\n")
  endforeach()

  # Append end of map, namespace to resources output file
  file(APPEND ${output} "};\n}")
  message(STATUS "Collected resources to ${output}")
endfunction()