# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

if(EXISTS "D:/Strand-Engine/engine/build/debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-gitclone-lastrun.txt" AND EXISTS "D:/Strand-Engine/engine/build/debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-gitinfo.txt" AND
  "D:/Strand-Engine/engine/build/debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-gitclone-lastrun.txt" IS_NEWER_THAN "D:/Strand-Engine/engine/build/debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'D:/Strand-Engine/engine/build/debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-gitclone-lastrun.txt'"
  )
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "D:/Strand-Engine/engine/build/debug/_deps/glfw-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'D:/Strand-Engine/engine/build/debug/_deps/glfw-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" 
            clone --no-checkout --config "advice.detachedHead=false" "https://github.com/glfw/glfw" "glfw-src"
    WORKING_DIRECTORY "D:/Strand-Engine/engine/build/debug/_deps"
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/glfw/glfw'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe" 
          checkout "master" --
  WORKING_DIRECTORY "D:/Strand-Engine/engine/build/debug/_deps/glfw-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'master'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "D:/Strand-Engine/engine/build/debug/_deps/glfw-src"
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'D:/Strand-Engine/engine/build/debug/_deps/glfw-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "D:/Strand-Engine/engine/build/debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-gitinfo.txt" "D:/Strand-Engine/engine/build/debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'D:/Strand-Engine/engine/build/debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-gitclone-lastrun.txt'")
endif()
