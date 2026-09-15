/*
    FileWriteError.cpp

    Implementation of a file write error.
*/

#include "io/error/FileWriteError.hpp"
#include <format>

namespace toxico {
    FileWriteError::FileWriteError(const std::string& file_name, const std::string& reason)
        : std::runtime_error(std::format("Failed to open file '{}': {}", file_name, reason)) {}

    FileWriteError::FileWriteError(const std::string& file_name)
        : std::runtime_error(std::format("Failed to write to file '{}'", file_name)) {}
}
