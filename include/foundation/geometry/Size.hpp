/*
    Size.hpp

    Declaration for the Size class
*/

#pragma once

#include <ostream>
#include <cstdint>

namespace toxico {
    struct Size {
        std::size_t width;
        std::size_t height;

        /**
         * @brief Constructor
         * 
         * @param width The horizontal size
         * @param height The vertical size
         */
        Size(std::size_t width = 0, std::size_t height = 0);
        
        /**
         * @brief Gets the area of a rectangle of this size
         * 
         * @return The area of a rectangle of this size
         */
        std::size_t area() const;

        /***
         * @brief Overloaded multiplication operator
         * 
         * @param s A multiplier value
         * @param size A size object
         * 
         * @return The scaled size
         */
        template<typename Scalar>
        friend Size operator*(const Scalar& s, Size size);

        /***
         * @brief Overloaded multiplication operator
         * 
         * @param s A multiplier value
         * 
         * @return The scaled size
         */
        template<typename Scalar>
        Size operator*(const Scalar& s) const;

        /***
         * @brief Overloaded chained multiplication + assignment operator
         * 
         * @param s A multiplier value
         * @return A reference to this size object
         */
        template<typename Scalar>
        Size& operator*=(const Scalar& s);

        /***
         * @brief Overloaded division operator
         * 
         * @param s A multiplier value
         * @param size A size object
         * 
         * @return The scaled size
         */
        template<typename Scalar>
        friend Size operator/(const Scalar& s, Size size);

        /***
         * @brief Overloaded division operator
         * 
         * @param s A multiplier value
         * 
         * @return The scaled size
         */
        template<typename Scalar>
        Size operator/(const Scalar& s) const;
        
        /***
         * @brief Overloaded chained division + assignment operator
         * 
         * @param s A multiplier value
         * @return A reference to this size object
         */
        template<typename Scalar>
        Size& operator/=(const Scalar& s);

        /**
         * @brief Compare two size object.
         * 
         * @result If the two sizes are equal.
         */
        bool operator==(Size size) const;
    };

    /***
     * @brief Overloaded insertion operator
     * 
     * @param o A reference to an output stream
     * @param size The size being output to the stream
     * 
     * @result A reference to the output stream being output to
     */
    std::ostream& operator<<(std::ostream& o, Size size);
}

#include "foundation/geometry/Size.tpp"
