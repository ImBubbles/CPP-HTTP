//
// Created by bubbles on 8/16/25.
//

#include "UtilString.h"

#include "../../logger/Log.h"

std::string UtilString::removeFirst(std::string regex, std::string pattern) {
    Log::debug("Removing regex from string");
    int index = pattern.find_first_of(regex);
    if (index == std::string::npos)
        return pattern;
    Log::debug("Valid index");
    std::string result = pattern.substr(0, index);
    result += pattern.substr(index+regex.size(), pattern.size());
    return result;
}