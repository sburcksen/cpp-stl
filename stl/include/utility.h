using sizeType = unsigned int;
using differenceType = unsigned int;

template <typename Iterator, typename T>
Iterator fillWithElement(Iterator first, sizeType count, const T& element)
{
    for (; count > 0; --count, ++first) {
        *first = element;
    }

    return first;
}
