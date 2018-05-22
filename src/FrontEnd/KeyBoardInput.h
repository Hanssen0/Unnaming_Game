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
#ifndef UNNAMING_GAME_SRC_FRONTEND_KEYBOARDINPUT_H_
#define UNNAMING_GAME_SRC_FRONTEND_KEYBOARDINPUT_H_
#include "../Interface/Input.h"
#include "../Interface/Object.h"
#include <cstdint>
#include <map>
#include <iostream>
class TerminalKeyBoardInput final : public Input {
 public:
  TerminalKeyBoardInput(Command& null_com) : null_command_(&null_com) {
  }
  virtual Command& HandleInput() override {
    char com;
    std::cin >> com;
    auto command_finder = command_for_key_.find(com);
    if (command_finder != command_for_key_.end()) {
      return *(command_finder -> second);
    }
    return *null_command_;
  }
  void set_command_for_key(const char& key, const Command& com) {
    command_for_key_[key] = const_cast< Command* >(&com);
  }
  
 private:
  std::map< char, Command* > command_for_key_;
  Command* null_command_;
};
#endif  // UNNAMING_GAME_SRC_FRONTEND_KEYBOARDINPUT_H_
