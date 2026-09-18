/*
    Quadratic.cpp

    Implementation of a quatratic function.
*/

#include "foundation/math/Quadratic.hpp"
#include <stdexcept>
#include <cmath>

namespace {
    toxico::fp_type signum(toxico::fp_type val) noexcept {
        return std::signbit(val) ? -1.0 : 1.0;
    }
}

namespace toxico {
    Quadratic::Quadratic(fp_type a, fp_type b, fp_type c) noexcept
        : a(a), b(b), c(c) {}

    fp_type Quadratic::operator()(fp_type x) const noexcept {
        return evaluate(x);
    }

    fp_type Quadratic::evaluate(fp_type x) const noexcept {
        return a * x * x + b * x + c;
    }

    fp_type Quadratic::discriminant() const noexcept {
        return b * b - 4 * a * c;
    }

    std::pair<std::complex<fp_type>, std::complex<fp_type>> Quadratic::roots() const {
        // Validate quadratic term
        if (a == fp_type{0.0})
            throw std::domain_error("Cannot calculate the roots of a non-quadratic");

        // Fetch discriminant
        const auto d = discriminant();

        // Repeated roots
        if (d == 0) {
            const std::complex<fp_type> root = -b / (fp_type{2} * a);
            return {root, root};
        }

        // Distinct real roots
        if (d >= 0) {
            const auto sqrt_d = std::sqrt(d);
            const auto q = fp_type{-0.5} * (b + signum(b) * sqrt_d);
            return {
                q / a,
                c / q
            };
        }

        // Distinct complex roots
        const auto sqrt_d = std::sqrt(std::complex<fp_type>{d});
        return {
            (-b + sqrt_d) / (fp_type{2} * a),
            (-b - sqrt_d) / (fp_type{2} * a)
        };
    }

    bool Quadratic::realRoots() const noexcept {
        return discriminant() >= 0 && a != fp_type{0.0};
    }

    bool Quadratic::distinctRoots() const noexcept {
        return discriminant() != 0 && a != fp_type{0.0};
    }
}
