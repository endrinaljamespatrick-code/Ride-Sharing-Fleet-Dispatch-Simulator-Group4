#include <iostream>
#include <string>
using namespace std;

// ENDRINAL: Stores driver information for ride‑sharing
struct Driver {
    int id;
    string name;
    double distance;
    double rating;

    Driver() : id(0), name(""), distance(0.0), rating(0.0) {}
    Driver(int i, string n, double d, double r)
        : id(i), name(n), distance(d), rating(r) {}
};

// ENDRINAL: Stores incoming passenger ride requests
struct RideRequest {
    int requestId;
    string passengerName;
    string location;
    double distance;

    RideRequest() : requestId(0), passengerName(""), location(""), distance(0.0) {}
    RideRequest(int rid, string pname, string loc, double d)
        : requestId(rid), passengerName(pname), location(loc), distance(d) {}
};

// ENDRINAL: Node for singly linked list (driver list)
struct LLNode {
    Driver data;
    LLNode* next;
    LLNode(Driver d) : data(d), next(nullptr) {}
};

// ENDRINAL: Custom Singly Linked List to hold all available drivers
class LinkedList {
private:
    LLNode* head;
public:
    LinkedList() : head(nullptr) {}

    void addAtEnd(Driver d) {
        LLNode* newNode = new LLNode(d);
        if (!head) { head = newNode; return; }
        LLNode* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    void addAtBeginning(Driver d) {
        LLNode* newNode = new LLNode(d);
        newNode->next = head;
        head = newNode;
    }

    void removeById(int id) {
        if (!head) { cout << "List empty.\n"; return; }
        if (head->data.id == id) {
            LLNode* temp = head;
            head = head->next;
            delete temp;
            cout << "Driver removed.\n";
            return;
        }
        LLNode* curr = head;
        while (curr->next && curr->next->data.id != id) curr = curr->next;
        if (curr->next) {
            LLNode* temp = curr->next;
            curr->next = temp->next;
            delete temp;
            cout << "Driver removed.\n";
        } else {
            cout << "Driver not found.\n";
        }
    }

    void display() {
        if (!head) { cout << "[Linked List] Empty\n"; return; }
        cout << "\n===== Registered Drivers =====\n";
        LLNode* temp = head;
        while (temp) {
            cout << "ID: " << temp->data.id
                 << " | Name: " << temp->data.name
                 << " | Dist: " << temp->data.distance << "km"
                 << " | Rating: " << temp->data.rating << "\n";
            temp = temp->next;
        }
        cout << "===============================\n";
    }

    ~LinkedList() {
        LLNode* curr = head;
        while (curr) {
            LLNode* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

// ENDRINAL: Node for stack (ride dispatch history / undo)
struct StackNode {
    RideRequest data;
    StackNode* next;
    StackNode(RideRequest r) : data(r), next(nullptr) {}
};

// ENDRINAL: Custom Stack LIFO for recent ride dispatch history
class Stack {
private:
    StackNode* topNode;
public:
    Stack() : topNode(nullptr) {}

    void push(RideRequest r) {
        StackNode* newNode = new StackNode(r);
        newNode->next = topNode;
        topNode = newNode;
    }

    RideRequest pop() {
        if (!topNode) { cout << "[Stack] Empty!\n"; return RideRequest(); }
        StackNode* temp = topNode;
        RideRequest val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    RideRequest peek() {
        if (!topNode) { cout << "[Stack] Empty!\n"; return RideRequest(); }
        return topNode->data;
    }

    bool isEmpty() { return topNode == nullptr; }

    void display() {
        if (!topNode) { cout << "[Stack] Empty\n"; return; }
        cout << "\n===== Recent Requests Stack =====\n";
        StackNode* temp = topNode;
        while (temp) {
            cout << "Req#" << temp->data.requestId
                 << " | " << temp->data.passengerName
                 << " @ " << temp->data.location << "\n";
            temp = temp->next;
        }
        cout << "==================================\n";
    }

    ~Stack() {
        while (!isEmpty()) pop();
    }
};

// ENDRINAL: Node for queue (waiting ride requests)
struct QueueNode {
    RideRequest data;
    QueueNode* next;
    QueueNode(RideRequest r) : data(r), next(nullptr) {}
};

// ENDRINAL: Custom Queue FIFO for peak‑hour waiting ride requests
class Queue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
public:
    Queue() : frontNode(nullptr), rearNode(nullptr) {}

    void enqueue(RideRequest r) {
        QueueNode* newNode = new QueueNode(r);
        if (!rearNode) {
            frontNode = rearNode = newNode;
            return;
        }
        rearNode->next = newNode;
        rearNode = newNode;
    }

    RideRequest dequeue() {
        if (!frontNode) { cout << "[Queue] Empty!\n"; return RideRequest(); }
        QueueNode* temp = frontNode;
        RideRequest val = temp->data;
        frontNode = frontNode->next;
        if (!frontNode) rearNode = nullptr;
        delete temp;
        return val;
    }

    RideRequest front() {
        if (!frontNode) { cout << "[Queue] Empty!\n"; return RideRequest(); }
        return frontNode->data;
    }

    bool isEmpty() { return frontNode == nullptr; }

    void display() {
        if (!frontNode) { cout << "[Queue] Empty\n"; return; }
        cout << "\n===== Waiting Requests Queue =====\n";
        QueueNode* temp = frontNode;
        while (temp) {
            cout << "Req#" << temp->data.requestId
                 << " | " << temp->data.passengerName
                 << " | Dist: " << temp->data.distance << "km\n";
            temp = temp->next;
        }
        cout << "===================================\n";
    }

    ~Queue() {
        while (!isEmpty()) dequeue();
    }
};

// ENDRINAL: Node for Binary Search Tree (fast driver lookup by ID)
struct BSTNode {
    Driver data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Driver d) : data(d), left(nullptr), right(nullptr) {}
};

// ENDRINAL: Custom Binary Search Tree for fast driver search using ID
class BST {
private:
    BSTNode* root;

    BSTNode* insertHelper(BSTNode* node, Driver d) {
        if (!node) return new BSTNode(d);
        if (d.id < node->data.id)
            node->left = insertHelper(node->left, d);
        else if (d.id > node->data.id)
            node->right = insertHelper(node->right, d);
        return node;
    }

    BSTNode* searchHelper(BSTNode* node, int id) {
        if (!node || node->data.id == id) return node;
        if (id < node->data.id) return searchHelper(node->left, id);
        return searchHelper(node->right, id);
    }

    void inorderHelper(BSTNode* node) {
        if (!node) return;
        inorderHelper(node->left);
        cout << "ID: " << node->data.id
             << " | " << node->data.name
             << " | Dist: " << node->data.distance << "km\n";
        inorderHelper(node->right);
    }

    void destroyTree(BSTNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(Driver d) { root = insertHelper(root, d); }

    bool search(int id) { return searchHelper(root, id) != nullptr; }

    void inorder() {
        cout << "\n===== BST (Sorted by ID) =====\n";
        inorderHelper(root);
        cout << "==============================\n";
    }

    ~BST() { destroyTree(root); }
};

int main() {
    cout << "===== TASK 1: RIDE‑SHARING DATA STRUCTURES (ENDRINAL) =====\n\n";

    cout << "=== 1. SINGLY LINKED LIST ===" << endl;
    LinkedList driverList;
    driverList.addAtEnd(Driver(101, "Sarah", 1.2, 4.9));
    driverList.addAtEnd(Driver(102, "Jess", 0.8, 4.8));
    driverList.addAtEnd(Driver(103, "Marco", 2.5, 4.7));
    driverList.addAtBeginning(Driver(100, "Leo", 1.5, 4.6));
    driverList.display();
    driverList.removeById(103);
    driverList.display();

    cout << "\n=== 2. QUEUE (FIFO - Ride Requests) ===" << endl;
    Queue requestQueue;
    requestQueue.enqueue(RideRequest(1, "Ana", "Downtown", 2.1));
    requestQueue.enqueue(RideRequest(2, "Ben", "Subway", 1.5));
    requestQueue.enqueue(RideRequest(3, "Carla", "Mall", 3.0));
    requestQueue.display();

    cout << "\nProcessing: " << requestQueue.front().passengerName << endl;
    requestQueue.dequeue();
    requestQueue.display();

    cout << "\n=== 3. STACK (LIFO - Recent History) ===" << endl;
    Stack historyStack;
    historyStack.push(RideRequest(10, "Dan", "Park", 1.0));
    historyStack.push(RideRequest(11, "Eve", "School", 2.2));
    historyStack.push(RideRequest(12, "Fay", "Hospital", 1.8));
    historyStack.display();

    cout << "\nUndo: " << historyStack.peek().passengerName << endl;
    historyStack.pop();
    historyStack.display();

    cout << "\n=== 4. BINARY SEARCH TREE (Search by Driver ID) ===" << endl;
    BST driverBST;
    driverBST.insert(Driver(205, "Alex", 3.8, 4.5));
    driverBST.insert(Driver(201, "Bea", 1.1, 4.8));
    driverBST.insert(Driver(208, "Coby", 2.0, 4.6));
    driverBST.insert(Driver(203, "Dina", 0.9, 4.9));
    driverBST.inorder();

    int searchID = 203;
    cout << "\nSearch Driver ID " << searchID << ": ";
    if (driverBST.search(searchID))
        cout << "FOUND\n";
    else
        cout << "NOT FOUND\n";

    cout << "\n===== TASK 1 COMPLETE =====\n";
    return 0;
}