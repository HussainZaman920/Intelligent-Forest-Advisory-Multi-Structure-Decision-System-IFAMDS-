// ============================================================
// queue.cpp
// Department 4: Task Scheduling and Priority Allocation Layer
// Implementation of all queue operations
// ============================================================

#include "queue.h"
#include <cstring>

// ============================================================
// initQueue()
// Sets front and rear to NULL, size to 0
// Time Complexity: O(1)
// ============================================================
void initQueue(Queue& q) {
    q.front = NULL;
    q.rear = NULL;
    q.size = 0;
}

// ============================================================
// enqueue()
// Creates new task node and adds it to rear of queue
// FIFO - first in first out
// Time Complexity: O(1)
// ============================================================
void enqueue(Queue& q, int taskID, int zone, float value, int priority, const char* type) {

    // Create new node
    QueueNode* newNode = new QueueNode();
    newNode->data.taskID = taskID;
    newNode->data.zone = zone;
    newNode->data.value = value;
    newNode->data.priority = priority;
    newNode->data.isPaused = false;
    newNode->next = NULL;

    // Copy task type string safely
    strcpy_s(newNode->data.type, 20, type);

    // If queue is empty
    if (q.rear == NULL) {
        q.front = newNode;
        q.rear = newNode;
        q.size++;
        cout << endl << "Task added to queue." << endl;
        cout << "Task ID  : " << taskID << endl;
        cout << "Zone     : " << zone << endl;
        cout << "Value    : " << value << endl;
        cout << "Priority : " << priority << endl;
        cout << "Type     : " << type << endl;
        return;
    }

    // Add to rear
    q.rear->next = newNode;
    q.rear = newNode;
    q.size++;

    cout << endl << "Task added to queue." << endl;
    cout << "Task ID  : " << taskID << endl;
    cout << "Zone     : " << zone << endl;
    cout << "Value    : " << value << endl;
    cout << "Priority : " << priority << endl;
    cout << "Type     : " << type << endl;
    cout << "Queue size: " << q.size << endl;
}

// ============================================================
// dequeue()
// Removes task from front of queue
// Time Complexity: O(1)
// ============================================================
void dequeue(Queue& q) {

    if (q.front == NULL) {
        cout << endl << "Queue is empty. Nothing to dequeue." << endl;
        return;
    }

    QueueNode* toDelete = q.front;
    q.front = q.front->next;

    // If queue becomes empty after dequeue
    if (q.front == NULL) {
        q.rear = NULL;
    }

    q.size--;

    cout << endl << "Task processed and removed from queue." << endl;
    cout << "Task ID  : " << toDelete->data.taskID << endl;
    cout << "Zone     : " << toDelete->data.zone << endl;
    cout << "Type     : " << toDelete->data.type << endl;
    cout << "Remaining: " << q.size << endl;

    delete toDelete;
}

// ============================================================
// peekQueue()
// Shows front task without removing it
// Time Complexity: O(1)
// ============================================================
void peekQueue(Queue& q) {

    if (q.front == NULL) {
        cout << endl << "Queue is empty." << endl;
        return;
    }

    cout << endl << "--- Front Task in Queue ---" << endl;
    cout << "Task ID  : " << q.front->data.taskID << endl;
    cout << "Zone     : " << q.front->data.zone << endl;
    cout << "Value    : " << q.front->data.value << endl;
    cout << "Priority : " << q.front->data.priority << endl;
    cout << "Type     : " << q.front->data.type << endl;

    if (q.front->data.isPaused == true) {
        cout << "Status   : PAUSED" << endl;
    }
    else {
        cout << "Status   : ACTIVE" << endl;
    }
}

// ============================================================
// isQueueEmpty()
// Returns true if queue has no elements
// Time Complexity: O(1)
// ============================================================
bool isQueueEmpty(Queue& q) {
    if (q.front == NULL) {
        return true;
    }
    return false;
}

// ============================================================
// displayQueue()
// Prints all tasks in queue from front to rear
// Time Complexity: O(n)
// ============================================================
void displayQueue(Queue& q) {

    if (q.front == NULL) {
        cout << endl << "Queue is empty." << endl;
        return;
    }

    cout << endl << "--- Queue Contents ---" << endl;
    cout << "Total tasks: " << q.size << endl;
    cout << "----------------------" << endl;

    QueueNode* current = q.front;
    int count = 1;

    while (current != NULL) {
        cout << endl << "Task [" << count << "]:" << endl;
        cout << "  Task ID  : " << current->data.taskID << endl;
        cout << "  Zone     : " << current->data.zone << endl;
        cout << "  Value    : " << current->data.value << endl;
        cout << "  Priority : " << current->data.priority << endl;
        cout << "  Type     : " << current->data.type << endl;

        if (current->data.isPaused == true) {
            cout << "  Status   : PAUSED" << endl;
        }
        else {
            cout << "  Status   : ACTIVE" << endl;
        }

        current = current->next;
        count++;
    }
}

// ============================================================
// processAllTasks()
// Processes and removes all tasks from queue one by one
// Skips paused tasks
// Time Complexity: O(n)
// ============================================================
void processAllTasks(Queue& q) {

    if (q.front == NULL) {
        cout << endl << "Queue is empty. No tasks to process." << endl;
        return;
    }

    cout << endl << "--- Processing All Tasks ---" << endl;
    int processed = 0;
    int skipped = 0;

    while (q.front != NULL) {

        if (q.front->data.isPaused == true) {
            cout << "Task [" << q.front->data.taskID << "] is PAUSED - skipping." << endl;
            skipped++;
            q.front = q.front->next;
            continue;
        }

        cout << "Processing Task [" << q.front->data.taskID << "]"
            << "  Zone: " << q.front->data.zone
            << "  Type: " << q.front->data.type
            << "  Value: " << q.front->data.value << endl;

        QueueNode* toDelete = q.front;
        q.front = q.front->next;
        delete toDelete;
        q.size--;
        processed++;
    }

    if (q.front == NULL) {
        q.rear = NULL;
    }

    cout << endl << "Processing complete." << endl;
    cout << "Tasks processed : " << processed << endl;
    cout << "Tasks skipped   : " << skipped << endl;
}

// ============================================================
// pauseTask()
// Finds task by ID and marks it as paused
// Time Complexity: O(n)
// ============================================================
void pauseTask(Queue& q, int taskID) {

    if (q.front == NULL) {
        cout << endl << "Queue is empty." << endl;
        return;
    }

    QueueNode* current = q.front;

    while (current != NULL) {
        if (current->data.taskID == taskID) {
            current->data.isPaused = true;
            cout << endl << "Task [" << taskID << "] paused successfully." << endl;
            return;
        }
        current = current->next;
    }

    cout << endl << "Task [" << taskID << "] not found in queue." << endl;
}

// ============================================================
// resumeTask()
// Finds task by ID and marks it as active again
// Time Complexity: O(n)
// ============================================================
void resumeTask(Queue& q, int taskID) {

    if (q.front == NULL) {
        cout << endl << "Queue is empty." << endl;
        return;
    }

    QueueNode* current = q.front;

    while (current != NULL) {
        if (current->data.taskID == taskID) {
            current->data.isPaused = false;
            cout << endl << "Task [" << taskID << "] resumed successfully." << endl;
            return;
        }
        current = current->next;
    }

    cout << endl << "Task [" << taskID << "] not found in queue." << endl;
}

// ============================================================
// prioritySwitch()
// Moves all emergency tasks to front of routine queue
// Simulates priority-based scheduling
// Time Complexity: O(n)
// ============================================================
void prioritySwitch(Queue& routine, Queue& emergency) {

    if (emergency.front == NULL) {
        cout << endl << "No emergency tasks to switch." << endl;
        return;
    }

    cout << endl << "--- Priority Switch: Emergency tasks moved to front ---" << endl;

    int moved = 0;

    // Move all emergency tasks to front of routine queue
    while (emergency.front != NULL) {

        QueueNode* toMove = emergency.front;
        emergency.front = emergency.front->next;
        emergency.size--;

        // Attach at front of routine queue
        toMove->next = routine.front;
        routine.front = toMove;

        if (routine.rear == NULL) {
            routine.rear = toMove;
        }

        routine.size++;
        moved++;

        cout << "Moved Task [" << toMove->data.taskID << "] to front." << endl;
    }

    emergency.rear = NULL;

    cout << endl << "Priority switch complete." << endl;
    cout << "Tasks moved: " << moved << endl;
}

// ============================================================
// loadBalance()
// Moves half of q1 tasks to q2 if q1 is overloaded
// Time Complexity: O(n)
// ============================================================
void loadBalance(Queue& q1, Queue& q2) {

    if (q1.front == NULL) {
        cout << endl << "Queue 1 is empty. No balancing needed." << endl;
        return;
    }

    int moveCount = q1.size / 2;

    if (moveCount == 0) {
        cout << endl << "Queue 1 has only 1 task. No balancing needed." << endl;
        return;
    }

    cout << endl << "--- Load Balancing ---" << endl;
    cout << "Moving " << moveCount << " tasks from Q1 to Q2." << endl;

    for (int i = 0; i < moveCount; i++) {

        if (q1.front == NULL) {
            break;
        }

        // Take from front of q1
        QueueNode* toMove = q1.front;
        q1.front = q1.front->next;
        q1.size--;

        if (q1.front == NULL) {
            q1.rear = NULL;
        }

        // Add to rear of q2
        toMove->next = NULL;

        if (q2.rear == NULL) {
            q2.front = toMove;
            q2.rear = toMove;
        }
        else {
            q2.rear->next = toMove;
            q2.rear = toMove;
        }

        q2.size++;

        cout << "Moved Task [" << toMove->data.taskID << "] to Q2." << endl;
    }

    cout << endl << "Load balancing complete." << endl;
    cout << "Q1 size now: " << q1.size << endl;
    cout << "Q2 size now: " << q2.size << endl;
}

// ============================================================
// getTotalTasks()
// Returns total number of tasks across all 4 queues
// Time Complexity: O(1)
// ============================================================
int getTotalTasks(Queue& q1, Queue& q2, Queue& q3, Queue& q4) {
    return q1.size + q2.size + q3.size + q4.size;
}