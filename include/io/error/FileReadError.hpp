/*
    FileReadError.hpp

    Declaration of a file read error.
*/

#pragma once

#include <stdexcept>
#include <string>

namespace toxico {
    class FileReadError : public std::runtime_error {
    public:
        /**
         * @brief Constructor.
         * 
         * @param file_name The name of the file this error is for.
         * @param reason An additional reason as to why the file couldn't be opened.
         */
        FileReadError(const std::string& file_name, const std::string& reason);

        /**
         * @brief Constructor.
         * 
         * @param file_name The name of the file this error is for.
         */
        FileReadError(const std::string& file_name);
    };
}
