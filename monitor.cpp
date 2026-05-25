// ============================================================
// monitor.cpp
// Department 8: System Monitoring and Adaptive
//               Optimization Layer
// Implementation of all monitoring operations
// ============================================================

#include "monitor.h"
#include <cstring>

// ============================================================
// initMonitor()
// Sets up all modules with names and default values
// Time Complexity: O(n)
// ============================================================
void initMonitor(SystemMonitor& sm) {

    strcpy_s(sm.modules[0].moduleName, 20, "Arrays");
    strcpy_s(sm.modules[1].moduleName, 20, "LinkedLists");
    strcpy_s(sm.modules[2].moduleName, 20, "Stack");
    strcpy_s(sm.modules[3].moduleName, 20, "Queue");
    strcpy_s(sm.modules[4].moduleName, 20, "Tree");
    strcpy_s(sm.modules[5].moduleName, 20, "Graph");
    strcpy_s(sm.modules[6].moduleName, 20, "HashTable");

    for (int i = 0; i < NUM_MODULES; i++) {
        sm.modules[i].activeTasks = 0;
        sm.modules[i].capacity = 100;
        sm.modules[i].loadPercentage = 0.0;
        sm.modules[i].isOverloaded = false;
    }

    sm.latencyCount = 0;
    sm.totalSystemLoad = 0.0;
    sm.bottleneckDetected = false;
    sm.bottleneckModule = -1;

    cout << endl << "System monitor initialized." << endl;
    cout << "Monitoring " << NUM_MODULES << " modules." << endl;
}

// ============================================================
// logLatency()
// Records timing of one operation
// Latency = Finish Time - Start Time
// Time Complexity: O(1)
// ============================================================
void logLatency(SystemMonitor& sm, int moduleIndex, float start, float end, const char* opName) {

    if (sm.latencyCount >= MAX_LATENCY_LOG) {
        cout << endl << "Latency log is full." << endl;
        return;
    }

    if (moduleIndex < 0 || moduleIndex >= NUM_MODULES) {
        cout << endl << "Invalid module index." << endl;
        return;
    }

    LatencyRecord& record = sm.latencyLog[sm.latencyCount];
    record.moduleIndex = moduleIndex;
    record.startTime = start;
    record.endTime = end;
    record.latency = end - start;

    strcpy_s(record.operationName, 30, opName);

    sm.latencyCount++;

    cout << endl << "Latency logged." << endl;
    cout << "Module    : " << sm.modules[moduleIndex].moduleName << endl;
    cout << "Operation : " << opName << endl;
    cout << "Latency   : " << record.latency << " ms" << endl;
}

// ============================================================
// displayLatencyLog()
// Shows all recorded latency measurements
// Time Complexity: O(n)
// ============================================================
void displayLatencyLog(SystemMonitor& sm) {

    if (sm.latencyCount == 0) {
        cout << endl << "No latency records available." << endl;
        return;
    }

    cout << endl << "--- Latency Log ---" << endl;
    cout << "Total records: " << sm.latencyCount << endl;
    cout << "-------------------" << endl;

    for (int i = 0; i < sm.latencyCount; i++) {
        LatencyRecord& r = sm.latencyLog[i];
        cout << endl << "Record [" << i + 1 << "]:" << endl;
        cout << "  Module    : " << sm.modules[r.moduleIndex].moduleName << endl;
        cout << "  Operation : " << r.operationName << endl;
        cout << "  Start     : " << r.startTime << " ms" << endl;
        cout << "  End       : " << r.endTime << " ms" << endl;
        cout << "  Latency   : " << r.latency << " ms" << endl;

        if (r.latency > 10.0) {
            cout << "  Status    : SLOW - possible bottleneck" << endl;
        }
        else if (r.latency > 5.0) {
            cout << "  Status    : WARNING - above normal" << endl;
        }
        else {
            cout << "  Status    : Normal" << endl;
        }
    }
}

// ============================================================
// updateModuleLoad()
// Updates active task count and recalculates load percentage
// Load = activeTasks / capacity * 100
// Time Complexity: O(1)
// ============================================================
void updateModuleLoad(SystemMonitor& sm, int moduleIndex, int activeTasks) {

    if (moduleIndex < 0 || moduleIndex >= NUM_MODULES) {
        cout << endl << "Invalid module index." << endl;
        return;
    }

    sm.modules[moduleIndex].activeTasks = activeTasks;
    sm.modules[moduleIndex].loadPercentage =
        (float)activeTasks / sm.modules[moduleIndex].capacity * 100.0;

    if (sm.modules[moduleIndex].loadPercentage > 80.0) {
        sm.modules[moduleIndex].isOverloaded = true;
    }
    else {
        sm.modules[moduleIndex].isOverloaded = false;
    }

    cout << endl << "Module load updated." << endl;
    cout << "Module : " << sm.modules[moduleIndex].moduleName << endl;
    cout << "Tasks  : " << activeTasks << endl;
    cout << "Load   : " << sm.modules[moduleIndex].loadPercentage << "%" << endl;

    if (sm.modules[moduleIndex].isOverloaded == true) {
        cout << "Status : OVERLOADED" << endl;
    }
    else {
        cout << "Status : Normal" << endl;
    }
}

// ============================================================
// displaySystemLoad()
// Shows load status for every module
// Time Complexity: O(n)
// ============================================================
void displaySystemLoad(SystemMonitor& sm) {

    cout << endl << "--- System Load Report ---" << endl;
    cout << "--------------------------" << endl;

    float totalLoad = 0.0;

    for (int i = 0; i < NUM_MODULES; i++) {

        cout << endl << "Module [" << i << "] "
            << sm.modules[i].moduleName << endl;
        cout << "  Active Tasks : " << sm.modules[i].activeTasks << endl;
        cout << "  Capacity     : " << sm.modules[i].capacity << endl;
        cout << "  Load         : " << sm.modules[i].loadPercentage << "%" << endl;

        if (sm.modules[i].isOverloaded == true) {
            cout << "  Status       : OVERLOADED" << endl;
        }
        else if (sm.modules[i].loadPercentage > 50.0) {
            cout << "  Status       : Moderate" << endl;
        }
        else {
            cout << "  Status       : Normal" << endl;
        }

        totalLoad += sm.modules[i].loadPercentage;
    }

    sm.totalSystemLoad = totalLoad / NUM_MODULES;

    cout << endl << "Average System Load: " << sm.totalSystemLoad << "%" << endl;
}

// ============================================================
// detectBottleneck()
// Finds module with highest load percentage
// That module is the bottleneck slowing the system
// Time Complexity: O(n)
// ============================================================
void detectBottleneck(SystemMonitor& sm) {

    cout << endl << "--- Bottleneck Detection ---" << endl;

    float maxLoad = 0.0;
    int   maxModule = -1;

    for (int i = 0; i < NUM_MODULES; i++) {
        if (sm.modules[i].loadPercentage > maxLoad) {
            maxLoad = sm.modules[i].loadPercentage;
            maxModule = i;
        }
    }

    if (maxModule == -1) {
        cout << "No modules have any load." << endl;
        return;
    }

    sm.bottleneckModule = maxModule;

    if (maxLoad > 80.0) {
        sm.bottleneckDetected = true;
        cout << "BOTTLENECK DETECTED!" << endl;
        cout << "Module   : " << sm.modules[maxModule].moduleName << endl;
        cout << "Load     : " << maxLoad << "%" << endl;
        cout << "Recommendation: Redistribute tasks from this module." << endl;
    }
    else if (maxLoad > 50.0) {
        sm.bottleneckDetected = false;
        cout << "WARNING - High load detected." << endl;
        cout << "Module   : " << sm.modules[maxModule].moduleName << endl;
        cout << "Load     : " << maxLoad << "%" << endl;
        cout << "Recommendation: Monitor this module closely." << endl;
    }
    else {
        sm.bottleneckDetected = false;
        cout << "No bottleneck detected." << endl;
        cout << "Highest load module: " << sm.modules[maxModule].moduleName << endl;
        cout << "Load               : " << maxLoad << "%" << endl;
        cout << "System is running smoothly." << endl;
    }
}

// ============================================================
// optimizePerformance()
// Reduces load on overloaded modules
// Redistributes tasks to less loaded modules
// Time Complexity: O(n)
// ============================================================
void optimizePerformance(SystemMonitor& sm) {

    cout << endl << "--- Performance Optimization ---" << endl;

    bool anyOptimization = false;

    for (int i = 0; i < NUM_MODULES; i++) {

        if (sm.modules[i].isOverloaded == true) {

            anyOptimization = true;

            cout << endl << "Optimizing Module: "
                << sm.modules[i].moduleName << endl;
            cout << "Current Load: " << sm.modules[i].loadPercentage << "%" << endl;

            // Find least loaded module to redistribute to
            int   minIndex = -1;
            float minLoad = 99999.0;

            for (int j = 0; j < NUM_MODULES; j++) {
                if (j != i && sm.modules[j].loadPercentage < minLoad) {
                    minLoad = sm.modules[j].loadPercentage;
                    minIndex = j;
                }
            }

            if (minIndex != -1) {
                // Transfer half the excess tasks
                int excessTasks = sm.modules[i].activeTasks / 2;

                sm.modules[i].activeTasks -= excessTasks;
                sm.modules[i].loadPercentage =
                    (float)sm.modules[i].activeTasks / sm.modules[i].capacity * 100.0;
                sm.modules[i].isOverloaded =
                    sm.modules[i].loadPercentage > 80.0;

                sm.modules[minIndex].activeTasks += excessTasks;
                sm.modules[minIndex].loadPercentage =
                    (float)sm.modules[minIndex].activeTasks / sm.modules[minIndex].capacity * 100.0;

                cout << "Transferred " << excessTasks << " tasks to "
                    << sm.modules[minIndex].moduleName << endl;
                cout << "New load: " << sm.modules[i].loadPercentage << "%" << endl;
            }
        }
    }

    if (anyOptimization == false) {
        cout << "No optimization needed. All modules running normally." << endl;
    }
    else {
        cout << endl << "Optimization complete." << endl;
    }
}

// ============================================================
// displaySystemHealth()
// Full system health report covering all modules
// Time Complexity: O(n)
// ============================================================
void displaySystemHealth(SystemMonitor& sm) {

    cout << endl << "============================================" << endl;
    cout << "         SYSTEM HEALTH REPORT               " << endl;
    cout << "============================================" << endl;

    int normalCount = 0;
    int warningCount = 0;
    int overloadCount = 0;

    for (int i = 0; i < NUM_MODULES; i++) {

        if (sm.modules[i].isOverloaded == true) {
            overloadCount++;
        }
        else if (sm.modules[i].loadPercentage > 50.0) {
            warningCount++;
        }
        else {
            normalCount++;
        }
    }

    cout << endl << "Module Summary:" << endl;
    cout << "  Normal    : " << normalCount << endl;
    cout << "  Warning   : " << warningCount << endl;
    cout << "  Overloaded: " << overloadCount << endl;

    cout << endl << "Latency Records : " << sm.latencyCount << endl;
    cout << "Total System Load: " << sm.totalSystemLoad << "%" << endl;

    if (sm.bottleneckDetected == true) {
        cout << "Bottleneck Module: "
            << sm.modules[sm.bottleneckModule].moduleName << endl;
    }
    else {
        cout << "Bottleneck       : None detected" << endl;
    }

    cout << endl << "Overall Status: ";

    if (overloadCount > 0) {
        cout << "CRITICAL - " << overloadCount
            << " module(s) overloaded" << endl;
    }
    else if (warningCount > 0) {
        cout << "WARNING - " << warningCount
            << " module(s) under high load" << endl;
    }
    else {
        cout << "HEALTHY - All modules running normally" << endl;
    }

    cout << "============================================" << endl;
}

// ============================================================
// simulateLoad()
// Simulates adding a number of tasks to a module
// Used for testing and demonstration
// Time Complexity: O(1)
// ============================================================
void simulateLoad(SystemMonitor& sm, int moduleIndex, int tasks) {

    if (moduleIndex < 0 || moduleIndex >= NUM_MODULES) {
        cout << endl << "Invalid module index." << endl;
        return;
    }

    sm.modules[moduleIndex].activeTasks += tasks;
    sm.modules[moduleIndex].loadPercentage =
        (float)sm.modules[moduleIndex].activeTasks /
        sm.modules[moduleIndex].capacity * 100.0;

    if (sm.modules[moduleIndex].loadPercentage > 80.0) {
        sm.modules[moduleIndex].isOverloaded = true;
    }
    else {
        sm.modules[moduleIndex].isOverloaded = false;
    }

    cout << endl << "Simulated " << tasks << " tasks on "
        << sm.modules[moduleIndex].moduleName << endl;
    cout << "Total tasks : " << sm.modules[moduleIndex].activeTasks << endl;
    cout << "Load        : " << sm.modules[moduleIndex].loadPercentage << "%" << endl;
}