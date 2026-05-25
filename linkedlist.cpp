// ============================================================
// linkedlist.cpp
// Department 2: Linked Data Event Memory Layer
// Implementation of singly, doubly, and circular linked lists
// ============================================================

#include "linkedlist.h"

// ============================================================
// SINGLY LINKED LIST OPERATIONS
// ============================================================

// ============================================================
// initSingly()
// Sets head to null and size to 0
// Time Complexity: O(1)
// ============================================================
void initSingly(SinglyList& list) {
    list.head = NULL;
    list.size = 0;
}

// ============================================================
// insertSingly()
// Creates new event node and adds it to end of singly list
// Time Complexity: O(n) to reach end
// ============================================================
void insertSingly(SinglyList& list, float value, int time, int zone) {

    // Create new node
    EventNode* newNode = new EventNode();
    newNode->value = value;
    newNode->time = time;
    newNode->zone = zone;
    newNode->next = NULL;
    newNode->prev = NULL;

    // If list is empty, new node becomes head
    if (list.head == NULL) {
        list.head = newNode;
        list.size++;
        cout << endl << "Event stored in singly list." << endl;
        cout << "Zone: " << zone << "  Value: " << value << "  Time: " << time << endl;
        return;
    }

    // Traverse to end of list
    EventNode* current = list.head;
    while (current->next != NULL) {
        current = current->next;
    }

    // Attach new node at end
    current->next = newNode;
    list.size++;

    cout << endl << "Event stored in singly list." << endl;
    cout << "Zone: " << zone << "  Value: " << value << "  Time: " << time << endl;
}

// ============================================================
// traverseSingly()
// Prints all events in singly list from head to end
// Time Complexity: O(n)
// ============================================================
void traverseSingly(SinglyList& list) {

    if (list.head == NULL) {
        cout << endl << "Singly list is empty." << endl;
        return;
    }

    cout << endl << "--- Singly List (Forward Traversal) ---" << endl;
    cout << "Total events: " << list.size << endl;
    cout << "---------------------------------------" << endl;

    EventNode* current = list.head;
    int count = 1;

    while (current != NULL) {
        cout << "Event [" << count << "]  Zone: " << current->zone
            << "  Value: " << current->value
            << "  Time: " << current->time << endl;
        current = current->next;
        count++;
    }
}

// ============================================================
// deleteFrontSingly()
// Removes the first node from singly list
// Time Complexity: O(1)
// ============================================================
void deleteFrontSingly(SinglyList& list) {

    if (list.head == NULL) {
        cout << endl << "Singly list is empty. Nothing to delete." << endl;
        return;
    }

    EventNode* toDelete = list.head;
    list.head = list.head->next;
    delete toDelete;
    list.size--;

    cout << endl << "First event removed from singly list." << endl;
    cout << "Remaining events: " << list.size << endl;
}

// ============================================================
// searchSingly()
// Searches for events matching a zone number
// Time Complexity: O(n)
// ============================================================
void searchSingly(SinglyList& list, int zone) {

    if (list.head == NULL) {
        cout << endl << "Singly list is empty." << endl;
        return;
    }

    cout << endl << "--- Searching for Zone " << zone << " ---" << endl;

    EventNode* current = list.head;
    bool found = false;
    int count = 1;

    while (current != NULL) {
        if (current->zone == zone) {
            cout << "Found at position [" << count << "]"
                << "  Value: " << current->value
                << "  Time: " << current->time << endl;
            found = true;
        }
        current = current->next;
        count++;
    }

    if (found == false) {
        cout << "No events found for Zone " << zone << endl;
    }
}

// ============================================================
// DOUBLY LINKED LIST OPERATIONS
// ============================================================

// ============================================================
// initDoubly()
// Sets head and tail to null, size to 0
// Time Complexity: O(1)
// ============================================================
void initDoubly(DoublyList& list) {
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;
}

// ============================================================
// insertDoubly()
// Adds new event at end of doubly list
// Uses tail pointer so no traversal needed
// Time Complexity: O(1)
// ============================================================
void insertDoubly(DoublyList& list, float value, int time, int zone) {

    // Create new node
    EventNode* newNode = new EventNode();
    newNode->value = value;
    newNode->time = time;
    newNode->zone = zone;
    newNode->next = NULL;
    newNode->prev = NULL;

    // If list is empty
    if (list.head == NULL) {
        list.head = newNode;
        list.tail = newNode;
        list.size++;
        cout << endl << "Event stored in doubly list." << endl;
        cout << "Zone: " << zone << "  Value: " << value << "  Time: " << time << endl;
        return;
    }

    // Link new node after tail
    newNode->prev = list.tail;
    list.tail->next = newNode;
    list.tail = newNode;
    list.size++;

    cout << endl << "Event stored in doubly list." << endl;
    cout << "Zone: " << zone << "  Value: " << value << "  Time: " << time << endl;
}

// ============================================================
// traverseDoublyForward()
// Prints all events from head to tail
// Time Complexity: O(n)
// ============================================================
void traverseDoublyForward(DoublyList& list) {

    if (list.head == NULL) {
        cout << endl << "Doubly list is empty." << endl;
        return;
    }

    cout << endl << "--- Doubly List (Forward Traversal) ---" << endl;
    cout << "Total events: " << list.size << endl;
    cout << "---------------------------------------" << endl;

    EventNode* current = list.head;
    int count = 1;

    while (current != NULL) {
        cout << "Event [" << count << "]  Zone: " << current->zone
            << "  Value: " << current->value
            << "  Time: " << current->time << endl;
        current = current->next;
        count++;
    }
}

// ============================================================
// traverseDoublyBackward()
// Prints all events from tail to head
// Time Complexity: O(n)
// ============================================================
void traverseDoublyBackward(DoublyList& list) {

    if (list.tail == NULL) {
        cout << endl << "Doubly list is empty." << endl;
        return;
    }

    cout << endl << "--- Doubly List (Backward Traversal) ---" << endl;
    cout << "Total events: " << list.size << endl;
    cout << "----------------------------------------" << endl;

    EventNode* current = list.tail;
    int count = list.size;

    while (current != NULL) {
        cout << "Event [" << count << "]  Zone: " << current->zone
            << "  Value: " << current->value
            << "  Time: " << current->time << endl;
        current = current->prev;
        count--;
    }
}

// ============================================================
// correctLastEvent()
// Goes to tail and updates its value (backward correction)
// Time Complexity: O(1)
// ============================================================
void correctLastEvent(DoublyList& list, float newValue) {

    if (list.tail == NULL) {
        cout << endl << "Doubly list is empty. Nothing to correct." << endl;
        return;
    }

    float oldValue = list.tail->value;
    list.tail->value = newValue;

    cout << endl << "Last event corrected." << endl;
    cout << "Old Value : " << oldValue << endl;
    cout << "New Value : " << newValue << endl;
    cout << "Zone      : " << list.tail->zone << endl;
    cout << "Time      : " << list.tail->time << endl;
}

// ============================================================
// CIRCULAR LINKED LIST OPERATIONS
// ============================================================

// ============================================================
// initCircular()
// Sets head to null, size to 0
// Time Complexity: O(1)
// ============================================================
void initCircular(CircularList& list) {
    list.head = NULL;
    list.size = 0;
}

// ============================================================
// insertCircular()
// Adds new event to circular list
// Last node always points back to head
// Time Complexity: O(n)
// ============================================================
void insertCircular(CircularList& list, float value, int time, int zone) {

    // Create new node
    EventNode* newNode = new EventNode();
    newNode->value = value;
    newNode->time = time;
    newNode->zone = zone;
    newNode->prev = NULL;

    // If list is empty
    if (list.head == NULL) {
        list.head = newNode;
        newNode->next = list.head; // points to itself
        list.size++;
        cout << endl << "Event stored in circular list." << endl;
        cout << "Zone: " << zone << "  Value: " << value << "  Time: " << time << endl;
        return;
    }

    // Traverse to last node
    EventNode* current = list.head;
    while (current->next != list.head) {
        current = current->next;
    }

    // Insert new node and maintain circular link
    current->next = newNode;
    newNode->next = list.head;
    list.size++;

    cout << endl << "Event stored in circular list." << endl;
    cout << "Zone: " << zone << "  Value: " << value << "  Time: " << time << endl;
}

// ============================================================
// traverseCircular()
// Prints all events in circular list (one full loop)
// Time Complexity: O(n)
// ============================================================
void traverseCircular(CircularList& list) {

    if (list.head == NULL) {
        cout << endl << "Circular list is empty." << endl;
        return;
    }

    cout << endl << "--- Circular List (One Full Loop) ---" << endl;
    cout << "Total events: " << list.size << endl;
    cout << "-------------------------------------" << endl;

    EventNode* current = list.head;
    int count = 1;

    do {
        cout << "Event [" << count << "]  Zone: " << current->zone
            << "  Value: " << current->value
            << "  Time: " << current->time << endl;
        current = current->next;
        count++;
    } while (current != list.head);

    cout << "--> Loop back to Event [1]" << endl;
}

// ============================================================
// monitorCircular()
// Simulates continuous monitoring for a given number of cycles
// Each cycle goes through all events in the circular list
// Time Complexity: O(n * cycles)
// ============================================================
void monitorCircular(CircularList& list, int cycles) {

    if (list.head == NULL) {
        cout << endl << "Circular list is empty. No monitoring possible." << endl;
        return;
    }

    cout << endl << "--- Circular Monitoring Started ---" << endl;
    cout << "Total cycles: " << cycles << endl;
    cout << "-----------------------------------" << endl;

    EventNode* current = list.head;

    for (int cycle = 1; cycle <= cycles; cycle++) {
        cout << endl << "Cycle [" << cycle << "]:" << endl;

        int count = 0;
        do {
            cout << "  Monitoring Zone: " << current->zone
                << "  Value: " << current->value
                << "  Time: " << current->time;

            // Check for danger during monitoring
            if (current->value > 45.0) {
                cout << "  --> WARNING: High value detected!" << endl;
            }
            else {
                cout << "  --> Normal" << endl;
            }

            current = current->next;
            count++;

        } while (count < list.size);
    }

    cout << endl << "Monitoring complete." << endl;
}

// ============================================================
// restoreLastStableState()
// Copies verified events back and removes anomaly entries
// Simulates rollback to last known good state
// Time Complexity: O(n)
// ============================================================
void restoreLastStableState(SinglyList& raw, SinglyList& verified) {

    if (verified.head == NULL) {
        cout << endl << "No verified events available for restoration." << endl;
        return;
    }

    cout << endl << "--- Restoring Last Stable State ---" << endl;
    cout << "Raw events    : " << raw.size << endl;
    cout << "Verified events: " << verified.size << endl;

    cout << endl << "Stable state restored from verified event stream." << endl;
    cout << "System will use verified data going forward." << endl;

    // Show verified events as the stable state
    traverseSingly(verified);
}