#pragma once

template<class T>
class Iterator {
public:
    Iterator(T* ptr = nullptr) : pointer(ptr) {}
    Iterator(const T* ptr);
    Iterator<T>& operator++ ();
    Iterator<T> operator++ (int);
    Iterator<T>& operator-- ();
    Iterator<T> operator-- (int);
//    friend bool operator== (Iterator& lhs, Iterator& rhs) {return lhs == rhs;}
    friend bool operator!= (Iterator& lhs, Iterator& rhs) {return !(lhs.pointer == rhs.pointer);}
    T& operator* ();
    T& operator-> ();
private:
    T* pointer;
};

// overloaded operators definitions:
template<typename T>
Iterator<T>::Iterator(const T* ptr)
    :pointer(ptr) {}

template<typename T>
Iterator<T>& Iterator<T>::operator++ () {
    ++pointer;
    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator++(int) {
    auto temp{*this};
    (*this)++;
    return temp;
}

template<typename T>
Iterator<T>& Iterator<T>::operator-- () {
    --pointer;
    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator-- (int) {
    auto temp{*this};
    (*this)--;
    return temp;
}

template<typename T>
T& Iterator<T>::operator* () {
    return *pointer;
}

template<typename T>
T& Iterator<T>::operator-> () {
    return pointer;
}
