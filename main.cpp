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
	Node* head;
	Node* tail;
public:
	Queue() : head(nullptr), tail(nullptr){}
	~Queue() {
		Node* current = head;
		while(current){
			Node* temp = current;
			current = current->next;
			delete temp;
		}
	}

	void push_back(int value) {
		Node* newNode = new Node(value);
		if (!head) head = tail = newNode; 
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}

	Node* getHead() const {
		return head;
	}

	Node* clone() const {
		Queue* newQueue = new Queue();
		for (Node* curr = head; curr != nullptr; curr = curr->next) {
			newQueue->push_back(curr->data);
		}
		return newQueue->getHead();
	}

	Queue operator+ (const Queue& other) const {
		Queue result;
		for (Node* curr = head; curr != nullptr; curr = curr->next) 
			result.push_back(curr->data);
		for (Node* curr = other.head; curr != nullptr; curr = curr->next) 
			result.push_back(curr->data);
		return result;
	}


	Queue operator* (const Queue& other) const {
		Queue result;
		for (Node* curr = head; curr != nullptr; curr = curr->next){
			for (Node* o = other.head; o != nullptr; o = o->next){
				if (curr->data == o->data) {
					result.push_back(curr->data);
					break;
				}
			}
		}
		return result;
	}

	void print() const {
		for (Node* curr = head; curr != nullptr; curr = curr->next)
			cout << curr->data << " ";
		cout << endl;
	}

};


int main() {
	Queue<int> a, b;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);

	b.push_back(2);
	b.push_back(3);
	b.push_back(4);

	cout << "List A: ";
	a.print();
	cout << "List B: ";
	b.print();

	Queue<int> c = a + b;
	cout << "A + B: ";
	c.print();

	Queue<int> d = a * b;
	cout << "A * B (intersection): ";
	d.print();

	auto cloned = a.clone();  
	cout << "Cloned A (via pointer): ";
	for (auto p = cloned; p; p = p->next) cout << p->data << " ";
	cout << endl;

	return 0;
}
