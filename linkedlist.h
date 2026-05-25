#pragma once
// ============================================================
// linkedlist.h
// Department 2: Linked Data Event Memory Layer
// Handles singly, doubly, and circular linked lists
// for storing forest events as a timeline
// ============================================================

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

// ============================================================
// EVENT NODE STRUCTURE
// Each node stores one forest event
// value = sensor reading, time = when it happened, zone = where
// ============================================================

struct EventNode {
    float  value;       // sensor reading (temperature or smoke)
    int    time;        // time step when event was recorded
    int    zone;        // zone number where event occurred
    EventNode* next;    // pointer to next event (singly + circular)
    EventNode* prev;    // pointer to previous event (doubly only)
};

// ============================================================
// SINGLY LINKED LIST (L1, L2, L3)
// Forward only traversal
// Used for: raw stream, verified stream, anomaly stream
// ============================================================

struct SinglyList {
    EventNode* head;
    int        size;
};

// ============================================================
// DOUBLY LINKED LIST (L4, L5, L6)
// Forward and backward traversal
// Used for: forward correction, backward correction, sync
// ============================================================

struct DoublyList {
    EventNode* head;
    EventNode* tail;
    int        size;
};

// ============================================================
// CIRCULAR LINKED LIST (L7, L8, L9, L10)
// Last node points back to first
// Used for: local monitor, system monitor, emergency, stability
// ============================================================

struct CircularList {
    EventNode* head;
    int        size;
};

// ============================================================
// FUNCTION DECLARATIONS
// ============================================================

// --- Singly Linked List Operations ---

// Initialize singly list
void initSingly(SinglyList& list);

// Insert event at end of singly list
// Time Complexity: O(n)
void insertSingly(SinglyList& list, float value, int time, int zone);

// Traverse singly list forward and print all events
// Time Complexity: O(n)
void traverseSingly(SinglyList& list);

// Delete first node of singly list
// Time Complexity: O(1)
void deleteFrontSingly(SinglyList& list);

// Search for an event by zone in singly list
// Time Complexity: O(n)
void searchSingly(SinglyList& list, int zone);

// --- Doubly Linked List Operations ---

// Initialize doubly list
void initDoubly(DoublyList& list);

// Insert event at end of doubly list
// Time Complexity: O(1) with tail pointer
void insertDoubly(DoublyList& list, float value, int time, int zone);

// Traverse doubly list forward
// Time Complexity: O(n)
void traverseDoublyForward(DoublyList& list);

// Traverse doubly list backward
// Time Complexity: O(n)
void traverseDoublyBackward(DoublyList& list);

// Correct last event value (backward correction)
// Time Complexity: O(1)
void correctLastEvent(DoublyList& list, float newValue);

// --- Circular Linked List Operations ---

// Initialize circular list
void initCircular(CircularList& list);

// Insert event into circular list
// Time Complexity: O(n)
void insertCircular(CircularList& list, float value, int time, int zone);

// Traverse circular list one full loop and print
// Time Complexity: O(n)
void traverseCircular(CircularList& list);

// Simulate continuous monitoring for n cycles
// Time Complexity: O(n * cycles)
void monitorCircular(CircularList& list, int cycles);

// --- Shared Utility ---

// Restore last stable state by removing anomaly events
// Time Complexity: O(n)
void restoreLastStableState(SinglyList& raw, SinglyList& verified);

#endif