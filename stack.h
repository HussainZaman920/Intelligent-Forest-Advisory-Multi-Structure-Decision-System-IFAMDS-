#pragma once
// ============================================================
// stack.h
// Department 3: Execution Control and Computational
//               Reasoning Layer
// Stack is used to save system states and roll back
// to last stable state when inconsistency is detected
// ============================================================

#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

// ============================================================
// SYSTEM STATE STRUCTURE
// Each state stores a snapshot of forest conditions
// at a specific point in time
// ============================================================

struct SystemState {
    float temperature;  // temperature at time of snapshot
    float smoke;        // smoke level at time of snapshot
    float humidity;     // humidity at time of snapshot
    int   zone;         // which zone this state belongs to
    int   timeStep;     // when this state was saved
    bool  isStable;     // whether this state was marked stable
};

// ============================================================
// STACK NODE
// Each node holds one system state
// ============================================================

struct StackNode {
    SystemState data;
    StackNode* next;
};

// ============================================================
// STACK STRUCTURE
// Top pointer and size tracker
// ============================================================

struct Stack {
    StackNode* top;
    int        size;
};

// ============================================================
// FUNCTION DECLARATIONS
// ============================================================

// Initialize stack
// Time Complexity: O(1)
void initStack(Stack& s);

// Push a new system state onto stack
// Time Complexity: O(1)
void pushState(Stack& s, float temp, float smoke, float humidity, int zone, int timeStep, bool stable);

// Pop the top state from stack
// Time Complexity: O(1)
void popState(Stack& s);

// Peek at top state without removing
// Time Complexity: O(1)
void peekState(Stack& s);

// Check if stack is empty
// Time Complexity: O(1)
bool isStackEmpty(Stack& s);

// Display all saved states in stack
// Time Complexity: O(n)
void displayAllStates(Stack& s);

// Rollback to last stable state
// Pops states until a stable one is found
// Time Complexity: O(n)
void rollbackToStable(Stack& s);

// Check for inconsistency in top state
// Flags if values exceed danger thresholds
// Time Complexity: O(1)
void checkInconsistency(Stack& s);

// Clear entire stack
// Time Complexity: O(n)
void clearStack(Stack& s);

#endif
