// Areesha Fatima 454459
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string process_id;
    int execution_time;
    int remaining_time;
    Node* next;
};

void insertProcess(Node*& head, int execution_time, int count) { // to insert a process at tail
    Node* n = new Node();
    n->process_id = "P" + to_string(count);
    n->execution_time = execution_time;
    n->remaining_time = execution_time;

    if (head == nullptr) {
        head = n;
        n->next = head;
    }
    else {
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = n;
        n->next = head;
    }
    count++; // increment count when process added
}

void display(Node* head) {  // to display the list
    if (head == nullptr) return;
    Node* temp = head;
    do {
        cout << temp->process_id << " (Remaining: " << temp->remaining_time << ") ";
        temp = temp->next;
    } while (temp != head);
    cout << endl;
}

void removeProcess(Node*& head, Node* todelete) {
    if (head == todelete) {  // if only one node in list
        if (head->next == head) {
            delete todelete;
            head = nullptr;
            return;
        }
        else {
            head = todelete->next;
        }
    }
    Node* temp = head;
    while (temp->next != todelete) {
        temp = temp->next;
    }
    temp->next = todelete->next;
    delete todelete;
}

void runScheduler(Node*& head, int timecycle) {
    Node* current = head;
    int cycleNumber = 1;
    int processCount = 4; // Starting process count from 4 as P1, P2, and P3 already exist

    while (head != nullptr) {
        cout << "Cycle " << cycleNumber << ": ";
        Node* temp = current;
        Node* previous = nullptr;
        int nodesVisited = 0;
        int totalNodes = 0;   // Counting total nodes

        Node* countTemp = head;
        do {
            totalNodes++;
            countTemp = countTemp->next;
        } while (countTemp != head);

        do {
            temp->remaining_time = temp->remaining_time - timecycle;  // Decreasing the remaining time for the current process
            if (temp->remaining_time < 0) {
                temp->remaining_time = 0;
            }
            cout << temp->process_id << " (Remaining: " << temp->remaining_time << ") ";
            if (temp->remaining_time == 0) {  // If the process is completed, removing it from the list
                cout << temp->process_id << " completes. ";
                Node* todelete = temp;
                temp = temp->next;
                removeProcess(head, todelete);

                if (head == nullptr) {
                    break; // If no processes are left, break the loop
                }
                if (previous == nullptr) {
                    current = temp; // Updating current if head is removed
                }
                else {
                    previous->next = temp;
                }
                nodesVisited++;
                continue;
            }
            previous = temp;   // Moving to the next process
            temp = temp->next;
            nodesVisited++;
        } while (nodesVisited < totalNodes && head != nullptr);
        cout << endl;

        cycleNumber++;  // Increment cycle number
        if (head != nullptr) {
            current = head; // Move to the head if it exists
        }
        else {
            current = nullptr; // Otherwise, set current to nullptr
        }
        char choice;   // Optional Task, after each cycle, ask the user if they want to add a new process
        cout << "\nDo you want to add a new process? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            int newexecution_time;
            cout << "Enter execution time for the new process: ";
            cin >> newexecution_time;
            insertProcess(head, newexecution_time, processCount++);
            cout << "New process P" << processCount - 1 << " added (Execution Time: " << newexecution_time << ")." << endl;
        }
    }
}

int main() {
    Node* head = nullptr;
    int timecycle;
    insertProcess(head, 10, 1);  // Inserting intitial processes
    insertProcess(head, 5, 2);
    insertProcess(head, 8, 3);
    cout << "Initial Processes: ";
    display(head);
    cout << "Enter CPU time per process per cycle: ";
    cin >> timecycle;
    cout << "CPU Time per Process per Cycle: " << timecycle << endl;

    runScheduler(head, timecycle);
    return 0;
}