// Areesha Fatima 454459
#include <iostream>
#include <cstdlib> // For rand and srand
#include <ctime>   // For time
#include <string>  // For string handling
using namespace std;

class Node {
public:
    uint64_t data;    // 64-bit data
    Node* next;      // Pointer to the next node
};

void insertdata(Node * &head, uint64_t data) {
    Node* n = new Node();
    n->data = data;       // Assign data to the new node
    n->next = nullptr;    // Initialize the next pointer to nullptr
    if (head == nullptr) {
        head = n;
    }
    else {
        Node* temp = head; 
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = n;
    }
}

void display(Node* head) {
    cout << endl;
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;       // Display the data of the current node
        if (temp->next != nullptr) {
            cout << " -> "; 
        }
        temp = temp->next;   // Moving to the next node
    }
    cout << endl; 
}

string randomnum() {
    string number;
    for (int i = 0; i < 309; ++i) {
        number = number + to_string(rand() % 10); // Generate a digit from 0 to 9
    }
    return number;
}

bool isprime(const string& num) {
    // Special cases
    if (num == "1") {  // 1 is not a prime number
        return false;
    }
    if (num == "2") { // 2 is prime
        return true;
    }
    if ((num[0] - '0') % 2 == 0) { // Excluding even numbers
        return false;
    }
    uint64_t n = stoull(num); // Convert to uint64_t by using stoull which converts string to long long
    for (uint64_t i = 3; i * i <= n; i += 2) {  // checking for factors
        if (n % i == 0) {
            return false; // Found a factor, not prime
        }
    }
    return true; 
}

string constructNumber(Node* head) {
    string number;
    Node* temp = head;
    while (temp != nullptr) {
        number = number + to_string(temp->data); // Concatenate each node's data to form the full number
        temp = temp->next;
    }
    return number; // Return the full number as a string
}

int main(){
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation
    string str_random = randomnum(); // Generating a random 1024-bit number represented as a string
    cout << "Generated 1024-bit number: " << str_random << endl;

    Node* head = nullptr;
    for (size_t i = 0; i < str_random.size(); i += 19) {    // 19 characters for 64 bits
        string node = str_random.substr(i, 19);
        uint64_t data = stoull(node);     
        insertdata(head, data);
    }

    display(head);  // Display the linked list

    string number = constructNumber(head); // Construct the full number from the linked list
    bool prime = isprime(number); // Check primality of the full number

    // Output the result for the entire number
    cout << "\nFull 1024-bit number: " << number << endl;
    cout << "\nOutput: ";
    if (prime == true) {
        cout << "True, is a prime number";
    }
    else {
        cout << "False, not a prime number";
    }

    return 0;
}

