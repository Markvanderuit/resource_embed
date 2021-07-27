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
# - target: execution target
# - rsrc: file path to resource file
function(rsrc_embed target rsrc)
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
  target_sources(${target} PRIVATE ${outputName})
endfunction()

# Function to embed list of resource files into target as strings
# args:
# - target: execution target
# - rsrc: list of file paths to resource files
function(rsrc_embed_multiple target rsrcs)
  foreach(rsrc ${rsrcs})
    rsrc_embed(${target} ${rsrc})
  endforeach()
endfunction()

# Function to embed all files in a specified directory into target as strings
# args:
# - target: execution target
# - dir: directory whose files are to be embedded
function(rsrc_embed_dir target dir)
  file(GLOB resources ${dir}/*.*)
  rsrc_embed_multiple(${target} "${resources}")
endfunction()