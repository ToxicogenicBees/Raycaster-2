/*
    OwningVector.tpp

    Template implementation of a vector holding polymorphic objects.
*/

#include <utility>

namespace toxico {
    template<typename Base>
    template<std::derived_from<Base> T>
    void OwningVector<Base>::push_back(std::unique_ptr<T> item) {
        data_.push_back(std::move(item));
    }

    template<typename Base>
    template<std::derived_from<Base> T>
    void OwningVector<Base>::push_back(const T& item) {
        data_.push_back(std::make_unique<T>(item));
    }

    template<typename Base>
    template<std::derived_from<Base> T, typename... Args>
    T& OwningVector<Base>::emplace_back(Args&& ...args) {
        data_.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        return getBackAs<T>();
    }

    template<typename Base>
    template<std::derived_from<Base> T>
    OwningVector<Base>::iterator OwningVector<Base>::insert(const_iterator pos, std::unique_ptr<T> value) {
        return data_.insert(pos.get(), std::move(value));
    }
    
    template<typename Base>
    template<std::derived_from<Base> T>
    OwningVector<Base>::iterator OwningVector<Base>::insert(const_iterator pos, const T& value) {
        return data_.insert(pos.get(), std::make_unique<T>(value));
    }

    template<typename Base>
    OwningVector<Base>::iterator OwningVector<Base>::erase(const_iterator pos) {
        return data_.erase(pos.get());
    }

    template<typename Base>
    OwningVector<Base>::iterator OwningVector<Base>::erase(const_iterator first, const_iterator last) {
        return data_.erase(first.get(), last.get());
    }

    template<typename Base>
    void OwningVector<Base>::pop_back() noexcept {
        data_.pop_back();
    }

    template<typename Base>
    template<std::derived_from<Base> T>
    const T& OwningVector<Base>::getAs(std::size_t index) const {
        return static_cast<const T&>(at(index));
    }

    template<typename Base>
    template<std::derived_from<Base> T>
    T& OwningVector<Base>::getAs(std::size_t index) {
        return static_cast<T&>(at(index));
    }

    template<typename Base>
    const Base& OwningVector<Base>::at(std::size_t index) const {
        return *data_.at(index).get();
    }

    template<typename Base>
    Base& OwningVector<Base>::at(std::size_t index) {
        return *data_.at(index).get();
    }

    template<typename Base>
    const Base& OwningVector<Base>::operator[](std::size_t index) const {
        return *data_[index].get();
    }

    template<typename Base>
    Base& OwningVector<Base>::operator[](std::size_t index) {
        return *data_[index].get();
    }

    template<typename Base>
    template<std::derived_from<Base> T>
    const T& OwningVector<Base>::getFrontAs() const {
        return static_cast<const T&>(front());
    }

    template<typename Base>
    template<std::derived_from<Base> T>
    T& OwningVector<Base>::getFrontAs() {
        return static_cast<T&>(front());
    }

    template<typename Base>
    const Base& OwningVector<Base>::front() const {
        return *data_.front().get();
    }

    template<typename Base>
    Base& OwningVector<Base>::front() {
        return *data_.front().get();
    }

    template<typename Base>
    template<std::derived_from<Base> T>
    const T& OwningVector<Base>::getBackAs() const {
        return static_cast<const T&>(back());
    }
    
    template<typename Base>
    template<std::derived_from<Base> T>
    T& OwningVector<Base>::getBackAs() {
        return static_cast<T&>(back());
    }
    
    template<typename Base>
    const Base& OwningVector<Base>::back() const {
        return *data_.back().get();
    }
    
    template<typename Base>
    Base& OwningVector<Base>::back() {
        return *data_.back().get();
    }
    
    template<typename Base>
    void OwningVector<Base>::resize(std::size_t size) {
        data_.resize(size);
    }

    template<typename Base>
    void OwningVector<Base>::reserve(std::size_t size) {
        data_.reserve(size);
    }

    template<typename Base>
    bool OwningVector<Base>::empty() const noexcept {
        return data_.empty();
    }

    template<typename Base>
    std::size_t OwningVector<Base>::capacity() const noexcept {
        return data_.capacity();
    }

    template<typename Base>
    std::size_t OwningVector<Base>::size() const noexcept {
        return data_.size();
    }

    template<typename Base>
    void OwningVector<Base>::clear() {
        data_.clear();
    }

    template<typename Base>
    OwningVector<Base>::const_iterator OwningVector<Base>::cbegin() const noexcept {
        return data_.cbegin();
    }

    template<typename Base>
    OwningVector<Base>::const_iterator OwningVector<Base>::begin() const noexcept {
        return data_.begin();
    }

    template<typename Base>
    OwningVector<Base>::iterator OwningVector<Base>::begin() noexcept {
        return data_.begin();
    }

    template<typename Base>
    OwningVector<Base>::const_iterator OwningVector<Base>::cend() const noexcept {
        return data_.cend();
    }

    template<typename Base>
    OwningVector<Base>::const_iterator OwningVector<Base>::end() const noexcept {
        return data_.end();
    }

    template<typename Base>
    OwningVector<Base>::iterator OwningVector<Base>::end() noexcept {
        return data_.end();
    }
}
