

#ifndef utils_h
#define utils_h
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <fstream>
#include <memory>
#include "enums.h"
#include "TextureManager.h"
#if TARGET_OS_MAC
#include <cmath>
#include <string>
#include "ResourcePath.hpp"
inline void eraseSubStr(std::string & mainStr, const std::string & toErase)
{
    // Search for the substring in string
    size_t pos = mainStr.find(toErase);
    
    if (pos != std::string::npos)
    {
        // If found then erase it from string
        mainStr.erase(pos, toErase.length());
    }
}
#endif
#endif /* utils_h */
