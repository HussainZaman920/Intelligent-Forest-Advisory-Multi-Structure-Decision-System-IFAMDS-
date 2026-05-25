// ============================================================
// scenarios.cpp
// Scenario-Based System Evaluation
// Five complete forest simulation scenarios
// ============================================================

#include "scenarios.h"

// ============================================================
// printSeparator()
// Prints a divider line for readability
// ============================================================
void printSeparator() {
    cout << "============================================" << endl;
}

// ============================================================
// printScenarioHeader()
// Prints scenario title banner
// ============================================================
void printScenarioHeader(int num, const char* title) {
    cout << endl;
    printSeparator();
    cout << "SCENARIO " << num << ": " << title << endl;
    printSeparator();
}

// ============================================================
// SCENARIO 1: Cascading Fire and Resource Conflict Resolution
// Fire starts in Zone 3, spreads to Zone 4 and Zone 6
// Demonstrates: Arrays, Stack, Queue, Graph, Tree
// ============================================================
void scenario1_CascadingFire() {

    printScenarioHeader(1, "Cascading Fire and Resource Conflict");

    // --------------------------------------------------------
    // STEP 1: Arrays - Collect sensor data from Zone 3
    // --------------------------------------------------------
    cout << endl << "STEP 1: Collecting sensor data from forest zones..." << endl;
    printSeparator();

    // Zone 3 - fire origin (high temp, high smoke)
    addSensorReading(65.0, 85.0, 15.0, 20.0);
    cout << "Zone 3 - Fire origin detected." << endl;

    // Zone 4 - spreading (moderate danger)
    addSensorReading(50.0, 72.0, 18.0, 25.0);
    cout << "Zone 4 - Fire spreading detected." << endl;

    // Zone 6 - monitoring (slight danger)
    addSensorReading(38.0, 45.0, 30.0, 15.0);
    cout << "Zone 6 - Elevated readings detected." << endl;

    // --------------------------------------------------------
    // STEP 2: Arrays - Validate readings and detect anomalies
    // --------------------------------------------------------
    cout << endl << "STEP 2: Validating sensor readings..." << endl;
    printSeparator();
    validateAndFilterNoise();

    // --------------------------------------------------------
    // STEP 3: Stack - Save current stable state before fire
    // --------------------------------------------------------
    cout << endl << "STEP 3: Saving stable state before emergency..." << endl;
    printSeparator();

    Stack fireStack;
    initStack(fireStack);

    // Save pre-fire stable state
    pushState(fireStack, 25.0, 0.0, 60.0, 3, 1, true);
    cout << "Pre-fire stable state saved for Zone 3." << endl;

    // Save current dangerous state
    pushState(fireStack, 65.0, 85.0, 15.0, 3, 2, false);
    cout << "Current fire state pushed as unstable." << endl;

    // --------------------------------------------------------
    // STEP 4: Queue - Schedule emergency response tasks
    // --------------------------------------------------------
    cout << endl << "STEP 4: Scheduling emergency response tasks..." << endl;
    printSeparator();

    Queue fireQueue;
    initQueue(fireQueue);

    enqueue(fireQueue, 101, 3, 65.0, 4, "emergency");
    cout << "Emergency task created for Zone 3." << endl;

    enqueue(fireQueue, 102, 4, 50.0, 3, "emergency");
    cout << "Emergency task created for Zone 4." << endl;

    enqueue(fireQueue, 103, 6, 38.0, 2, "surveillance");
    cout << "Surveillance task created for Zone 6." << endl;

    displayQueue(fireQueue);

    // --------------------------------------------------------
    // STEP 5: Tree - Calculate risk scores and make decisions
    // --------------------------------------------------------
    cout << endl << "STEP 5: Computing risk scores and decisions..." << endl;
    printSeparator();

    Tree fireTree;
    initTree(fireTree);

    fireTree.root = insertZone(fireTree.root, 3, "Zone3", 65.0, 85.0, 15.0);
    fireTree.root = insertZone(fireTree.root, 4, "Zone4", 50.0, 72.0, 18.0);
    fireTree.root = insertZone(fireTree.root, 6, "Zone6", 38.0, 45.0, 30.0);

    cout << endl << "Making local decisions for each zone:" << endl;
    TreeNode* z3 = searchZone(fireTree.root, 3);
    TreeNode* z4 = searchZone(fireTree.root, 4);
    TreeNode* z6 = searchZone(fireTree.root, 6);

    localZoneDecision(z3);
    localZoneDecision(z4);
    localZoneDecision(z6);

    // --------------------------------------------------------
    // STEP 6: Graph - Simulate fire spread using BFS
    // --------------------------------------------------------
    cout << endl << "STEP 6: Simulating fire spread with BFS..." << endl;
    printSeparator();

    AdjListGraph fireGraph;
    initAdjListGraph(fireGraph, 7);

    addEdgeList(fireGraph, 3, 4, 5.0, 3.0);
    addEdgeList(fireGraph, 3, 6, 7.0, 2.0);
    addEdgeList(fireGraph, 4, 5, 4.0, 1.0);
    addEdgeList(fireGraph, 6, 5, 6.0, 1.0);

    BFS(fireGraph, 3);

    // --------------------------------------------------------
    // STEP 7: Stack - Rollback if needed
    // --------------------------------------------------------
    cout << endl << "STEP 7: Rolling back to last stable state..." << endl;
    printSeparator();
    rollbackToStable(fireStack);

    // --------------------------------------------------------
    // STEP 8: Queue - Process all emergency tasks
    // --------------------------------------------------------
    cout << endl << "STEP 8: Processing all emergency tasks..." << endl;
    printSeparator();
    processAllTasks(fireQueue);

    cout << endl << "SCENARIO 1 COMPLETE." << endl;
    cout << "Fire contained. Resources deployed. System stable." << endl;
    printSeparator();
}

// ============================================================
// SCENARIO 2: Sensor Failure and System Reconstruction
// Zone 2 sensors fail, system reconstructs from history
// Demonstrates: Arrays, LinkedList, Stack
// ============================================================
void scenario2_SensorFailure() {

    printScenarioHeader(2, "Sensor Failure and System Reconstruction");

    // --------------------------------------------------------
    // STEP 1: LinkedList - Store valid historical events
    // --------------------------------------------------------
    cout << endl << "STEP 1: Loading historical event data for Zone 2..." << endl;
    printSeparator();

    SinglyList rawList;
    SinglyList verifiedList;
    initSingly(rawList);
    initSingly(verifiedList);

    // Store past valid readings
    insertSingly(verifiedList, 25.0, 1, 2);
    insertSingly(verifiedList, 26.0, 2, 2);
    insertSingly(verifiedList, 27.0, 3, 2);
    cout << "Historical verified events loaded for Zone 2." << endl;

    // --------------------------------------------------------
    // STEP 2: Arrays - Receive bad sensor readings
    // --------------------------------------------------------
    cout << endl << "STEP 2: Receiving faulty sensor readings..." << endl;
    printSeparator();

    // Bad readings from failed sensors
    addSensorReading(-5.0, -1.0, 110.0, 0.0);
    cout << "Bad reading 1 received (negative values - sensor failure)." << endl;

    addSensorReading(999.0, 999.0, 0.0, 0.0);
    cout << "Bad reading 2 received (impossible values - sensor failure)." << endl;

    // --------------------------------------------------------
    // STEP 3: Arrays - Validate and flag bad readings
    // --------------------------------------------------------
    cout << endl << "STEP 3: Validating readings - detecting failures..." << endl;
    printSeparator();
    validateAndFilterNoise();

    // --------------------------------------------------------
    // STEP 4: Stack - Save last known good state
    // --------------------------------------------------------
    cout << endl << "STEP 4: Saving last known stable state..." << endl;
    printSeparator();

    Stack recoveryStack;
    initStack(recoveryStack);

    pushState(recoveryStack, 27.0, 5.0, 58.0, 2, 3, true);
    cout << "Last stable state of Zone 2 saved." << endl;

    // Simulate failed state
    pushState(recoveryStack, -5.0, -1.0, 110.0, 2, 4, false);
    cout << "Faulty state pushed as unstable." << endl;

    // --------------------------------------------------------
    // STEP 5: Stack - Rollback to stable state
    // --------------------------------------------------------
    cout << endl << "STEP 5: Rolling back to last stable state..." << endl;
    printSeparator();
    rollbackToStable(recoveryStack);

    // --------------------------------------------------------
    // STEP 6: LinkedList - Restore from verified history
    // --------------------------------------------------------
    cout << endl << "STEP 6: Restoring Zone 2 from verified history..." << endl;
    printSeparator();
    restoreLastStableState(rawList, verifiedList);

    // --------------------------------------------------------
    // STEP 7: LinkedList - Add reconstructed readings
    // --------------------------------------------------------
    cout << endl << "STEP 7: Adding reconstructed sensor data..." << endl;
    printSeparator();

    // Estimated values using spatial interpolation logic
    insertSingly(rawList, 27.5, 4, 2);
    insertSingly(rawList, 28.0, 5, 2);
    cout << "Reconstructed readings added to Zone 2 stream." << endl;

    traverseSingly(rawList);

    cout << endl << "SCENARIO 2 COMPLETE." << endl;
    cout << "Zone 2 reconstructed. System operating normally." << endl;
    printSeparator();
}

// ============================================================
// SCENARIO 3: Multi-Factor Anomaly Escalation
// Animal movement + fire risk + human intrusion detected
// Demonstrates: Arrays, Tree, Queue, LinkedList
// ============================================================
void scenario3_MultiFactorAnomaly() {

    printScenarioHeader(3, "Multi-Factor Anomaly Escalation");

    // --------------------------------------------------------
    // STEP 1: Arrays - Collect multi-zone readings
    // --------------------------------------------------------
    cout << endl << "STEP 1: Collecting readings from multiple zones..." << endl;
    printSeparator();

    // Zone with animal movement (moderate temp spike)
    addSensorReading(35.0, 20.0, 45.0, 30.0);
    cout << "Zone A - Unusual animal movement detected." << endl;

    // Zone with fire risk (high temp, high smoke)
    addSensorReading(55.0, 78.0, 17.0, 22.0);
    cout << "Zone B - Fire risk detected." << endl;

    // Zone with human intrusion (moderate readings)
    addSensorReading(30.0, 15.0, 50.0, 10.0);
    cout << "Zone C - Human movement detected." << endl;

    // --------------------------------------------------------
    // STEP 2: LinkedList - Store all anomaly events
    // --------------------------------------------------------
    cout << endl << "STEP 2: Storing anomaly events in linked list..." << endl;
    printSeparator();

    SinglyList anomalyList;
    initSingly(anomalyList);

    insertSingly(anomalyList, 35.0, 1, 7);
    cout << "Animal movement event stored." << endl;

    insertSingly(anomalyList, 55.0, 2, 8);
    cout << "Fire risk event stored." << endl;

    insertSingly(anomalyList, 30.0, 3, 9);
    cout << "Human intrusion event stored." << endl;

    traverseSingly(anomalyList);

    // --------------------------------------------------------
    // STEP 3: Tree - Compute risk for each anomaly zone
    // --------------------------------------------------------
    cout << endl << "STEP 3: Computing risk scores for anomaly zones..." << endl;
    printSeparator();

    Tree anomalyTree;
    initTree(anomalyTree);

    anomalyTree.root = insertZone(anomalyTree.root, 7, "AnimalZone", 35.0, 20.0, 45.0);
    anomalyTree.root = insertZone(anomalyTree.root, 8, "FireZone", 55.0, 78.0, 17.0);
    anomalyTree.root = insertZone(anomalyTree.root, 9, "HumanZone", 30.0, 15.0, 50.0);

    cout << endl << "Regional decision across all anomaly zones:" << endl;
    regionalDecision(anomalyTree.root);

    // --------------------------------------------------------
    // STEP 4: Queue - Schedule responses by priority
    // --------------------------------------------------------
    cout << endl << "STEP 4: Scheduling responses by priority..." << endl;
    printSeparator();

    Queue responseQueue;
    Queue emergQueue;
    initQueue(responseQueue);
    initQueue(emergQueue);

    enqueue(responseQueue, 201, 7, 35.0, 1, "routine");
    cout << "Routine monitoring task for animal zone." << endl;

    enqueue(emergQueue, 202, 8, 55.0, 4, "emergency");
    cout << "Emergency task for fire zone." << endl;

    enqueue(responseQueue, 203, 9, 30.0, 2, "surveillance");
    cout << "Surveillance task for human zone." << endl;

    // Move emergency tasks to front
    prioritySwitch(responseQueue, emergQueue);

    cout << endl << "Final task order after priority switch:" << endl;
    displayQueue(responseQueue);

    // --------------------------------------------------------
    // STEP 5: Arrays - Check boundaries between anomaly zones
    // --------------------------------------------------------
    cout << endl << "STEP 5: Checking boundaries between affected zones..." << endl;
    printSeparator();

    updateGrid(0, 0, 35.0, 20.0);
    updateGrid(0, 1, 55.0, 78.0);
    updateGrid(0, 2, 30.0, 15.0);
    boundaryDetection();

    cout << endl << "SCENARIO 3 COMPLETE." << endl;
    cout << "All anomalies tracked. Responses prioritized." << endl;
    printSeparator();
}

// ============================================================
// SCENARIO 4: System Overload and Load Redistribution
// Too many updates arrive at once, system rebalances
// Demonstrates: Queue, Stack, Monitor
// ============================================================
void scenario4_SystemOverload() {

    printScenarioHeader(4, "System Overload and Load Redistribution");

    // --------------------------------------------------------
    // STEP 1: Queue - Flood system with many tasks
    // --------------------------------------------------------
    cout << endl << "STEP 1: Simulating large number of incoming tasks..." << endl;
    printSeparator();

    Queue overloadQueue;
    Queue backupQueue;
    initQueue(overloadQueue);
    initQueue(backupQueue);

    // Add many tasks to simulate overload
    for (int i = 1; i <= 8; i++) {
        enqueue(overloadQueue, 300 + i, i, 30.0 + i, 2, "routine");
    }

    cout << endl << "Total tasks in queue: " << overloadQueue.size << endl;
    cout << "System is overloaded!" << endl;

    // --------------------------------------------------------
    // STEP 2: Monitor - Detect overload condition
    // --------------------------------------------------------
    cout << endl << "STEP 2: Monitor detecting overload..." << endl;
    printSeparator();

    SystemMonitor overloadMonitor;
    initMonitor(overloadMonitor);

    // Simulate high load on queue module (index 3)
    simulateLoad(overloadMonitor, 3, 85);
    simulateLoad(overloadMonitor, 5, 90);

    detectBottleneck(overloadMonitor);

    // --------------------------------------------------------
    // STEP 3: Stack - Save stable state before rebalancing
    // --------------------------------------------------------
    cout << endl << "STEP 3: Saving system state before rebalancing..." << endl;
    printSeparator();

    Stack overloadStack;
    initStack(overloadStack);

    pushState(overloadStack, 28.0, 10.0, 55.0, 1, 10, true);
    cout << "Stable checkpoint saved before load redistribution." << endl;

    // --------------------------------------------------------
    // STEP 4: Queue - Load balance across queues
    // --------------------------------------------------------
    cout << endl << "STEP 4: Redistributing load across queues..." << endl;
    printSeparator();

    loadBalance(overloadQueue, backupQueue);

    cout << endl << "After load balancing:" << endl;
    cout << "Main Queue size   : " << overloadQueue.size << endl;
    cout << "Backup Queue size : " << backupQueue.size << endl;

    // --------------------------------------------------------
    // STEP 5: Monitor - Optimize performance
    // --------------------------------------------------------
    cout << endl << "STEP 5: Optimizing system performance..." << endl;
    printSeparator();

    optimizePerformance(overloadMonitor);

    // --------------------------------------------------------
    // STEP 6: Queue - Process remaining tasks
    // --------------------------------------------------------
    cout << endl << "STEP 6: Processing remaining tasks..." << endl;
    printSeparator();

    processAllTasks(overloadQueue);
    processAllTasks(backupQueue);

    // --------------------------------------------------------
    // STEP 7: Monitor - Final health check
    // --------------------------------------------------------
    cout << endl << "STEP 7: Final system health check..." << endl;
    printSeparator();

    displaySystemHealth(overloadMonitor);

    cout << endl << "SCENARIO 4 COMPLETE." << endl;
    cout << "Load redistributed. System returned to normal." << endl;
    printSeparator();
}

// ============================================================
// SCENARIO 5: Global Multi-Zone Emergency Synchronization
// Large scale emergency across all zones simultaneously
// Demonstrates: All departments
// ============================================================
void scenario5_GlobalEmergency() {

    printScenarioHeader(5, "Global Multi-Zone Emergency Synchronization");

    // --------------------------------------------------------
    // STEP 1: Arrays - Mass sensor data collection
    // --------------------------------------------------------
    cout << endl << "STEP 1: Collecting emergency readings from all zones..." << endl;
    printSeparator();

    addSensorReading(70.0, 90.0, 10.0, 35.0);
    cout << "Zone 1 - CRITICAL readings." << endl;

    addSensorReading(65.0, 80.0, 12.0, 30.0);
    cout << "Zone 2 - CRITICAL readings." << endl;

    addSensorReading(60.0, 75.0, 15.0, 28.0);
    cout << "Zone 3 - HIGH readings." << endl;

    validateAndFilterNoise();

    // --------------------------------------------------------
    // STEP 2: LinkedList - Store all emergency events
    // --------------------------------------------------------
    cout << endl << "STEP 2: Storing emergency events in memory..." << endl;
    printSeparator();

    SinglyList  emergRaw;
    SinglyList  emergVerified;
    DoublyList  emergCorrection;
    CircularList emergMonitor;

    initSingly(emergRaw);
    initSingly(emergVerified);
    initDoubly(emergCorrection);
    initCircular(emergMonitor);

    insertSingly(emergRaw, 70.0, 1, 1);
    insertSingly(emergRaw, 65.0, 2, 2);
    insertSingly(emergRaw, 60.0, 3, 3);

    insertDoubly(emergCorrection, 70.0, 1, 1);
    insertDoubly(emergCorrection, 65.0, 2, 2);

    insertCircular(emergMonitor, 70.0, 1, 1);
    insertCircular(emergMonitor, 65.0, 2, 2);
    insertCircular(emergMonitor, 60.0, 3, 3);

    cout << "All emergency events stored." << endl;
    traverseSingly(emergRaw);

    // --------------------------------------------------------
    // STEP 3: Stack - Save global stable state
    // --------------------------------------------------------
    cout << endl << "STEP 3: Saving last global stable checkpoint..." << endl;
    printSeparator();

    Stack globalStack;
    initStack(globalStack);

    pushState(globalStack, 25.0, 0.0, 60.0, 0, 0, true);
    pushState(globalStack, 70.0, 90.0, 10.0, 1, 1, false);
    pushState(globalStack, 65.0, 80.0, 12.0, 2, 2, false);

    rollbackToStable(globalStack);

    // --------------------------------------------------------
    // STEP 4: Queue - Emergency task flood
    // --------------------------------------------------------
    cout << endl << "STEP 4: Creating emergency response tasks..." << endl;
    printSeparator();

    Queue globalEmergQueue;
    Queue globalRoutineQueue;
    initQueue(globalEmergQueue);
    initQueue(globalRoutineQueue);

    enqueue(globalEmergQueue, 401, 1, 70.0, 4, "emergency");
    enqueue(globalEmergQueue, 402, 2, 65.0, 4, "emergency");
    enqueue(globalEmergQueue, 403, 3, 60.0, 4, "emergency");
    enqueue(globalRoutineQueue, 404, 4, 25.0, 1, "routine");
    enqueue(globalRoutineQueue, 405, 5, 25.0, 1, "routine");

    prioritySwitch(globalRoutineQueue, globalEmergQueue);

    // --------------------------------------------------------
    // STEP 5: Tree - Global decision making
    // --------------------------------------------------------
    cout << endl << "STEP 5: Running global emergency decision..." << endl;
    printSeparator();

    Tree globalTree;
    initTree(globalTree);

    globalTree.root = insertZone(globalTree.root, 1, "Zone1", 70.0, 90.0, 10.0);
    globalTree.root = insertZone(globalTree.root, 2, "Zone2", 65.0, 80.0, 12.0);
    globalTree.root = insertZone(globalTree.root, 3, "Zone3", 60.0, 75.0, 15.0);
    globalTree.root = insertZone(globalTree.root, 4, "Zone4", 25.0, 5.0, 60.0);
    globalTree.root = insertZone(globalTree.root, 5, "Zone5", 28.0, 8.0, 58.0);

    globalEmergencyDecision(globalTree.root);

    // --------------------------------------------------------
    // STEP 6: Graph - Fire spread across all zones
    // --------------------------------------------------------
    cout << endl << "STEP 6: Mapping fire spread across all zones..." << endl;
    printSeparator();

    AdjListGraph globalGraph;
    initAdjListGraph(globalGraph, 6);

    addEdgeList(globalGraph, 1, 2, 3.0, 4.0);
    addEdgeList(globalGraph, 1, 3, 5.0, 3.0);
    addEdgeList(globalGraph, 2, 4, 4.0, 2.0);
    addEdgeList(globalGraph, 3, 5, 6.0, 1.0);

    updateBlockedRoutes(globalGraph, 1, 0.9);

    BFS(globalGraph, 1);

    // --------------------------------------------------------
    // STEP 7: Hash Table - Index all zone data
    // --------------------------------------------------------
    cout << endl << "STEP 7: Indexing all zone data for fast access..." << endl;
    printSeparator();

    HashTable globalHash;
    initHashTable(globalHash);

    insertRecord(globalHash, 1, 70.0, 90.0, 10.0, 0.9);
    insertRecord(globalHash, 2, 65.0, 80.0, 12.0, 0.8);
    insertRecord(globalHash, 3, 60.0, 75.0, 15.0, 0.75);

    displayHashTable(globalHash);

    // --------------------------------------------------------
    // STEP 8: Monitor - Full system health during emergency
    // --------------------------------------------------------
    cout << endl << "STEP 8: Monitoring system during global emergency..." << endl;
    printSeparator();

    SystemMonitor globalMonitor;
    initMonitor(globalMonitor);

    simulateLoad(globalMonitor, 0, 80);
    simulateLoad(globalMonitor, 1, 75);
    simulateLoad(globalMonitor, 2, 60);
    simulateLoad(globalMonitor, 3, 90);
    simulateLoad(globalMonitor, 4, 85);
    simulateLoad(globalMonitor, 5, 88);
    simulateLoad(globalMonitor, 6, 70);

    detectBottleneck(globalMonitor);
    optimizePerformance(globalMonitor);
    displaySystemHealth(globalMonitor);

    // --------------------------------------------------------
    // STEP 9: Circular Monitor - Continuous zone monitoring
    // --------------------------------------------------------
    cout << endl << "STEP 9: Starting continuous emergency monitoring..." << endl;
    printSeparator();

    monitorCircular(emergMonitor, 2);

    // --------------------------------------------------------
    // STEP 10: Execute final global action
    // --------------------------------------------------------
    cout << endl << "STEP 10: Executing final global action..." << endl;
    printSeparator();

    executeFinalAction(0.85, 0);

    cout << endl << "SCENARIO 5 COMPLETE." << endl;
    cout << "Global emergency handled. All zones synchronized." << endl;
    printSeparator();
}

// ============================================================
// runFullSimulation()
// Runs all 5 scenarios back to back
// ============================================================
void runFullSimulation() {

    cout << endl;
    printSeparator();
    cout << "RUNNING FULL SYSTEM SIMULATION - ALL 5 SCENARIOS" << endl;
    printSeparator();

    scenario1_CascadingFire();
    scenario2_SensorFailure();
    scenario3_MultiFactorAnomaly();
    scenario4_SystemOverload();
    scenario5_GlobalEmergency();

    cout << endl;
    printSeparator();
    cout << "FULL SIMULATION COMPLETE." << endl;
    cout << "All 5 scenarios executed successfully." << endl;
    printSeparator();
}