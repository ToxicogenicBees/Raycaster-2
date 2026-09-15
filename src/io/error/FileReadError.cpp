/*
    FileReadError.cpp

    Implementation of a file read error.
*/

#include "io/error/FileReadError.hpp"
#include <format>

namespace toxico {
    FileReadError::FileReadError(const std::string& file_name, const std::string& reason)
        : std::runtime_error(std::format("Failed to open file '{}': {}", file_name, reason)) {}

    FileReadError::FileReadError(const std::string& file_name)
        : std::runtime_error(std::format("Failed to read file '{}'", file_name)) {}
}
