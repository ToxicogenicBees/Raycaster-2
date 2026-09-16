/*
    Image.tpp

    Template implementation of an image object.
*/

namespace toxico {
    template<std::input_iterator InputIter>
    Image::Image(InputIter begin, InputIter end, Size size)
        : pixels_(begin, end, size, GridOrder::RowMajor) {}
}
