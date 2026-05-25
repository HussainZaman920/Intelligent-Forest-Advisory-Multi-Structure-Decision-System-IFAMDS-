// ============================================================
// stack.cpp
// Department 3: Execution Control and Computational
//               Reasoning Layer
// Implementation of stack operations for system state
// management and rollback
// ============================================================

#include "stack.h"

// ============================================================
// initStack()
// Sets top to NULL and size to 0
// Time Complexity: O(1)
// ============================================================
void initStack(Stack& s) {
    s.top = NULL;
    s.size = 0;
}

// ============================================================
// pushState()
// Creates a new state node and pushes it onto the stack
// Time Complexity: O(1)
// ============================================================
void pushState(Stack& s, float temp, float smoke, float humidity, int zone, int timeStep, bool stable) {

    // Create new stack node
    StackNode* newNode = new StackNode();
    newNode->data.temperature = temp;
    newNode->data.smoke = smoke;
    newNode->data.humidity = humidity;
    newNode->data.zone = zone;
    newNode->data.timeStep = timeStep;
    newNode->data.isStable = stable;
    newNode->next = s.top;

    // New node becomes top
    s.top = newNode;
    s.size++;

    cout << endl << "State pushed onto stack." << endl;
    cout << "Zone      : " << zone << endl;
    cout << "Temp      : " << temp << "C" << endl;
    cout << "Smoke     : " << smoke << endl;
    cout << "Humidity  : " << humidity << "%" << endl;
    cout << "Time Step : " << timeStep << endl;

    if (stable == true) {
        cout << "Status    : STABLE" << endl;
    }
    else {
        cout << "Status    : UNSTABLE" << endl;
    }

    cout << "Stack size: " << s.size << endl;
}

// ============================================================
// popState()
// Removes the top state from the stack
// Time Complexity: O(1)
// ============================================================
void popState(Stack& s) {

    if (s.top == NULL) {
        cout << endl << "Stack is empty. Nothing to pop." << endl;
        return;
    }

    StackNode* toDelete = s.top;
    s.top = s.top->next;
    s.size--;

    cout << endl << "State popped from stack." << endl;
    cout << "Removed Zone      : " << toDelete->data.zone << endl;
    cout << "Removed Temp      : " << toDelete->data.temperature << "C" << endl;
    cout << "Remaining states  : " << s.size << endl;

    delete toDelete;
}

// ============================================================
// peekState()
// Shows the top state without removing it
// Time Complexity: O(1)
// ============================================================
void peekState(Stack& s) {

    if (s.top == NULL) {
        cout << endl << "Stack is empty. No state to peek." << endl;
        return;
    }

    cout << endl << "--- Current Top State ---" << endl;
    cout << "Zone      : " << s.top->data.zone << endl;
    cout << "Temp      : " << s.top->data.temperature << "C" << endl;
    cout << "Smoke     : " << s.top->data.smoke << endl;
    cout << "Humidity  : " << s.top->data.humidity << "%" << endl;
    cout << "Time Step : " << s.top->data.timeStep << endl;

    if (s.top->data.isStable == true) {
        cout << "Status    : STABLE" << endl;
    }
    else {
        cout << "Status    : UNSTABLE" << endl;
    }
}

// ============================================================
// isStackEmpty()
// Returns true if stack has no elements
// Time Complexity: O(1)
// ============================================================
bool isStackEmpty(Stack& s) {
    if (s.top == NULL) {
        return true;
    }
    return false;
}

// ============================================================
// displayAllStates()
// Prints all states from top to bottom
// Time Complexity: O(n)
// ============================================================
void displayAllStates(Stack& s) {

    if (s.top == NULL) {
        cout << endl << "Stack is empty. No states saved." << endl;
        return;
    }

    cout << endl << "--- All Saved System States ---" << endl;
    cout << "Total states: " << s.size << endl;
    cout << "-------------------------------" << endl;

    StackNode* current = s.top;
    int count = s.size;

    while (current != NULL) {
        cout << endl << "State [" << count << "]:" << endl;
        cout << "  Zone      : " << current->data.zone << endl;
        cout << "  Temp      : " << current->data.temperature << "C" << endl;
        cout << "  Smoke     : " << current->data.smoke << endl;
        cout << "  Humidity  : " << current->data.humidity << "%" << endl;
        cout << "  Time Step : " << current->data.timeStep << endl;

        if (current->data.isStable == true) {
            cout << "  Status    : STABLE" << endl;
        }
        else {
            cout << "  Status    : UNSTABLE" << endl;
        }

        current = current->next;
        count--;
    }
}

// ============================================================
// rollbackToStable()
// Pops states from stack until a stable state is found
// Restores system to last known good state
// Time Complexity: O(n)
// ============================================================
void rollbackToStable(Stack& s) {

    if (s.top == NULL) {
        cout << endl << "Stack is empty. Cannot rollback." << endl;
        return;
    }

    cout << endl << "--- Rolling Back to Last Stable State ---" << endl;

    int poppedCount = 0;

    // Keep popping until we find a stable state
    while (s.top != NULL) {

        if (s.top->data.isStable == true) {
            cout << endl << "Stable state found!" << endl;
            cout << "Rolled back " << poppedCount << " unstable state(s)." << endl;
            peekState(s);
            return;
        }

        // Pop unstable state
        cout << "Removing unstable state - Zone: " << s.top->data.zone
            << "  Temp: " << s.top->data.temperature << "C" << endl;

        StackNode* toDelete = s.top;
        s.top = s.top->next;
        s.size--;
        delete toDelete;
        poppedCount++;
    }

    cout << endl << "No stable state found in stack." << endl;
    cout << "System needs fresh initialization." << endl;
}

// ============================================================
// checkInconsistency()
// Checks top state for dangerous or inconsistent values
// Flags anomalies based on thresholds
// Time Complexity: O(1)
// ============================================================
void checkInconsistency(Stack& s) {

    if (s.top == NULL) {
        cout << endl << "Stack is empty. Nothing to check." << endl;
        return;
    }

    cout << endl << "--- Checking Top State for Inconsistency ---" << endl;

    bool inconsistent = false;

    // Check temperature
    if (s.top->data.temperature > 45.0) {
        cout << "INCONSISTENCY - Temperature " << s.top->data.temperature
            << "C exceeds safe limit of 45C" << endl;
        inconsistent = true;
    }

    // Check smoke
    if (s.top->data.smoke > 70.0) {
        cout << "INCONSISTENCY - Smoke " << s.top->data.smoke
            << " exceeds safe limit of 70" << endl;
        inconsistent = true;
    }

    // Check humidity
    if (s.top->data.humidity < 20.0) {
        cout << "INCONSISTENCY - Humidity " << s.top->data.humidity
            << "% is below safe limit of 20%" << endl;
        inconsistent = true;
    }

    // Mark state as unstable if inconsistency found
    if (inconsistent == true) {
        s.top->data.isStable = false;
        cout << endl << "State marked as UNSTABLE." << endl;
        cout << "Recommend rollback to last stable state." << endl;
    }
    else {
        s.top->data.isStable = true;
        cout << "No inconsistency detected. State is STABLE." << endl;
    }
}

// ============================================================
// clearStack()
// Removes all states from stack and frees memory
// Time Complexity: O(n)
// ============================================================
void clearStack(Stack& s) {

    if (s.top == NULL) {
        cout << endl << "Stack is already empty." << endl;
        return;
    }

    int count = 0;

    while (s.top != NULL) {
        StackNode* toDelete = s.top;
        s.top = s.top->next;
        delete toDelete;
        count++;
    }

    s.size = 0;
    cout << endl << "Stack cleared. " << count << " state(s) removed." << endl;
}