#pragma once
// ============================================================
// queue.h
// Department 4: Task Scheduling and Priority Allocation Layer
// Four queues handle different task types:
// Q1 = Routine, Q2 = Surveillance,
// Q3 = Emergency, Q4 = Multi-Factor
// ============================================================

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

// ============================================================
// TASK STRUCTURE
// Each task represents one unit of work in the system
// ============================================================

struct Task {
    int    taskID;       // unique task identifier
    int    zone;         // which zone this task is for
    float  value;        // sensor value that triggered task
    int    priority;     // 1=low, 2=medium, 3=high, 4=emergency
    bool   isPaused;     // whether task is paused
    char   type[20];     // "routine", "surveillance", "emergency", "multifactor"
};

// ============================================================
// QUEUE NODE
// ============================================================

struct QueueNode {
    Task       data;
    QueueNode* next;
};

// ============================================================
// QUEUE STRUCTURE
// Front = dequeue side, Rear = enqueue side
// ============================================================

struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int        size;
};

// ============================================================
// FUNCTION DECLARATIONS
// ============================================================

// Initialize a queue
// Time Complexity: O(1)
void initQueue(Queue& q);

// Add task to rear of queue (enqueue)
// Time Complexity: O(1)
void enqueue(Queue& q, int taskID, int zone, float value, int priority, const char* type);

// Remove task from front of queue (dequeue)
// Time Complexity: O(1)
void dequeue(Queue& q);

// View front task without removing
// Time Complexity: O(1)
void peekQueue(Queue& q);

// Display all tasks in queue
// Time Complexity: O(n)
void displayQueue(Queue& q);

// Check if queue is empty
// Time Complexity: O(1)
bool isQueueEmpty(Queue& q);

// Process all tasks in queue one by one
// Time Complexity: O(n)
void processAllTasks(Queue& q);

// Pause a task by taskID
// Time Complexity: O(n)
void pauseTask(Queue& q, int taskID);

// Resume a paused task by taskID
// Time Complexity: O(n)
void resumeTask(Queue& q, int taskID);

// Priority switch - move emergency tasks to front
// Time Complexity: O(n)
void prioritySwitch(Queue& routine, Queue& emergency);

// Load balancing - move excess tasks to another queue
// Time Complexity: O(n)
void loadBalance(Queue& q1, Queue& q2);

// Get total task count across all queues
// Time Complexity: O(1)
int getTotalTasks(Queue& q1, Queue& q2, Queue& q3, Queue& q4);

#endif
