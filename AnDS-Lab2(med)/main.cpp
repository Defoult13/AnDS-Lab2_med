#include <iostream>
#include <random>
#include <stdexcept>
#include <cstddef>

template<typename T>
struct Node {
    T data;
    Node<T>* next;

    explicit Node(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
class LinkedList {
public:
    LinkedList()
        : head_(nullptr), tail_(nullptr) {}

    explicit LinkedList(const LinkedList<T>& other)
        : head_(nullptr), tail_(nullptr) {
        CopyFrom(other);
    }

    LinkedList(std::size_t count, int min_value, int max_value)
        : head_(nullptr), tail_(nullptr) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<T> dist(min_value, max_value);
        for (std::size_t i = 0; i < count; ++i) {
            T value = dist(gen);
            PushTail(value);
        }
    }

    ~LinkedList() {
        Clear();
    }
