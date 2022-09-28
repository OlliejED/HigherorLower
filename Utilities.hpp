//
//  Utilities.hpp
//  HigherorLower
//
//  Created by Oliver ED on 27/09/2022.
//

#pragma once

#include <string>
#include <fstream>
#include <iostream>

std::string string_to_lower(std::string lower_me);
void to_log_file(std::string severity);
std::string converter(int card);


std::string LOG_FILE = "error.log";
