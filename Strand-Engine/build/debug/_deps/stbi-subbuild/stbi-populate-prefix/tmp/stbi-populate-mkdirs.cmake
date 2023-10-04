# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Strand-Engine/engine/build/debug/_deps/stbi-src"
  "D:/Strand-Engine/engine/build/debug/_deps/stbi-build"
  "D:/Strand-Engine/engine/build/debug/_deps/stbi-subbuild/stbi-populate-prefix"
  "D:/Strand-Engine/engine/build/debug/_deps/stbi-subbuild/stbi-populate-prefix/tmp"
  "D:/Strand-Engine/engine/build/debug/_deps/stbi-subbuild/stbi-populate-prefix/src/stbi-populate-stamp"
  "D:/Strand-Engine/engine/build/debug/_deps/stbi-subbuild/stbi-populate-prefix/src"
  "D:/Strand-Engine/engine/build/debug/_deps/stbi-subbuild/stbi-populate-prefix/src/stbi-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Strand-Engine/engine/build/debug/_deps/stbi-subbuild/stbi-populate-prefix/src/stbi-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Strand-Engine/engine/build/debug/_deps/stbi-subbuild/stbi-populate-prefix/src/stbi-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
