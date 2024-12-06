#pragma once

#include <stdexcept>
#include <string>

class gameException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class fileNotFound : public gameException {
public:
    explicit fileNotFound(const std::string& file_path);
};

class fontError : public gameException {
public:
    explicit fontError(const std::string& font_path);
};

class textureError : public gameException {
public:
    explicit textureError(const std::string& texture_path);
};