#include "../header/Exceptions.h"

fileNotFound::fileNotFound(const std::string &file_path)
    : gameException("Specified file does not exist or is not a valid file name: " + file_path) {}

fontError::fontError(const std::string &font_path)
    : gameException("Font has not loaded succesfully: " + font_path) {}

textureError::textureError(const std::string &texture_path)
    : gameException("Failed to load texture: " + texture_path) {}

divideByZero::divideByZero(const myVec &vec)
    : gameException("Vec2 normalize() called with zero length: " + vec.myVec_to_string()) {}
