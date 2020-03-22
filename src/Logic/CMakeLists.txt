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
# TODO(handsome0hell): Update Logic library to shareable library.
cmake_minimum_required(VERSION 3.0)
project(Logic_library CXX)
cmake_policy(SET CMP0063 NEW) # Enable hidden visibility for static library
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
aux_source_directory(. DIR_LIB_LOGIC)
add_library(Logic ${DIR_LIB_LOGIC})
