#pragma once

#include <cassert>
#include <iostream>
#include <algorithm>
#include "Iterator.hpp"

template<class T>
class m_vector {
public:
    m_vector() : m_length(0), m_capacity(0), m_data(nullptr) {}

    m_vector(m_vector const& m): m_length(m.m_length), m_capacity(m.m_capacity), m_data(new T[m.m_capacity]) {}

    m_vector(int length)
        : m_length(length) {
        assert(length >= 0);
        m_capacity = length;

        if (length > 0) {
            m_data = new T[length];
        }
        else
            m_data = nullptr;
    }

    void erase() {
        delete[] m_data;

        m_data = nullptr;
        m_length = 0;
        m_capacity = 0;
    }

    T& operator[](int index) {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    void reServe(unsigned int newCapacity) {
        // if the length of an array is equall to planed length - return
        if (newCapacity == m_capacity)
            return;

        // if empty array is needed - do it and return
        if (newCapacity <= 0) {
            erase();
            return;
        }

        // allocating a new array
        T* data = new T[newCapacity];

        // copying elements from a lesser array to a greater
        if (m_capacity > 0) {
            int elementsToCopy = (newCapacity > m_capacity) ? m_capacity : newCapacity;

            for (int index = 0; index < elementsToCopy; ++index)
                data[index] = m_data[index];
        }
        // deleting an old array
        delete[] m_data;

        m_data = data;
        m_capacity = newCapacity;

    }

    // resize function changes the size of an array. All elements of the old array have been kept
    void reSize(unsigned int length) {
        reServe(length);
        m_length = length;
    }

    void shrink_to_fin() {
        if (m_capacity > m_length)
            m_capacity = m_length;
    }

    void insertBefore(int value, int index) {
        assert(index >= 0 && index <= m_length);

        T* data = new T[m_length + 1];

        // copying all elements before the index
        for (int before = 0; before < index; ++before) {
            data[before] = m_data[before];
        }

        data[index] = value;

        for (int after = index; after < m_length; ++after) {
            data[after + 1] = m_data[after];
        }

        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void push_Back(const T& value) {
        if (m_length >= m_capacity)
            reServe(m_capacity + 5);

        m_data[m_length++] = value;
    }

    void pop_Back() {
        assert(m_length > 0);
        m_length--;
    }

    void pop_Front() {
        for (int index = 1; index < m_length; ++index) {
            m_data[index - 1] = m_data[index];
        }
        --m_length;
    }

    void print_arr() {
        for (int i = 0; i < m_length; ++i)
            std::cout << m_data[i] << " ";
        std::cout << '\n';
    }

    void qsort() {
        std::sort(m_data, m_data + m_length);
    }

    int siZe() { return m_length; }

    Iterator<T> begin() const {
        return Iterator(&m_data[0]);
    }

    Iterator<T> end() const {
        return Iterator(&m_data[0 + m_length]);
    }

    ~m_vector() {
        erase();
    }
private:
    int m_length;
    int m_capacity;
    T* m_data;
};
