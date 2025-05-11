#include <iostream>
using namespace std;

template<typename T>
class Array {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;
    int capacity;
    int growBy;

    Node* getNodeAt(int index) const {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        Node* current = head;
        for (int i = 0; i < index; ++i) current = current->next;
        return current;
    }

public:
    Array(int initSize = 0, int grow = 1) : head(nullptr), tail(nullptr), size(0), capacity(0), growBy(grow) {
        SetSize(initSize, grow);
    }

    ~Array() { RemoveAll(); }

    int GetSize() const { return capacity; }

    void SetSize(int newSize, int grow = 1) {
        growBy = grow;
        if (newSize < size) {
            for (int i = size - 1; i >= newSize; --i) RemoveAt(i);
        }
        else if (newSize > capacity) {
            for (int i = capacity; i < newSize; ++i) {
                Node* newNode = new Node(T());
                if (!head) head = tail = newNode;
                else {
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode;
                }
                size++;
            }
        }
        capacity = newSize;
    }

    int GetUpperBound() const { return size - 1; }

    bool IsEmpty() const { return size == 0; }

    void FreeExtra() {
        capacity = size;
    }

    void RemoveAll() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
        capacity = 0;
    }

    T GetAt(int index) const { return getNodeAt(index)->data; }

    void SetAt(int index, const T& value) { getNodeAt(index)->data = value; }

    T& operator[](int index) { return getNodeAt(index)->data; }

    const T& operator[](int index) const { return getNodeAt(index)->data; }

    void Add(const T& value) {
        if (size == capacity) SetSize(capacity + growBy, growBy);
        Node* newNode = new Node(value);
        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void Append(const Array<T>& other) {
        for (int i = 0; i < other.size; ++i) Add(other.GetAt(i));
    }

    Array<T>& operator=(const Array<T>& other) {
        if (this == &other) return *this;
        RemoveAll();
        SetSize(other.capacity, other.growBy);
        for (int i = 0; i < other.size; ++i) Add(other.GetAt(i));
        return *this;
    }

    T* GetData() {
        T* dataArr = new T[size];
        Node* current = head;
        for (int i = 0; i < size; ++i) {
            dataArr[i] = current->data;
            current = current->next;
        }
        return dataArr; 
    }

    void InsertAt(int index, const T& value) {
        if (index < 0 || index > size) throw out_of_range("InsertAt: index out of range");
        Node* newNode = new Node(value);
        if (index == 0) {
            newNode->next = head;
            if (head) head->prev = newNode;
            head = newNode;
            if (!tail) tail = newNode;
        }
        else if (index == size) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        else {
            Node* current = getNodeAt(index);
            newNode->next = current;
            newNode->prev = current->prev;
            if (current->prev) current->prev->next = newNode;
            current->prev = newNode;
        }
        size++;
        if (size > capacity) capacity = size;
    }

    void RemoveAt(int index) {
        Node* node = getNodeAt(index);
        if (node->prev) node->prev->next = node->next;
        else head = node->next;
        if (node->next) node->next->prev = node->prev;
        else tail = node->prev;
        delete node;
        size--;
        if (size == 0) tail = nullptr;
    }
};

int main() {
    Array<int> arr(5, 3); 

    cout << "Initial array (size): " << arr.GetSize() << endl;
    for (int i = 0; i < 5; ++i) {
        arr[i] = i + 1;
    }

    cout << "Array after SetAt (via []): ";
    for (int i = 0; i <= arr.GetUpperBound(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    arr.Add(6);
    arr.Add(7);
    arr.Add(8);
    arr.Add(9); 

    cout << "Array after Add: ";
    for (int i = 0; i <= arr.GetUpperBound(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    arr.InsertAt(3, 99);
    cout << "Array after InsertAt(3, 99): ";
    for (int i = 0; i <= arr.GetUpperBound(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    arr.RemoveAt(2);
    cout << "Array after RemoveAt(2): ";
    for (int i = 0; i <= arr.GetUpperBound(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    arr.FreeExtra();
    cout << "Size after FreeExtra: " << arr.GetSize() << endl;

    return 0;
}
