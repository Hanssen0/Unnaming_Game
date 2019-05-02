//    Copyright (C) 2018  Handsome0hell
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//    Email: handsome0hell@gmail.com
#ifndef UNNAMING_GAME_SRC_FRONTEND_CININPUT_H_
#define UNNAMING_GAME_SRC_FRONTEND_CININPUT_H_
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
class CinInput;
typedef std::shared_ptr< CinInput > CinInput_ref;
class CinInput {
 public:
  ~CinInput();
  void HandleInput();
  void BindKey(const char& key, const std::function< void() > function);
  static CinInput_ref CreateCinInput(const std::function< void() >);
 private:
  CinInput() = delete;
  CinInput& operator=(const CinInput&) = delete;
  CinInput(const std::function< void() >);
  std::map< char, std::function< void() > > function_for_key_;
  const std::function< void() > null_function_;
};
#endif  // UNNAMING_GAME_SRC_FRONTEND_CININPUT_H_
