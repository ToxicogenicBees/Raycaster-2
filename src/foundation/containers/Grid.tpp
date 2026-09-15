/*
    Grid.tpp

    Template implementation of a 2D container of data.
*/

#include <algorithm>

namespace {
    using namespace toxico;

    std::size_t linIndex(std::size_t x, std::size_t y, Size size, GridOrder order) {
        if (order == GridOrder::ColumnMajor)
            return y + (x * size.height);
        else
            return x + (y * size.width);
    }
}

namespace toxico {
    template<typename T>
    template<std::input_iterator InputIter>
    Grid<T>::Grid(InputIter begin, InputIter end, Size size, GridOrder order)
        : data_(begin, end),
          size_(size),
          order_(order)
    {
        if (data_.size() != size.area())
            throw std::invalid_argument("Provided data doesn't match grid size");
    }

    template<typename T>
    Grid<T>::Grid(Size size, T initial, GridOrder order) noexcept
        : data_(size.area(), initial),
          size_(size),
          order_(order)
    {}

    template<typename T>
    Grid<T>::Grid(Size size, GridOrder order) noexcept
        : data_(size.area()),
          size_(size),
          order_(order)
    {}

    template<typename T>
    Grid<T>::Grid(GridOrder order) noexcept
        : order_(order) {}

    template<typename T>
    const T& Grid<T>::operator[](std::size_t index) const {
        return data_[index];
    }

    template<typename T>
    T& Grid<T>::operator[](std::size_t index) {
        return data_[index];
    }

    template<typename T>
    const T& Grid<T>::at(std::size_t index) const {
        if (index >= data_.size())
            throw std::out_of_range("Accessed grid out of bounds");

        return data_[index];
    }

    template<typename T>
    T& Grid<T>::at(std::size_t index) {
        if (index >= data_.size())
            throw std::out_of_range("Accessed grid out of bounds");

        return data_[index];
    }

    template<typename T>
    const T& Grid<T>::operator()(std::size_t x, std::size_t y) const {
        auto index = linIndex(x, y, size_, order_);
        return data_[index];
    }

    template<typename T>
    T& Grid<T>::operator()(std::size_t x, std::size_t y) {
        auto index = linIndex(x, y, size_, order_);
        return data_[index];
    }

    template<typename T>
    const T& Grid<T>::at(std::size_t x, std::size_t y) const {
        if (x >= size_.width || y >= size_.height)
            throw std::out_of_range("Accessed grid out of bounds");

        auto index = linIndex(x, y, size_, order_);
        return data_[index];
    }

    template<typename T>
    T& Grid<T>::at(std::size_t x, std::size_t y) {
        if (x >= size_.width || y >= size_.height)
            throw std::out_of_range("Accessed grid out of bounds");

        auto index = linIndex(x, y, size_, order_);
        return data_[index];
    }

    template<typename T>
    void Grid<T>::fill(const T& value) noexcept {
        for (auto& item : data_)
            item = value;
    }

    template<typename T>
    void Grid<T>::resize(Size size) noexcept {
        data_.resize(size.area());
        size_ = size;
    }

    template<typename T>
    Size Grid<T>::size() const noexcept {
        return size_;
    }

    template<typename T>
    GridOrder Grid<T>::order() const noexcept {
        return order_;
    }

    template<typename T>
    Grid<T>::const_iterator Grid<T>::cbegin() const noexcept {
        return data_.begin();
    }

    template<typename T>
    Grid<T>::const_iterator Grid<T>::begin() const noexcept {
        return data_.begin();
    }

    template<typename T>
    Grid<T>::iterator Grid<T>::begin() noexcept {
        return data_.begin();
    }

    template<typename T>
    Grid<T>::const_iterator Grid<T>::cend() const noexcept {
        return data_.cend();
    }

    template<typename T>
    Grid<T>::const_iterator Grid<T>::end() const noexcept {
        return data_.end();
    }

    template<typename T>
    Grid<T>::iterator Grid<T>::end() noexcept {
        return data_.end();
    }
}
