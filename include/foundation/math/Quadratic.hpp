/*
    Quadratic.hpp

    Declaration of a quatratic function.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include <utility>
#include <complex>

namespace toxico {
    struct Quadratic {
        // ax^2 + bx + c
        fp_type a = 0.0;
        fp_type b = 0.0;
        fp_type c = 0.0;

        /**
         * @brief Constructor.
         * 
         * @param a The quadratic term.
         * @param b The linear term.
         * @param c The constant term.
         */
        Quadratic(fp_type a, fp_type b, fp_type c) noexcept;

        /**
         * @brief Constructor.
         */
        Quadratic() noexcept = default;

        /**
         * @brief Evaluates the quadratic for a given value.
         * 
         * @param x The desired position to evaluate the quadratic.
         * @return The value at the desired coordinate.
         */
        fp_type operator()(fp_type x) const noexcept;
        fp_type evaluate(fp_type x) const noexcept;

        /**
         * @brief Gets the discriminant of the quadratic.
         * 
         * @return The discriminant of the quadratic.
         */
        fp_type discriminant() const noexcept;

        /**
         * @brief Gets the roots of the quadratic.
         * 
         * @return The pair of roots for this quadratic.
         * 
         * Throws an exception if the quadratic term is zero.
         */
        std::pair<std::complex<fp_type>, std::complex<fp_type>> roots() const;

        /**
         * @brief Gets if the roots of the quadratic are real.
         * 
         * @return If the roots of the quadratic are real.
         */
        bool realRoots() const noexcept;

        /**
         * @brief Gets if the roots of the quadratic are distinct.
         * 
         * @return If the roots of the quadratic are distinct.
         */
        bool distinctRoots() const noexcept;
    };
}
