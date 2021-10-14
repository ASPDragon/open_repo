#include <array>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <mutex>
#include <vector>
#include <random>
#include <execution>

std::mutex mut;
using std::chrono_literals::operator""ms;

// Task One function: wrapping for std::cout to provide a thread-safe access
void pcout(std::string str) {
    std::lock_guard<std::mutex> lg(mut);
    std::cout << "Start thread: " << '"' <<  str << '"' << " ";
    std::this_thread::sleep_for(30ms);
    std::cout << "Stop thread" << std::endl;
}

// Task Two functions: Looking for an N-th Prime Number with showing of the calculation in the separate thread.
constexpr size_t SZ = 255;

void PrimeArr(std::array<int, SZ>& arr) {
    std::lock_guard<std::mutex> lg(mut);
    int capacity = 2;
    for (size_t i = 4; i < SZ; ++i) {
        bool isPrime = true;
        for (size_t j = 0; j < capacity; ++j) {
            std::thread th1;
            if (i % arr[j] == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            std::this_thread::sleep_for(10ms);
            arr[capacity++] = i;
        }
    }
}

void PrintSieve(std::array<int, SZ>& arr) {
    std::lock_guard<std::mutex> lg(mut);
    std::this_thread::sleep_for(100ms);
    auto it { arr.begin() };
    std::for_each(arr.begin(), arr.end(), [&](int& val) {
        if (val != 0) {
            constexpr int OFFSET = 3;
            std::cout << std::setw(OFFSET) << val << (std::next(it) == arr.end() ? "" : " ");
        }
    });
    std::cout << std::endl;
}

void PrintNumber(std::array<int, SZ>& arr, size_t ind) {
    std::scoped_lock lg(mut);
    std::this_thread::sleep_for(100ms);
    constexpr int INDEX_ARITHMETICS = 1;
    std::cout << ind << "th Prime Number is: " << arr[ind - INDEX_ARITHMETICS] << std::endl;
}

void NPrime(int number) {
    std::array<int, SZ> primes { {2, 3} };
    std::thread th1 {PrimeArr, std::ref(primes)};
    th1.join();
    std::thread th2(PrintSieve, std::ref(primes));
    th2.join();
    std::thread th3(PrintNumber, std::ref(primes), number);
    th3.join();
}

// Task Three functions: 2 Threads (Owner and Thief). Owner brings valuable items at home,
// the Thief steals the most valuable of them.
std::mutex m1;
std::mutex m2;

//template<typename T>
//void PushRandT(T& container) {
//    std::random_device random;
//    std::mt19937_64 mt {random()};
//    std::uniform_int_distribution<int> dist {0, 10000};
//    auto gen = [&]() {return dist(mt); };
//    container.push_back(gen);
//}

void IBroughtSomeItemsAtHome(std::vector<int>& cont) {
    srand(time(NULL));
    size_t SZ = 20;
    int day = 1;
    while (cont.size() < SZ) {
        m1.lock();
        int item = rand() % 10000;
        cont.push_back(item);
        std::cout << "Day " << day++ << " The fair owner brought home " << item << '$' << std::endl;
        std::sort(std::execution::par, cont.begin(), cont.end());
        if (day == 20)
            break;
        m1.unlock();
        std::this_thread::sleep_for(1ms);
    }
}

int FindMax(std::vector<int> cont) {
    auto it { cont.begin() };
    int max = *it;
    for (; it != std::prev(cont.end()); ++it) {
        if (*it < *std::next(it))
            max = *std::next(it);
    }
    return max;
}

std::vector<int>::iterator LinearSearch(std::vector<int> cont, int value) {
    auto it { cont.begin() };
    while (it != cont.end() && *it != value) {
        it++;
    }
    if (it != cont.end())
        return it;
    else
        return cont.end();
}

void TimeToMakeSomeMoney(std::vector<int>& cont) {
    int day = 1;
    int max = FindMax(cont);
    int stolen = 0;
    while (!cont.empty()) {
        m2.lock();
        stolen = *std::find(cont.begin(), cont.end(), max);
        cont.pop_back();
        std::cout << "Day " << day++ << " "  << "Our Thief has just executed a successful raid on the apartment and took "
                  << stolen << "$" << std::endl;
        if (day == 20)
            break;
        m2.unlock();
        std::this_thread::sleep_for(5ms);
    }
}

// Functions calls
void TaskOne() {
    std::cout << "\tTask #1" << std::endl;
    std::thread th1 { pcout, "Good afternoon, Earthling Ilya!" };
    std::thread th2 { pcout, "The ultimate answer to life, the universe and everything?" };
    std::thread th3 { pcout, "42" };
    std::thread th4 { pcout, "Foo Bar!" };
    th1.join();
    th2.join();
    th3.join();
    th4.join();
}

void TaskTwo() {
    std::cout << "\tTask #2" << std::endl;
    int num;
    std::cout << "Please, input the number of the prime number you'd like to get: ";
    std::cin >> num;
    std::cout << std::endl;
    NPrime(num);
}

void TaskThree() {
    std::cout << "\tTask #3" << std::endl;
    std::vector<int> possession {100, 800, 9000, 1098, 587, 876, 4242, 7654, 2442};
    std::thread Owner { IBroughtSomeItemsAtHome, std::ref(possession) };
    std::thread Thief { TimeToMakeSomeMoney, std::ref(possession) };
    Owner.join();
    Thief.join();
}

int main() {
    TaskOne();
    TaskTwo();
    TaskThree();
    return 0;
}