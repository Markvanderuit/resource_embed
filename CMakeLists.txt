cmake_minimum_required(VERSION 3.16)

project(StringEmbed LANGUAGES CXX)

# Add interface library to include header file
add_library(LibStringEmbed INTERFACE)
target_include_directories(LibStringEmbed INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add executable to perform string embeds
add_executable(ExecStringEmbed ${CMAKE_CURRENT_SOURCE_DIR}/src/string_embed.cpp)
target_compile_features(ExecStringEmbed PUBLIC cxx_std_17)

# Function to embed a single resource file into a target as a string
# args:
# - rsrc: file path to resource file
# - target: execution target
function(string_embed rsrc target)
  # Define input and output file names
  get_filename_component(inputName ${rsrc} NAME_WE)
  set(outputName ${CMAKE_BINARY_DIR}/resources/${inputName}.cpp)

  # Specify command to generate file with the resource embedded as string inside
  # Calls the ExecStringEmbed executable defined above
  add_custom_command(
    OUTPUT ${outputName}
    COMMAND ExecStringEmbed ${inputName} ${rsrc} ${outputName}
    DEPENDS ${rsrc}
  )

  # Append file to list of target's sources
  target_sources(${target} PRIVATE ${embedding})
endfunction()

# Function to embed list of resource files into target as strings
# args:
# - rsrc: list of file paths to resource files
# - target: execution target
function(embed_resources rsrcs target)
  foreach(rsrc ${rsrcs})
    string_embed(${rsrc} ${target})
  endforeach()
endfunction()

# Function to embed all files in a specified directory into target as strings
# args:
# - dir: directory whose files are to be embedded
# - target: execution target
function(embed_resource_dir dir target)
  file(GLOB resources ${dir}/*.*)
  embed_resources("${resources}" ${target})
endfunction()