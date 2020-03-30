# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
cmake_minimum_required(VERSION 3.0)
project(Map_library CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(GenerateExportHeader)
include(../../CMake/compiler.cmake)
include(../../CMake/libraries.cmake)
add_library(Map SHARED Map.cc Space.cc
            Block/Block.cc Block/BaseBlock.cc
            Building/Building.cc Building/BaseBuilding.cc
            Building/LinkBuilding.cc)
target_link_libraries(Map Logic)
generate_export_header(Map)
