/*
    FileWriteError.hpp

    Declaration of a file write error.
*/

#pragma once

#include <stdexcept>
#include <string>

namespace toxico {
    class FileWriteError : public std::runtime_error {
    public:
        /**
         * @brief Constructor.
         * 
         * @param file_name The name of the file this error is for.
         * @param reason An additional reason as to why the file couldn't be opened.
         */
        FileWriteError(const std::string& file_name, const std::string& reason);

        /**
         * @brief Constructor.
         * 
         * @param file_name The name of the file this error is for.
         */
        FileWriteError(const std::string& file_name);
    };
}
