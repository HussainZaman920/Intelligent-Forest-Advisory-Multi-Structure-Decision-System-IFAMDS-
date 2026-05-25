#pragma once
// ============================================================
// monitor.h
// Department 8: System Monitoring and Adaptive
//               Optimization Layer
// Tracks latency, load, bottlenecks, and system health
// across all departments
// ============================================================

#ifndef MONITOR_H
#define MONITOR_H

#include <iostream>
using namespace std;

// ============================================================
// CONSTANTS
// ============================================================

const int NUM_MODULES = 7;   // number of system modules
const int MAX_LATENCY_LOG = 50;  // max latency records

// ============================================================
// MODULE NAMES
// Index maps to department
// ============================================================
// 0 = Arrays
// 1 = Linked Lists
// 2 = Stack
// 3 = Queue
// 4 = Tree
// 5 = Graph
// 6 = Hash Table
// ============================================================

// ============================================================
// LATENCY RECORD
// Stores one operation timing entry
// ============================================================

struct LatencyRecord {
    int   moduleIndex;   // which module was measured
    float startTime;     // simulated start time
    float endTime;       // simulated end time
    float latency;       // endTime - startTime
    char  operationName[30]; // name of operation measured
};

// ============================================================
// MODULE LOAD
// Tracks workload for one module
// ============================================================

struct ModuleLoad {
    char  moduleName[20];   // name of module
    int   activeTasks;      // current active tasks
    int   capacity;         // max tasks this module can handle
    float loadPercentage;   // activeTasks / capacity * 100
    bool  isOverloaded;     // true if load > 80%
};

// ============================================================
// SYSTEM MONITOR STRUCTURE
// Holds all monitoring data
// ============================================================

struct SystemMonitor {
    ModuleLoad   modules[NUM_MODULES];   // load per module
    LatencyRecord latencyLog[MAX_LATENCY_LOG]; // latency history
    int          latencyCount;           // number of records
    float        totalSystemLoad;        // average load across all
    bool         bottleneckDetected;     // any module overloaded
    int          bottleneckModule;       // index of slowest module
};

// ============================================================
// FUNCTION DECLARATIONS
// ============================================================

// Initialize system monitor
// Time Complexity: O(n) where n = NUM_MODULES
void initMonitor(SystemMonitor& sm);

// Log a latency measurement for an operation
// Time Complexity: O(1)
void logLatency(SystemMonitor& sm, int moduleIndex, float start, float end, const char* opName);

// Display all latency records
// Time Complexity: O(n)
void displayLatencyLog(SystemMonitor& sm);

// Update load for a specific module
// Time Complexity: O(1)
void updateModuleLoad(SystemMonitor& sm, int moduleIndex, int activeTasks);

// Display load for all modules
// Time Complexity: O(n)
void displaySystemLoad(SystemMonitor& sm);

// Detect which module is the bottleneck
// Time Complexity: O(n)
void detectBottleneck(SystemMonitor& sm);

// Optimize performance by redistributing load
// Time Complexity: O(n)
void optimizePerformance(SystemMonitor& sm);

// Display overall system health report
// Time Complexity: O(n)
void displaySystemHealth(SystemMonitor& sm);

// Simulate adding tasks to a module
// Time Complexity: O(1)
void simulateLoad(SystemMonitor& sm, int moduleIndex, int tasks);

#endif

