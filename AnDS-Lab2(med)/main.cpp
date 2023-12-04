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

    Node<T>* GetHead() const {
        return head_;
    }

    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            Clear();
            CopyFrom(other);
        }
        return *this;
    }

    void PushTail(const T& value) {
        Node<T>* temp = new Node<T>(value);
        if (IsEmpty()) {
            head_ = temp;
            tail_ = temp;
        }
        else {
            tail_->next = temp;
            tail_ = temp;
        }
    }

    void PushTail(const LinkedList<T>& other) {
        Node<T>* temp = other.head_;
        while (temp != nullptr) {
            PushTail(temp->data);
            temp = temp->next;
        }
    }

    void PushHead(const T& value) {
        Node<T>* temp = new Node<T>(value);
        if (IsEmpty()) {
            head_ = temp;
            tail_ = temp;
        }
        else {
            temp->next = head_;
            head_ = temp;
        }
    }

    void PushHead(const LinkedList<T>& other) {
        Node<T>* temp = other.head_;
        while (temp != nullptr) {
            PushHead(temp->data);
            temp = temp->next;
        }
    }

    void PopHead() {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty.");
        }
        Node<T>* temp = head_;
        head_ = head_->next;
        delete temp;
    }

    void PopTail() {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty.");
        }
        Node<T>* current = head_;
        Node<T>* prev = nullptr;
        while (current->next != nullptr) {
            prev = current;
            current = current->next;
        }
        tail_ = prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        }
        delete current;
    }

    void DeleteNode(const T& value) {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty.");
        }
        Node<T>* current = head_;
        Node<T>* prev = nullptr;
        while (current != nullptr) {
            if (current->data == value) {
                if (current == head_) {
                    head_ = head_->next;
                }
                else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    const T& operator[](std::size_t index) const {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty.");
        }
        Node<T>* current = head_;
        std::size_t iter = 0;
        while (current != nullptr && iter < index) {
            current = current->next;
            ++iter;
        }
        if (current == nullptr) {
            throw std::out_of_range("Index out of range.");
        }
        return current->data;
    }

    T& operator[](std::size_t index) {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty.");
        }
        Node<T>* current = head_;
        std::size_t iter = 0;
        while (current != nullptr && iter < index) {
            current = current->next;
            ++iter;
        }
        if (current == nullptr) {
            throw std::out_of_range("Index out of range.");
        }
        return current->data;
    }

    void Clear() {
        Node<T>* current = head_;
        while (current != nullptr) {
            Node<T>* node_to_delete = current;
            current = current->next;
            delete node_to_delete;
        }
        head_ = nullptr;
        tail_ = nullptr;
    }

    bool IsEmpty() const {
        return head_ == nullptr;
    }

    size_t Size() const {
        std::size_t size = 0;
        Node<T>* current = head_;
        while (current != nullptr) {
            size++;
            current = current->next;
        }
        return size;
    }

    void RemoveEveryNth(int n) {
        if (n <= 1) {
            return;
        }

        Node<T>* current = head_;
        Node<T>* prev = nullptr;
        int count = 1;

        while (current != nullptr) {
            if (count % n == 0) {
                Node<T>* node_to_delete = current;
                current = current->next;

                if (node_to_delete == head_) {
                    head_ = head_->next;
                }
                else {
                    prev->next = current;
                }

                delete node_to_delete;
            }
            else {
                prev = current;
                current = current->next;
            }

            count++;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
        Node<T>* current = list.head_;
        while (current != nullptr) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }

private:
    void CopyFrom(const LinkedList<T>& other) {
        Node<T>* temp = other.head_;
        while (temp != nullptr) {
            PushTail(temp->data);
            temp = temp->next;
        }
    }

private:
    Node<T>* head_;
    Node<T>* tail_;
};

