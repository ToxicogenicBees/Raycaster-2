/*
    Grid.hpp

    Declaration of a 2D container of data.
*/

#pragma once

#include "foundation/geometry/Size.hpp"
#include <cstdint>
#include <iterator>
#include <vector>

namespace toxico {
    enum class GridOrder {
        ColumnMajor,
        RowMajor
    };

    template<typename T>
    class Grid {
    private:
        std::vector<T> data_;
        Size size_;
        GridOrder order_;

    public:
        using const_iterator = std::vector<T>::const_iterator;
        using iterator = std::vector<T>::iterator;

        /**
         * @brief Constructor.
         *        Throws an invalid-arguments exception if the data and size don't match.
         * 
         * @param begin The beginning of a list of data.
         * @param end The end of a list of data.
         * @param size The size of the data.
         * @param order The grid order (default is row-major)
         */
        template<std::input_iterator InputIter>
        Grid(InputIter begin, InputIter end, Size size, GridOrder order = GridOrder::RowMajor);

        /**
         * @brief Constructor.
         * 
         * @param size The size of the grid.
         * @param initial The initial value for each entry in the grid.
         * @param order The grid order (default is row-major)
         */
        Grid(Size size, T initial, GridOrder order = GridOrder::RowMajor) noexcept;

        /**
         * @brief Constructor.
         * 
         * @param size The size of the grid.
         * @param order The grid order (default is row-major)
         */
        Grid(Size size, GridOrder order = GridOrder::RowMajor) noexcept;

        /**
         * @brief Constructlr.
         * 
         * @param order The grid order (default is row-major)
         */
        Grid(GridOrder order = GridOrder::RowMajor) noexcept;

        /**
         * @brief Linearly indexes the grid.
         * 
         * @param index The linear tile index.
         * @return The desired value.
         */
        const T& operator[](std::size_t index) const;
        T& operator[](std::size_t index);

        /**
         * @brief Linearly indexes the grid.
         *        Throws an out-of-range exception if the index is invalid.
         * 
         * @param index The linear tile index.
         * @return The desired value.
         */
        const T& at(std::size_t index) const;
        T& at(std::size_t index);

        /**
         * @brief Positionally indexes the grid.
         * 
         * @param x The desired x-position.
         * @param y The desired y-position.
         * @return The desired value.
         */
        const T& operator()(std::size_t x, std::size_t y) const;
        T& operator()(std::size_t x, std::size_t y);

        /**
         * @brief Positionally indexes the grid.
         *        Throws an out-of-range exception if the position is invalid.
         * 
         * @param x The desired x-position.
         * @param y The desired y-position.
         * @return The desired value.
         */
        const T& at(std::size_t x, std::size_t y) const;
        T& at(std::size_t x, std::size_t y);

        /**
         * @brief Fills the grid with the desired value.
         * 
         * @param value The desired value.
         */
        void fill(const T& value) noexcept;

        /**
         * @brief Resizes the grid, not preserving data formatting.
         * 
         * @param size The new size of the grid.
         */
        void resize(Size size) noexcept;

        /**
         * @brief Gets the size of the grid.
         * 
         * @return The size of the grid.
         */
        Size size() const noexcept;

        /**
         * @brief Gets the order of the grid.
         * 
         * @return The order of the grid.
         */
        GridOrder order() const noexcept;

        /**
         * @brief Gets the desired iterator for this grid's data.
         * 
         * @return The desired iterator.
         */
        const_iterator cbegin() const noexcept;
        const_iterator begin() const noexcept;
        iterator begin() noexcept;
        const_iterator cend() const noexcept;
        const_iterator end() const noexcept;
        iterator end() noexcept;
    };
}

#include "foundation/containers/Grid.tpp"
