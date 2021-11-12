#include <iostream>
#include <cassert>
#include <array>
#include <vector>

constexpr size_t SIZE = 10;

// Task 1: Write the algorithm that can replace bool Foo(int value){return value % 2 == 0;}:
bool Foo(int bar) {
    return !(bar & 1);
}

void TaskOne() {
    std::cout << "Task 1: Write the algorithm that can replace bool Foo(int value){return value % 2 == 0;}" <<
    std::endl;
    int a = -8;
    int8_t b = -127;
    int c = 0;
    int d = 1;
    std::cout << std::boolalpha << "The number " << a << " is " << (Foo(a) ? "" : "not ") << "even" << std::endl;
    std::cout << std::boolalpha << "The number " << static_cast<int>(b) << " is "
              << (Foo(static_cast<int>(b)) ? "" : "not ") << "even" << std::endl;
    std::cout << std::boolalpha << "The number " << c << " is " << (Foo(c) ? "" : "not " )
              << "even" << std::endl;
    std::cout << std::boolalpha << "The number " << d << " is " << (Foo(d) ? "" : "not " )
              << "even" << std::endl;
}

// Task 2: Write at least 2 classes which implement the cyclic buffer

// var 1: template custom vector implementation + its iterator:
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

template<class T>
class vector_ {
public:
    vector_() : length_(0), capacity_(0), data_(nullptr) {}

    vector_(vector_ const& m): length_(m.length_), capacity_(m.capacity_), data_(new T[m.capacity_]) {}

    vector_(int length)
            : length_(length) {
        assert(length >= 0);
        capacity_ = length;

        if (length > 0) {
            data_ = new T[length];
        }
        else
            data_ = nullptr;
    }

    void erase() {
        delete[] data_;

        data_ = nullptr;
        length_ = 0;
        capacity_ = 0;
    }

    T& operator[](const size_t index) {
        assert(index < length_);
        return data_[index];
    }

    void reServe(unsigned int newCapacity) {
        // if the length of an array is equal to planed length - return
        if (newCapacity == capacity_)
            return;

        // if empty array is needed - do it and return
        if (newCapacity <= 0) {
            erase();
            return;
        }

        // allocating a new array
        T* data = new T[newCapacity];

        // copying elements from a lesser array to a greater
        if (capacity_ > 0) {
            int elementsToCopy = (newCapacity > capacity_) ? capacity_ : newCapacity;

            for (int index = 0; index < elementsToCopy; ++index)
                data[index] = data_[index];
        }
        // deleting an old array
        delete[] data_;

        data_ = data;
        capacity_ = newCapacity;

    }

    // resize function changes the size of an array. All elements of the old array have been kept
    void reSize(size_t length) {
        reServe(length);
        length_ = length;
    }

    void shrink_to_fin() {
        if (capacity_ > length_)
            capacity_ = length_;
    }

    void insertBefore(T value, size_t index) {
        assert(index <= length_);

        T* data = new T[length_ + 1];

        // copying all elements before the index
        for (int before = 0; before < index; ++before) {
            data[before] = data_[before];
        }

        data[index] = value;

        for (size_t after = index; after < length_; ++after) {
            data[after + 1] = data_[after];
        }

        delete[] data_;
        data_ = data;
        ++length_;
    }

    // The magic happens here:
    void push_Back(const T& value) {
        if (length_ == capacity_)
            data_[data_[length_ - 1] % length_] = value; // if index >= length -> we're writing into 0 index etc
        else
            data_[length_++] = value;
    }

    void pop_Back() {
        assert(length_ > 0);
        length_--;
    }

    void pop_Front() {
        for (size_t index = 1; index < length_; ++index) {
            data_[index - 1] = data_[index];
        }
        --length_;
    }

    void print_arr() {
        for (int i = 0; i < length_; ++i)
            std::cout << data_[i] << " ";
        std::cout << '\n';
    }

    int siZe() { return length_; }

    Iterator<T> begin() const {
        return Iterator(&data_[0]);
    }

    Iterator<T> end() const {
        return Iterator(&data_[0 + length_]);
    }

    ~vector_() {
        erase();
    }
private:
    size_t length_;
    size_t capacity_;
    T* data_;
};

// var 2: more C-style with structures:
//template<typename T>
//struct Node {
//    T data_;
//    Node* next_;
//};
//
//constexpr size_t MAX_CAPACITY = 5;
//
//template<class T>
//class CyclicList : public Iterator<T>{
//public:
//    CyclicList() {
//        head_ = nullptr;
//        size_ = 0;
//    }
//
//    void push_back(T&& value) {
//        Node<T>* new_ = new Node<T>;
//        new_->data_ = value;
//        new_->next_ = head_;
//
//        Node<T>* current_ = head_;
//
//        if (current_ == nullptr) {
//            head_ = new_;
//            new_->next_ = head_;
//            size_++;
//            return;
//        }
//        else {
//            while (current_->next_ != head_) {
//                current_ = current_->next_;
//            }
//            current_->next_ = new_;
//            size_++;
//        }
//    }
//
//    Node<T>* rem_node(T&& data) {
//        Node<T>* current_ = head_;
//        Node<T>* parent_ = nullptr;
//
//        if (current_ == nullptr)
//            return nullptr;
//
//        while (current_->next != head_ && current_->data_ != data) {
//            parent_ = current_;
//            current_ = current_->next;
//        }
//
//        if (current_->data_ != data)
//            return nullptr;
//
//        if (current_ == head_) {
//            if (current_->next == head_) {
//                head_ = nullptr;
//                size_--;
//                return current_;
//            }
//            else {
//                Node<T>* temp_ = head_;
//
//                while (current_->next_ != head_) {
//                    current_ = current_->next_;
//                }
//                head_ = temp_->next_;
//                current_->next_ = head_;
//                size_--;
//                return temp_;
//            }
//        }
//        parent_->next_ = current_->next_;
//        size_--;
//        return current_;
//    }
//
//    void printOneNode(Node<T>* n) {
//        if (n == nullptr) {
//            std::cout << "[]";
//            return;
//        }
//        std::cout << '[' << n->data_ << ']';
//    }
//
//    void print() {
//        Node<T>* current_ = head_;
//
//        if (current_ == nullptr)
//            printOneNode(current_);
//        else {
//            do {
//                printOneNode(current_);
//                current_ = current_->next_;
//            } while (current_ != head_);
//        }
//        std::cout << "\nSize: " << size_ << std::endl;
//    }
//
//private:
//    Node<T>* head_;
//    size_t size_;
//    size_t capacity_ = MAX_CAPACITY;
//};

void cyclicIntArrInsert(int* arr, const size_t size, const size_t index, int val) {
    if (index < size)
        arr[index] = val;
    else
        arr[arr[size - 1] % size] = val;
}

void print(int* arr, const size_t size) {
    for (size_t i = 0; i < size; ++i)
        std::cout << arr[i] << (i == size - 1? "" : ", ");
    std::cout << std::endl;
}

void TaskTwo() {
    std::cout << "Custom vector implementation: " << std::endl;
    vector_<int> Foo;
    constexpr size_t SZ = 5;
    Foo.reSize(SZ);
    Foo[0] = 1;
    Foo[1] = 2;
    Foo[2] = 3;
    Foo[3] = 4;
    Foo[4] = 5;
    Foo.print_arr();
    Foo.push_Back(6);
    Foo.print_arr();

//    std::cout << "\nCyclic list implementation: " << std::endl;
//    CyclicList<int> lst;
//    lst.push_back(10);
//    lst.push_back(20);
//    lst.push_back(30);
//    lst.push_back(40);
//    lst.push_back(50);
//    lst.print();
    std::cout << "\nArray implementation: " << std::endl;
    int array[SZ];
    cyclicIntArrInsert(array, SZ, 0, 10);
    cyclicIntArrInsert(array, SZ, 1, 20);
    cyclicIntArrInsert(array, SZ, 2, 30);
    cyclicIntArrInsert(array, SZ, 3, 40);
    cyclicIntArrInsert(array, SZ, 4, 50);
    print(array, SZ);
    cyclicIntArrInsert(array, SZ, 5, 60);
    print(array, SZ);
}

// Task 3: Write the fastest sorting function
void swapInt(int* lhs, int* rhs) {
    int temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

void printIntArr(std::array<int, SIZE> arr) {
    std::for_each(arr.begin(), arr.end(), [&arr](int& i) {
        std::cout << '{' << i;
        if (&i != arr.end() - 1)
             std::cout <<  "}, ";
        else
            std::cout << '}' << std::endl;
    });
}

void quick_sort(std::array<int, SIZE>& arr, int first, int last) {
    if (first < last) {
        int x = arr[last];
        int i = first;

        for (size_t j = first; j <= last - 1; ++j) {
            if (arr[j] <= x) {
                swapInt(&arr[i], &arr[j]);
                i++;
            }
        }
        swapInt(&arr[i], &arr[last]);
        quick_sort(arr, first, i - 1);
        quick_sort(arr, i + 1, last);
    }
}

void TaskThree() {
    std::array<int, SIZE> arr {{ 0, 10, 7, 18, 32, 5, 2, 11, 100, 15}};
    std::cout << "The array before the quick sort function:" << std::endl;
    printIntArr(arr);
    quick_sort(arr, 0, SIZE - 1);
    std::cout << "The array after the quick sort function:" << std::endl;
    printIntArr(arr);
}

int main() {
    TaskOne();
    TaskTwo();
    TaskThree();
    return 0;
}
