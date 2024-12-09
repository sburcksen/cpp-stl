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

template <typename It1, typename It2>
bool equal(It1 first1, It1 end1, It2 first2)
{
    for (; first1 != end1; ++first1, ++first2) {
        if (*first1 != *first2) {
            return false;
        }
    }
    return true;
}
