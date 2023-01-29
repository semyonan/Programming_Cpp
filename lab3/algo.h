template <class InputIterator, class UnaryPredicate>
bool all_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
    while (first != last) {
        if (!pred(*first)) {
            return false;
        }
        ++first;
    }
    return true;
}

template <class InputIterator, class UnaryPredicate>
bool any_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            return true;
        }
        ++first;
    }
    return false;
}

template <class InputIterator, class UnaryPredicate>
bool none_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
    return !any_of(first, last, pred);
}

template <class InputIterator, class UnaryPredicate>
bool one_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
    int flag = 0;
    while ((first != last) && (flag < 2)) {
        if (pred(*first)) { 
            flag++;
        }
        ++first;
    }
    return flag == 1;
}

template <class BiDirIterator, class UnaryPredicate>
bool is_sorted(BiDirIterator first, BiDirIterator last, UnaryPredicate pred) {
    while (first != std::prev(last)) {
        if (!pred(*first, *(std::next(first, 1)))) {
            return false;
        }
        ++first;
    }
    return true;
}

template <class BiDirIterator, class UnaryPredicate>
bool is_partitioned(BiDirIterator first, BiDirIterator last, UnaryPredicate pred) {
    int flag = 0;
    bool prev, cur;
    if (first != last) {
        prev = pred(*first);
        cur = pred(*(++first));
    }
    
    while ((first != last) && (flag < 2)) {
        if (cur != prev) {
            flag++;
        }
        prev = cur;
        ++first;
    }

    return flag < 2;
}

template<class InputIterator, class Type>
InputIterator find_not(InputIterator first, InputIterator last, const Type& elem) {
    while (first != last){
        if (*first != elem) {
            return first;
        };
        ++first;
    }
    return last;
}

template<class BiDirIterator, class Type>
BiDirIterator find_backwards(BiDirIterator first, BiDirIterator last, const Type& elem) {
    BiDirIterator l = last;

    while (last != first){
        --last;
        if (*last == elem) {
            return last;
        }
    }

    return l;
}

template <class BiDirIterator, class UnaryPredicate>
bool is_palindrome(BiDirIterator first, BiDirIterator last, UnaryPredicate pred) {

    while (first != last) {
        --last;
        if (!pred(*first, *last)) {
            return false;
        }
        if (first == last) {break;}
        ++first;
    }
    return true;
}
