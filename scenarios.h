#pragma once
// ============================================================
// scenarios.h
// Scenario-Based System Evaluation
// Five complete forest simulation scenarios
// Each scenario demonstrates multiple data structures
// working together
// ============================================================

#ifndef SCENARIOS_H
#define SCENARIOS_H

#include <iostream>
#include "arrays.h"
#include "linkedlist.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"
#include "graph.h"
#include "hashtable.h"
#include "monitor.h"
using namespace std;

// ============================================================
// FUNCTION DECLARATIONS
// ============================================================

// Scenario 1: Fire starts in Zone 3 and spreads
// Uses: Arrays, Stack, Queue, Graph, Tree
void scenario1_CascadingFire();

// Scenario 2: Sensors fail in Zone 2, system reconstructs
// Uses: Arrays, LinkedList, Stack
void scenario2_SensorFailure();

// Scenario 3: Multiple anomalies detected simultaneously
// Uses: Arrays, Tree, Queue, LinkedList
void scenario3_MultiFactorAnomaly();

// Scenario 4: System overloaded, load redistributed
// Uses: Queue, Stack, Monitor
void scenario4_SystemOverload();

// Scenario 5: Global emergency across all zones
// Uses: All departments
void scenario5_GlobalEmergency();

// Run all 5 scenarios back to back
void runFullSimulation();

// Helper: print scenario header
void printScenarioHeader(int num, const char* title);

// Helper: print separator line
void printSeparator();

#endif