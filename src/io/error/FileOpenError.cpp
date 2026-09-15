/*
    FileOpenError.cpp

    Implementation of a file open error.
*/

#include "io/error/FileOpenError.hpp"
#include <format>

namespace toxico {
    FileOpenError::FileOpenError(const std::string& file_name, const std::string& reason)
        : std::runtime_error(std::format("Failed to open file '{}': {}", file_name, reason)) {}

    FileOpenError::FileOpenError(const std::string& file_name)
        : std::runtime_error(std::format("Failed to open file '{}'", file_name)) {}
}
