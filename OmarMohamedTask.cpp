//عمر محمد العمري - علوم حاسب
#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* prev;
    Node* next;
    
    Node(int val) : value(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Helper function to create a new node
    Node* createNode(int val) {
        return new Node(val);
    }

    // Insert at the end of the list
    void append(int val) {
        Node* newNode = createNode(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    // Insert at a specific position
    void insertAt(int pos, int val) {
        if (pos < 1 || pos > size + 1) {
            cout << "Invalid position" << endl;
            return;
        }

        if (pos == 1) {
            Node* newNode = createNode(val);
            newNode->next = head;
            if (head) {
                head->prev = newNode;
            } else {
                tail = newNode;
            }
            head = newNode;
        } else if (pos == size + 1) {
            append(val);
            return;
        } else {
            Node* current = head;
            for (int i = 1; i < pos - 1; ++i) {
                current = current->next;
            }
            Node* newNode = createNode(val);
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
        }
        size++;
    }

    // Delete node at position
    void deleteAt(int pos) {
        if (pos < 1 || pos > size) {
            cout << "Invalid position" << endl;
            return;
        }

        if (pos == 1) {
            Node* temp = head;
            head = head->next;
            if (head) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            delete temp;
        } else if (pos == size) {
            Node* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        } else {
            Node* current = head;
            for (int i = 1; i < pos; ++i) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        size--;
    }

    // Display the list
    void display() const {
        Node* current = head;
        while (current) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Reverse the list
    void reverse() {
        if (!head || !head->next) return;

        Node* current = head;
        while (current) {
            Node* temp = current->next;
            current->next = current->prev;
            current->prev = temp;
            current = temp;
        }
        swap(head, tail);
    }

    // Remove duplicates
    void removeDuplicates() {
        if (!head) return;

        Node* current = head;
        while (current) {
            Node* runner = current->next;
            while (runner) {
                Node* nextNode = runner->next;
                if (runner->value == current->value) {
                    // Delete runner node
                    if (runner == tail) {
                        tail = runner->prev;
                        tail->next = nullptr;
                    } else {
                        runner->prev->next = runner->next;
                        runner->next->prev = runner->prev;
                    }
                    delete runner;
                    size--;
                }
                runner = nextNode;
            }
            current = current->next;
        }
    }

    // Merge two lists
    void merge(const DoublyLinkedList& other) {
        Node* current = other.head;
        while (current) {
            append(current->value);
            current = current->next;
        }
    }

    // Get size of the list
    int getSize() const {
        return size;
    }

    // Destructor to free memory
    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    DoublyLinkedList l1, l2, l3;
    
    // Test append and insertAt
    l1.append(2);
    l1.append(1);
    l1.append(6);
    l1.append(1);
    l1.append(9);
    l1.append(9);
    l1.append(1);
    l1.insertAt(4, 10);
    
    l2.append(4);
    l2.append(1);
    l2.append(3);
    l2.append(2);
    l2.append(7);
    l2.insertAt(1, 6);
    
    cout << "Initial lists:" << endl;
    l1.display();
    l2.display();
    cout << "************" << endl;
    
    // Test deleteAt
    l1.deleteAt(3);
    l1.display();
    cout << "************" << endl;
    
    l2.deleteAt(1);
    l2.display();
    cout << "************" << endl;
    
    // Test merge
    l3.merge(l1);
    l3.merge(l2);
    l3.display();
    cout << "************" << endl;
    
    // Test reverse
    l1.reverse();
    l1.display();
    cout << "************" << endl;
    
    // Test removeDuplicates
    l1.removeDuplicates();
    l1.display();
    cout << "************" << endl;
    
    cout << "Sizes:" << endl;
    cout << "l1: " << l1.getSize() << endl;
    cout << "l2: " << l2.getSize() << endl;
    cout << "l3: " << l3.getSize() << endl;
   
    
    return 0;
}