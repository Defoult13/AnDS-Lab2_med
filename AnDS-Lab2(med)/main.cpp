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
        : _head(nullptr), _tail(nullptr) {}

    explicit LinkedList(const LinkedList<T>& other)
        : _head(nullptr), _tail(nullptr) {
        CopyFrom(other);
    }

    LinkedList(std::size_t count, int min_value, int max_value)
        : _head(nullptr), _tail(nullptr) {
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
        return _head;
    }

    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            Clear();
            CopyFrom(other);
        }
        return *this;
    }

    void push_tail(const T& value) {
        Node<T>* temp = new Node<T>(value);
        if (IsEmpty()) {
            _head = temp;
            _tail = temp;
        }
        else {
            _tail->next = temp;
            _tail = temp;
        }
    }

    void push_tail(const LinkedList<T>& other) {
        Node<T>* temp = other._head;
        while (temp != nullptr) {
            push_tail(temp->data);
            temp = temp->next;
        }
    }

    void push_head(const T& value) {
        Node<T>* temp = new Node<T>(value);
        if (IsEmpty()) {
            _head = temp;
            _tail = temp;
        }
        else {
            temp->next = _head;
            _head = temp;
        }
    }

    void push_head(const LinkedList<T>& other) {
        Node<T>* temp = other._head;
        LinkedList<T> tempCopy; 
        while (temp != nullptr) {
            tempCopy.push_head(temp->data);
            temp = temp->next;
        }

        temp = tempCopy._head;
        while (temp != nullptr) {
            push_head(temp->data);
            temp = temp->next;
        }
    }

    void pop_head() {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty.");
        }
        Node<T>* temp = _head;
        _head = _head->next;
        delete temp;
    }

    void pop_tail() {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty.");
        }
        Node<T>* current = _head;
        Node<T>* prev = nullptr;
        while (current->next != nullptr) {
            prev = current;
            current = current->next;
        }
        _tail = prev;
        if (_tail != nullptr) {
            _tail->next = nullptr;
        }
        delete current;
    }

    void DeleteNode(const T& value) {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty.");
        }
        Node<T>* current = _head;
        Node<T>* prev = nullptr;
        while (current != nullptr) {
            if (current->data == value) {
                if (current == _head) {
                    _head = _head->next;
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
        Node<T>* current = _head;
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
        Node<T>* current = _head;
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
        Node<T>* current = _head;
        while (current != nullptr) {
            Node<T>* node_to_delete = current;
            current = current->next;
            delete node_to_delete;
        }
        _head = nullptr;
        _tail = nullptr;
    }

    bool IsEmpty() const {
        return _head == nullptr;
    }

    size_t Size() const {
        std::size_t size = 0;
        Node<T>* current = _head;
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

        Node<T>* current = _head;
        Node<T>* prev = nullptr;
        int count = 1;

        while (current != nullptr) {
            if (count % n == 0) {
                Node<T>* node_to_delete = current;
                current = current->next;

                if (node_to_delete == _head) {
                    _head = _head->next;
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
        Node<T>* current = list._head;
        while (current != nullptr) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }

private:
    void CopyFrom(const LinkedList<T>& other) {
        Node<T>* temp = other._head;
        while (temp != nullptr) {
            PushTail(temp->data);
            temp = temp->next;
        }
    }

private:
    Node<T>* _head;
    Node<T>* _tail;
};

void findUnluckyNumbersAndPrint(int N) {
    LinkedList<int> numbers;

    for (int i = 1; i <= N; ++i) {
        numbers.push_tail(i);
    }

    int step = 2;
    int index = 0;

    while (index < numbers.Size() && step <= N) {
        numbers.RemoveEveryNth(step);
        index++;
        if (index < numbers.Size()) {
            step = numbers[index];
        }
    }

    for (std::size_t i = 0; i < numbers.Size(); ++i) {
        std::cout << numbers[i] << " ";
    }

    std::cout << std::endl;
}

int main() {
    try {
        LinkedList<int> list;
        list.push_tail(1);
        list.push_tail(2);
        list.push_tail(3);
        list.push_head(0);

        std::cout << "Original List: " << list << std::endl;

        list.pop_head();
        list.pop_tail();

        std::cout << "List after PopHead and PopTail: " << list << std::endl;

        LinkedList<int> anotherList;
        anotherList.push_tail(4);
        anotherList.push_tail(5);
        anotherList.push_tail(6);

        list.push_tail(anotherList);

        LinkedList<int> list1;
        list1.push_tail(11);
        list1.push_tail(12);
        list1.push_tail(13);
        
        LinkedList<int> anotherList1;
        anotherList1.push_tail(1);
        anotherList1.push_tail(2);
        anotherList1.push_tail(3);

        list1.push_head(anotherList1);

        std::cout << "List1 after Pushhead with anotherList: " << list1 << std::endl;

        std::cout << "List after PushTail with anotherList: " << list << std::endl;

        std::cout << "Element at index 1: " << list[1] << std::endl;

        list.RemoveEveryNth(2);

        std::cout << "List after RemoveEveryNth(2): " << list << std::endl;

        findUnluckyNumbersAndPrint(100);

    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
