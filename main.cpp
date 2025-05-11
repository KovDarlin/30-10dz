#include <iostream>

using namespace std;

template <typename T>
class Queue {
private:
	struct Node {
		T data;
		Node* prev;
		Node* next;
		Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
	};
	Node* front;
	Node* rear;
	size_t size;
public:
	Queue(): front(nullptr), rear(nullptr), size(0){}
	~Queue() {
		while (!isEmpty()) {
			dequeue();
		}
	}

	void enqueue(const T& value) {
		Node* newNode = new Node(value);
		if(isEmpty()) {
			front = rear = newNode;
		}
		else {
			rear->next = newNode;
			newNode->prev = rear;
			rear = newNode;
		}
		size++;
	}

	void dequeue() {
		if (isEmpty()) {
			cerr << "Empty queue!No elements!\n";
			return;
		}
		Node* temp = front;
		front = front->next;
		if (front) front->prev = nullptr;
		else rear = nullptr;
		delete temp;
		size--;
	}

	T peek() const {
		if (isEmpty()) {
			throw runtime_error("Empty queue"); 
		}
		return front->data;
	}

	bool isEmpty() const {
		return front == nullptr;
	}

	size_t getSize() const {
		return size;
	}

};


int main() {
	Queue<int> q;

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);

	cout << "First element: " << q.peek() << endl;
	q.dequeue();
	cout << "After deleted element: " << q.peek() << endl;
	cout << "Size queue: " << q.getSize() << endl;
	return 0;



}
