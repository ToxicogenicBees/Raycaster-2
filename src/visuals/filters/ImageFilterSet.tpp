/*
    ImageFilterSet.tpp

    Template implementation of an ordered set of image filters.
*/

namespace toxico {
    template<typename Filter, typename... Args>
    requires std::is_base_of_v<IImageFilter, Filter>
    void ImageFilterSet::add(Args&& ...args) {
        filters_.push_back(std::make_unique<Filter>(std::forward<Args>(args)...));
    }
}
