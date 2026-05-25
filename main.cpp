//Mehza Ayesh 24i-2573 AI-B
#include <iostream>
#include "arrays.h"
#include "linkedlist.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"
#include "graph.h"
#include "hashtable.h"
#include "monitor.h"
#include "scenarios.h"
using namespace std;
// ============================================================
// DEPARTMENT 1: Arrays
// ============================================================

void inputEnvironmentalData() {
    int choice;
    cout << endl << "--- Input Environmental Data ---" << endl;
    cout << "1.1 Add Sensor Reading (Temperature, Smoke, Wind)" << endl;
    cout << "1.2 Store Data in Dynamic Array (auto on add)" << endl;
    cout << "1.3 Compare with Static Baseline" << endl;
    cout << "1.4 Validate and Filter Noise" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        float temp, smoke, humidity, wind;
        cout << "Enter Temperature (C)  : "; cin >> temp;
        cout << "Enter Smoke Level      : "; cin >> smoke;
        cout << "Enter Humidity (%)     : "; cin >> humidity;
        cout << "Enter Wind Speed (km/h): "; cin >> wind;
        addSensorReading(temp, smoke, humidity, wind);
    }
    else if (choice == 2) {
        cout << endl << "Data is stored automatically when you add a sensor reading." << endl;
        cout << "Total readings stored: " << getReadingCount() << endl;
    }
    else if (choice == 3) {
        compareWithBaseline();
    }
    else if (choice == 4) {
        validateAndFilterNoise();
    }
    else {
        cout << "Invalid choice." << endl;
    }
}

void viewForestGrid() {
    int choice;
    cout << endl << "--- View Forest Grid Status ---" << endl;
    cout << "2.1 Display 1D Time Series Data" << endl;
    cout << "2.2 Display 2D Forest Zone Matrix" << endl;
    cout << "2.3 View Zone-wise Conditions" << endl;
    cout << "2.4 Update a Zone in Grid" << endl;
    cout << "2.5 Spatial Interpolation (Estimate Missing Zone)" << endl;
    cout << "2.6 Boundary Detection" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        display1DTimeSeries();
    }
    else if (choice == 2) {
        display2DForestGrid();
    }
    else if (choice == 3) {
        displayZoneConditions();
    }
    else if (choice == 4) {
        int row, col;
        float t, s;
        cout << "Enter row (0-2)        : "; cin >> row;
        cout << "Enter col (0-2)        : "; cin >> col;
        cout << "Enter Temperature (C)  : "; cin >> t;
        cout << "Enter Smoke Level      : "; cin >> s;
        updateGrid(row, col, t, s);
    }
    else if (choice == 5) {
        int row, col;
        cout << "Enter row (0-2): "; cin >> row;
        cout << "Enter col (0-2): "; cin >> col;
        spatialInterpolation(row, col);
    }
    else if (choice == 6) {
        boundaryDetection();
    }
    else {
        cout << "Invalid choice." << endl;
    }
}

// ============================================================
// DEPARTMENT 2: Linked Lists
// ============================================================

// Global linked list instances (used across menu options)
SinglyList  rawStream;
SinglyList  verifiedStream;
SinglyList  anomalyStream;
DoublyList  correctionChain;
CircularList monitorLoop;
bool listsInitialized = false;

void initializeLists() {
    if (listsInitialized == false) {
        initSingly(rawStream);
        initSingly(verifiedStream);
        initSingly(anomalyStream);
        initDoubly(correctionChain);
        initCircular(monitorLoop);
        listsInitialized = true;
    }
}

void eventMemorySystem() {
    initializeLists();

    int choice;
    cout << endl << "--- Event Memory System ---" << endl;
    cout << "3.1 Store Event (Singly - Raw Stream)" << endl;
    cout << "3.2 Traverse Event History Forward" << endl;
    cout << "3.3 Traverse Event History Backward" << endl;
    cout << "3.4 Circular Event Monitoring" << endl;
    cout << "3.5 Restore Last Stable State" << endl;
    cout << "3.6 Store Verified Event (Doubly List)" << endl;
    cout << "3.7 Correct Last Event" << endl;
    cout << "3.8 Search Event by Zone" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        float value;
        int   time, zone;
        cout << "Enter sensor value : "; cin >> value;
        cout << "Enter time step    : "; cin >> time;
        cout << "Enter zone number  : "; cin >> zone;
        insertSingly(rawStream, value, time, zone);
    }
    else if (choice == 2) {
        traverseSingly(rawStream);
    }
    else if (choice == 3) {
        traverseDoublyBackward(correctionChain);
    }
    else if (choice == 4) {
        if (monitorLoop.size == 0) {
            cout << endl << "No events in monitor loop. Adding current raw events..." << endl;
            // Copy raw stream events into circular list for monitoring
            EventNode* current = rawStream.head;
            while (current != NULL) {
                insertCircular(monitorLoop, current->value, current->time, current->zone);
                current = current->next;
            }
        }
        int cycles;
        cout << "Enter number of monitoring cycles: "; cin >> cycles;
        monitorCircular(monitorLoop, cycles);
    }
    else if (choice == 5) {
        restoreLastStableState(rawStream, verifiedStream);
    }
    else if (choice == 6) {
        float value;
        int   time, zone;
        cout << "Enter sensor value : "; cin >> value;
        cout << "Enter time step    : "; cin >> time;
        cout << "Enter zone number  : "; cin >> zone;
        insertDoubly(correctionChain, value, time, zone);
        insertSingly(verifiedStream, value, time, zone);
    }
    else if (choice == 7) {
        float newVal;
        cout << "Enter corrected value: "; cin >> newVal;
        correctLastEvent(correctionChain, newVal);
    }
    else if (choice == 8) {
        int zone;
        cout << "Enter zone number to search: "; cin >> zone;
        searchSingly(rawStream, zone);
    }
    else {
        cout << "Invalid choice." << endl;
    }
}

// ============================================================
// DEPARTMENT 3: Stack
// ============================================================

// Global stack instance
Stack systemStack;
bool  stackInitialized = false;

void initializeStack() {
    if (stackInitialized == false) {
        initStack(systemStack);
        stackInitialized = true;
    }
}

void fireDetectionControl() {
    initializeStack();

    int choice;
    cout << endl << "--- Fire Detection and Control (Stack) ---" << endl;
    cout << "4.1 Save Current System State" << endl;
    cout << "4.2 View Current State (Peek)" << endl;
    cout << "4.3 Rollback to Last Stable State" << endl;
    cout << "4.4 Check State for Inconsistency" << endl;
    cout << "4.5 View All Saved States" << endl;
    cout << "4.6 Remove Top State (Pop)" << endl;
    cout << "4.7 Clear All States" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        float temp, smoke, humidity;
        int   zone, timeStep;
        int   stableInput;
        bool  stable;
        cout << "Enter Temperature (C)  : "; cin >> temp;
        cout << "Enter Smoke Level      : "; cin >> smoke;
        cout << "Enter Humidity (%)     : "; cin >> humidity;
        cout << "Enter Zone Number      : "; cin >> zone;
        cout << "Enter Time Step        : "; cin >> timeStep;
        cout << "Is this state stable? (1=Yes 0=No): "; cin >> stableInput;
        if (stableInput == 1) {
            stable = true;
        }
        else {
            stable = false;
        }
        pushState(systemStack, temp, smoke, humidity, zone, timeStep, stable);
    }
    else if (choice == 2) {
        peekState(systemStack);
    }
    else if (choice == 3) {
        rollbackToStable(systemStack);
    }
    else if (choice == 4) {
        checkInconsistency(systemStack);
    }
    else if (choice == 5) {
        displayAllStates(systemStack);
    }
    else if (choice == 6) {
        popState(systemStack);
    }
    else if (choice == 7) {
        clearStack(systemStack);
    }
    else {
        cout << "Invalid choice." << endl;
    }
}

// ============================================================
// DEPARTMENT 4: Queues
// ============================================================

// Global queue instances
Queue routineQueue;
Queue surveillanceQueue;
Queue emergencyQueue;
Queue multiFactorQueue;
bool  queuesInitialized = false;
int   taskCounter = 1;

void initializeQueues() {
    if (queuesInitialized == false) {
        initQueue(routineQueue);
        initQueue(surveillanceQueue);
        initQueue(emergencyQueue);
        initQueue(multiFactorQueue);
        queuesInitialized = true;
    }
}

void taskSchedulingSystem() {
    initializeQueues();

    int choice;
    cout << endl << "--- Task Scheduling System ---" << endl;
    cout << "5.1  Add Routine Task (Q1)" << endl;
    cout << "5.2  Add Surveillance Task (Q2)" << endl;
    cout << "5.3  Add Emergency Task (Q3)" << endl;
    cout << "5.4  Add Multi-Factor Task (Q4)" << endl;
    cout << "5.5  Process All Routine Tasks" << endl;
    cout << "5.6  Process All Emergency Tasks" << endl;
    cout << "5.7  View Queue Contents" << endl;
    cout << "5.8  Pause a Task" << endl;
    cout << "5.9  Resume a Task" << endl;
    cout << "5.10 Priority Switch (Emergency to Front)" << endl;
    cout << "5.11 Load Balance Q1 and Q2" << endl;
    cout << "5.12 View Total Tasks Across All Queues" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        int   zone;
        float value;
        cout << "Enter Zone  : "; cin >> zone;
        cout << "Enter Value : "; cin >> value;
        enqueue(routineQueue, taskCounter++, zone, value, 1, "routine");
    }
    else if (choice == 2) {
        int   zone;
        float value;
        cout << "Enter Zone  : "; cin >> zone;
        cout << "Enter Value : "; cin >> value;
        enqueue(surveillanceQueue, taskCounter++, zone, value, 2, "surveillance");
    }
    else if (choice == 3) {
        int   zone;
        float value;
        cout << "Enter Zone  : "; cin >> zone;
        cout << "Enter Value : "; cin >> value;
        enqueue(emergencyQueue, taskCounter++, zone, value, 4, "emergency");
    }
    else if (choice == 4) {
        int   zone;
        float value;
        cout << "Enter Zone  : "; cin >> zone;
        cout << "Enter Value : "; cin >> value;
        enqueue(multiFactorQueue, taskCounter++, zone, value, 3, "multifactor");
    }
    else if (choice == 5) {
        processAllTasks(routineQueue);
    }
    else if (choice == 6) {
        processAllTasks(emergencyQueue);
    }
    else if (choice == 7) {
        int qChoice;
        cout << "Which queue? (1=Routine 2=Surveillance 3=Emergency 4=MultiFacto): ";
        cin >> qChoice;
        if (qChoice == 1) {
            displayQueue(routineQueue);
        }
        else if (qChoice == 2) {
            displayQueue(surveillanceQueue);
        }
        else if (qChoice == 3) {
            displayQueue(emergencyQueue);
        }
        else if (qChoice == 4) {
            displayQueue(multiFactorQueue);
        }
        else {
            cout << "Invalid queue choice." << endl;
        }
    }
    else if (choice == 8) {
        int taskID;
        cout << "Enter Task ID to pause: "; cin >> taskID;
        pauseTask(routineQueue, taskID);
    }
    else if (choice == 9) {
        int taskID;
        cout << "Enter Task ID to resume: "; cin >> taskID;
        resumeTask(routineQueue, taskID);
    }
    else if (choice == 10) {
        prioritySwitch(routineQueue, emergencyQueue);
    }
    else if (choice == 11) {
        loadBalance(routineQueue, surveillanceQueue);
    }
    else if (choice == 12) {
        int total = getTotalTasks(routineQueue, surveillanceQueue, emergencyQueue, multiFactorQueue);
        cout << endl << "Total tasks across all queues: " << total << endl;
        cout << "Routine Queue     : " << routineQueue.size << endl;
        cout << "Surveillance Queue: " << surveillanceQueue.size << endl;
        cout << "Emergency Queue   : " << emergencyQueue.size << endl;
        cout << "Multi-Factor Queue: " << multiFactorQueue.size << endl;
    }
    else {
        cout << "Invalid choice." << endl;
    }
}

// ============================================================
// DEPARTMENT 5: Trees
// ============================================================

// Global tree instances
Tree         zoneTree;
ResourceTree resourceTree;
bool         treesInitialized = false;

void initializeTrees() {
    if (treesInitialized == false) {
        initTree(zoneTree);
        initResourceTree(resourceTree);
        treesInitialized = true;
    }
}

void decisionSystem() {
    initializeTrees();

    int choice;
    cout << endl << "--- Decision System ---" << endl;
    cout << "6.1  Compute Risk Score" << endl;
    cout << "6.2  Add Zone to Tree" << endl;
    cout << "6.3  Display All Zones (Inorder)" << endl;
    cout << "6.4  Display Tree Structure" << endl;
    cout << "6.5  Search Zone by ID" << endl;
    cout << "6.6  Local Zone Decision" << endl;
    cout << "6.7  Regional Decision" << endl;
    cout << "6.8  Global Emergency Decision" << endl;
    cout << "6.9  Update Zone Conditions" << endl;
    cout << "6.10 Execute Final Action" << endl;
    cout << "6.11 Add Resource" << endl;
    cout << "6.12 Display All Resources" << endl;
    cout << "6.13 Check Resource Availability" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        computeRiskScore();
    }
    else if (choice == 2) {
        int   zoneID;
        char  name[30];
        float temp, smoke, humidity;
        cout << "Enter Zone ID     : "; cin >> zoneID;
        cout << "Enter Zone Name   : "; cin >> name;
        cout << "Enter Temperature : "; cin >> temp;
        cout << "Enter Smoke Level : "; cin >> smoke;
        cout << "Enter Humidity    : "; cin >> humidity;
        zoneTree.root = insertZone(zoneTree.root, zoneID, name, temp, smoke, humidity);
        zoneTree.size++;
    }
    else if (choice == 3) {
        if (zoneTree.root == NULL) {
            cout << endl << "Zone tree is empty. Add zones first." << endl;
        }
        else {
            cout << endl << "--- All Zones (Inorder) ---" << endl;
            inorderDisplay(zoneTree.root);
        }
    }
    else if (choice == 4) {
        if (zoneTree.root == NULL) {
            cout << endl << "Zone tree is empty. Add zones first." << endl;
        }
        else {
            cout << endl << "--- Tree Structure ---" << endl;
            displayTreeStructure(zoneTree.root, 0);
        }
    }
    else if (choice == 5) {
        int zoneID;
        cout << "Enter Zone ID to search: "; cin >> zoneID;
        TreeNode* found = searchZone(zoneTree.root, zoneID);
        if (found == NULL) {
            cout << endl << "Zone " << zoneID << " not found." << endl;
        }
        else {
            cout << endl << "Zone found!" << endl;
            cout << "Zone ID   : " << found->zoneID << endl;
            cout << "Zone Name : " << found->zoneName << endl;
            cout << "Temp      : " << found->temperature << "C" << endl;
            cout << "Smoke     : " << found->smoke << endl;
            cout << "Risk      : " << found->riskScore << endl;
        }
    }
    else if (choice == 6) {
        int zoneID;
        cout << "Enter Zone ID: "; cin >> zoneID;
        TreeNode* found = searchZone(zoneTree.root, zoneID);
        localZoneDecision(found);
    }
    else if (choice == 7) {
        if (zoneTree.root == NULL) {
            cout << endl << "Zone tree is empty." << endl;
        }
        else {
            cout << endl << "--- Regional Decision ---" << endl;
            regionalDecision(zoneTree.root);
        }
    }
    else if (choice == 8) {
        if (zoneTree.root == NULL) {
            cout << endl << "Zone tree is empty." << endl;
        }
        else {
            globalEmergencyDecision(zoneTree.root);
        }
    }
    else if (choice == 9) {
        int   zoneID;
        float temp, smoke, humidity;
        cout << "Enter Zone ID     : "; cin >> zoneID;
        cout << "Enter Temperature : "; cin >> temp;
        cout << "Enter Smoke Level : "; cin >> smoke;
        cout << "Enter Humidity    : "; cin >> humidity;
        updateZoneConditions(zoneTree.root, zoneID, temp, smoke, humidity);
    }
    else if (choice == 10) {
        float riskScore;
        int   zone;
        cout << "Enter Risk Score (0-1) : "; cin >> riskScore;
        cout << "Enter Zone Number      : "; cin >> zone;
        executeFinalAction(riskScore, zone);
    }
    else if (choice == 11) {
        int   id;
        char  name[30];
        float available, required;
        cout << "Enter Resource ID       : "; cin >> id;
        cout << "Enter Resource Name     : "; cin >> name;
        cout << "Enter Available Amount  : "; cin >> available;
        cout << "Enter Required Amount   : "; cin >> required;
        resourceTree.root = insertResource(resourceTree.root, id, name, available, required);
        resourceTree.size++;
    }
    else if (choice == 12) {
        if (resourceTree.root == NULL) {
            cout << endl << "Resource tree is empty." << endl;
        }
        else {
            cout << endl << "--- All Resources ---" << endl;
            displayResources(resourceTree.root);
        }
    }
    else if (choice == 13) {
        if (resourceTree.root == NULL) {
            cout << endl << "Resource tree is empty." << endl;
        }
        else {
            cout << endl << "--- Resource Availability Check ---" << endl;
            checkResourceAvailability(resourceTree.root);
        }
    }
    else {
        cout << "Invalid choice." << endl;
    }
}

// ============================================================
// DEPARTMENT 6: Graph
// ============================================================

// Global graph instances
AdjListGraph   adjListGraph;
AdjMatrixGraph adjMatrixGraph;
bool           graphsInitialized = false;

void initializeGraphs() {
    if (graphsInitialized == false) {
        initAdjListGraph(adjListGraph, MAX_GRAPH_ZONES);
        initAdjMatrixGraph(adjMatrixGraph, MAX_GRAPH_ZONES);
        graphsInitialized = true;
    }
}

void spatialRoutingSystem() {
    initializeGraphs();

    int choice;
    cout << endl << "--- Spatial Routing System ---" << endl;
    cout << "7.1  Load Graph (Adjacency List)" << endl;
    cout << "7.2  Load Graph (Adjacency Matrix)" << endl;
    cout << "7.3  Display Adjacency List" << endl;
    cout << "7.4  Display Adjacency Matrix" << endl;
    cout << "7.5  BFS Traversal (Fire Spread)" << endl;
    cout << "7.6  DFS Traversal (Deep Analysis)" << endl;
    cout << "7.7  Compute Safe Path" << endl;
    cout << "7.8  Update Blocked Routes (Fire Level)" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        int   from, to;
        float distance, danger;
        cout << "Enter From Zone   : "; cin >> from;
        cout << "Enter To Zone     : "; cin >> to;
        cout << "Enter Distance    : "; cin >> distance;
        cout << "Enter Danger Level: "; cin >> danger;
        addEdgeList(adjListGraph, from, to, distance, danger);
    }
    else if (choice == 2) {
        int   from, to;
        float cost;
        cout << "Enter From Zone: "; cin >> from;
        cout << "Enter To Zone  : "; cin >> to;
        cout << "Enter Cost     : "; cin >> cost;
        addEdgeMatrix(adjMatrixGraph, from, to, cost);
    }
    else if (choice == 3) {
        displayAdjList(adjListGraph);
    }
    else if (choice == 4) {
        displayAdjMatrix(adjMatrixGraph);
    }
    else if (choice == 5) {
        int startZone;
        cout << "Enter start zone for BFS: "; cin >> startZone;
        BFS(adjListGraph, startZone);
    }
    else if (choice == 6) {
        int startZone;
        cout << "Enter start zone for DFS: "; cin >> startZone;
        bool visited[MAX_GRAPH_ZONES];
        for (int i = 0; i < MAX_GRAPH_ZONES; i++) {
            visited[i] = false;
        }
        cout << endl << "--- DFS Deep Analysis from Zone " << startZone << " ---" << endl;
        DFS(adjListGraph, startZone, visited);
        cout << endl << "DFS complete." << endl;
    }
    else if (choice == 7) {
        int startZone;
        cout << "Enter start zone: "; cin >> startZone;
        computeSafePath(adjListGraph, startZone);
    }
    else if (choice == 8) {
        int   zone;
        float fireLevel;
        cout << "Enter Zone Number : "; cin >> zone;
        cout << "Enter Fire Level  : "; cin >> fireLevel;
        updateBlockedRoutes(adjListGraph, zone, fireLevel);
    }
    else {
        cout << "Invalid choice." << endl;
    }
}

// ============================================================
// DEPARTMENT 7: Hash Table
// ============================================================

// Global hash table and cache instances
HashTable hashTable;
Cache     fastCache;
bool      hashInitialized = false;

void initializeHash() {
    if (hashInitialized == false) {
        initHashTable(hashTable);
        initCache(fastCache);
        hashInitialized = true;
    }
}

void hashFastAccessSystem() {
    initializeHash();

    int choice;
    cout << endl << "--- Hash-Based Fast Access System ---" << endl;
    cout << "8.1  Insert Zone Data (Hash Table)" << endl;
    cout << "8.2  Retrieve Zone Data (O(1) Access)" << endl;
    cout << "8.3  Delete Zone Record" << endl;
    cout << "8.4  Display Hash Table" << endl;
    cout << "8.5  Display Collision Chains" << endl;
    cout << "8.6  Add to Cache" << endl;
    cout << "8.7  Retrieve from Cache" << endl;
    cout << "8.8  Display Cache" << endl;
    cout << "8.9  Clear Cache" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        int   zoneID;
        float temp, smoke, humidity, risk;
        cout << "Enter Zone ID     : "; cin >> zoneID;
        cout << "Enter Temperature : "; cin >> temp;
        cout << "Enter Smoke Level : "; cin >> smoke;
        cout << "Enter Humidity    : "; cin >> humidity;
        cout << "Enter Risk Score  : "; cin >> risk;
        insertRecord(hashTable, zoneID, temp, smoke, humidity, risk);
    }
    else if (choice == 2) {
        int zoneID;
        cout << "Enter Zone ID to retrieve: "; cin >> zoneID;

        // Check cache first
        CacheEntry* cached = getFromCache(fastCache, zoneID);

        if (cached != NULL) {
            cout << endl << "Retrieved from CACHE (fast access):" << endl;
            cout << "Zone ID     : " << cached->data.zoneID << endl;
            cout << "Temperature : " << cached->data.temperature << "C" << endl;
            cout << "Smoke       : " << cached->data.smoke << endl;
            cout << "Humidity    : " << cached->data.humidity << "%" << endl;
            cout << "Risk Score  : " << cached->data.riskScore << endl;
        }
        else {
            // Not in cache - retrieve from hash table
            HashNode* found = retrieveRecord(hashTable, zoneID);

            if (found == NULL) {
                cout << endl << "Zone " << zoneID << " not found." << endl;
            }
            else {
                cout << endl << "Retrieved from HASH TABLE:" << endl;
                cout << "Zone ID     : " << found->data.zoneID << endl;
                cout << "Temperature : " << found->data.temperature << "C" << endl;
                cout << "Smoke       : " << found->data.smoke << endl;
                cout << "Humidity    : " << found->data.humidity << "%" << endl;
                cout << "Risk Score  : " << found->data.riskScore << endl;

                // Store in cache for next time
                updateCache(fastCache, zoneID, found->data);
                cout << "Zone " << zoneID << " added to cache for faster future access." << endl;
            }
        }
    }
    else if (choice == 3) {
        int zoneID;
        cout << "Enter Zone ID to delete: "; cin >> zoneID;
        deleteRecord(hashTable, zoneID);
    }
    else if (choice == 4) {
        displayHashTable(hashTable);
    }
    else if (choice == 5) {
        displayCollisions(hashTable);
    }
    else if (choice == 6) {
        int   zoneID;
        float temp, smoke, humidity, risk;
        cout << "Enter Zone ID     : "; cin >> zoneID;
        cout << "Enter Temperature : "; cin >> temp;
        cout << "Enter Smoke Level : "; cin >> smoke;
        cout << "Enter Humidity    : "; cin >> humidity;
        cout << "Enter Risk Score  : "; cin >> risk;
        ZoneRecord record;
        record.zoneID = zoneID;
        record.temperature = temp;
        record.smoke = smoke;
        record.humidity = humidity;
        record.riskScore = risk;
        updateCache(fastCache, zoneID, record);
    }
    else if (choice == 7) {
        int zoneID;
        cout << "Enter Zone ID to retrieve from cache: "; cin >> zoneID;
        CacheEntry* entry = getFromCache(fastCache, zoneID);
        if (entry == NULL) {
            cout << endl << "Zone " << zoneID << " not found in cache." << endl;
        }
        else {
            cout << endl << "Found in cache!" << endl;
            cout << "Zone ID     : " << entry->data.zoneID << endl;
            cout << "Temperature : " << entry->data.temperature << "C" << endl;
            cout << "Smoke       : " << entry->data.smoke << endl;
            cout << "Humidity    : " << entry->data.humidity << "%" << endl;
            cout << "Risk Score  : " << entry->data.riskScore << endl;
            cout << "Accessed    : " << entry->accessCount << " times" << endl;
        }
    }
    else if (choice == 8) {
        displayCache(fastCache);
    }
    else if (choice == 9) {
        clearCache(fastCache);
    }
    else {
        cout << "Invalid choice." << endl;
    }
}


// ============================================================
// DEPARTMENT 8: System Monitor
// ============================================================

// Global monitor instance
SystemMonitor sysMonitor;
bool          monitorInitialized = false;

void initializeMonitor() {
    if (monitorInitialized == false) {
        initMonitor(sysMonitor);
        monitorInitialized = true;
    }
}

void systemMonitoring() {
    initializeMonitor();

    int choice;
    cout << endl << "--- System Monitoring ---" << endl;
    cout << "9.1  Monitor System Load" << endl;
    cout << "9.2  Log Latency Record" << endl;
    cout << "9.3  Display Latency Log" << endl;
    cout << "9.4  Detect Bottlenecks" << endl;
    cout << "9.5  Optimize Performance" << endl;
    cout << "9.6  View System Health Report" << endl;
    cout << "9.7  Simulate Load on Module" << endl;
    cout << "9.8  Update Module Load Manually" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        displaySystemLoad(sysMonitor);
    }
    else if (choice == 2) {
        int   moduleIndex;
        float start, end;
        char  opName[30];
        cout << "Module Index (0=Arrays 1=LinkedList 2=Stack" << endl;
        cout << "             3=Queue  4=Tree       5=Graph 6=Hash): ";
        cin >> moduleIndex;
        cout << "Enter Operation Name : "; cin >> opName;
        cout << "Enter Start Time (ms): "; cin >> start;
        cout << "Enter End Time (ms)  : "; cin >> end;
        logLatency(sysMonitor, moduleIndex, start, end, opName);
    }
    else if (choice == 3) {
        displayLatencyLog(sysMonitor);
    }
    else if (choice == 4) {
        detectBottleneck(sysMonitor);
    }
    else if (choice == 5) {
        optimizePerformance(sysMonitor);
    }
    else if (choice == 6) {
        displaySystemHealth(sysMonitor);
    }
    else if (choice == 7) {
        int moduleIndex, tasks;
        cout << "Module Index (0=Arrays 1=LinkedList 2=Stack" << endl;
        cout << "             3=Queue  4=Tree       5=Graph 6=Hash): ";
        cin >> moduleIndex;
        cout << "Enter number of tasks to simulate: ";
        cin >> tasks;
        simulateLoad(sysMonitor, moduleIndex, tasks);
    }
    else if (choice == 8) {
        int moduleIndex, activeTasks;
        cout << "Module Index (0=Arrays 1=LinkedList 2=Stack" << endl;
        cout << "             3=Queue  4=Tree       5=Graph 6=Hash): ";
        cin >> moduleIndex;
        cout << "Enter active task count: ";
        cin >> activeTasks;
        updateModuleLoad(sysMonitor, moduleIndex, activeTasks);
    }
    else {
        cout << "Invalid choice." << endl;
    }
}

// ============================================================
// SCENARIOS
// ============================================================

void scenarioSimulation() {
    int choice;
    cout << endl << "--- Scenario Simulation ---" << endl;
    cout << "10.1 Cascading Fire Scenario" << endl;
    cout << "10.2 Sensor Failure Scenario" << endl;
    cout << "10.3 Multi-Factor Anomaly Scenario" << endl;
    cout << "10.4 System Overload Scenario" << endl;
    cout << "10.5 Global Emergency Scenario" << endl;
    cout << "10.6 Run Full System Simulation" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        scenario1_CascadingFire();
    }
    else if (choice == 2) {
        scenario2_SensorFailure();
    }
    else if (choice == 3) {
        scenario3_MultiFactorAnomaly();
    }
    else if (choice == 4) {
        scenario4_SystemOverload();
    }
    else if (choice == 5) {
        scenario5_GlobalEmergency();
    }
    else if (choice == 6) {
        runFullSimulation();
    }
    else {
        cout << "Invalid choice." << endl;
    }
}

// ============================================================
// MAIN MENU
// ============================================================

void showMainMenu() {
    cout << endl;
    cout << "============================================" << endl;
    cout << "   IFAMDS - Forest Management System       " << endl;
    cout << "============================================" << endl;
    cout << "1.  Input Environmental Data" << endl;
    cout << "2.  View Forest Grid Status" << endl;
    cout << "3.  Event Memory System" << endl;
    cout << "4.  Fire Detection and Control" << endl;
    cout << "5.  Task Scheduling System" << endl;
    cout << "6.  Decision System" << endl;
    cout << "7.  Spatial Routing System" << endl;
    cout << "8.  Hash-Based Fast Access System" << endl;
    cout << "9.  System Monitoring" << endl;
    cout << "10. Scenario Simulation" << endl;
    cout << "0.  Exit System" << endl;
    cout << "============================================" << endl;
    cout << "Enter your choice: ";
}

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    int choice;

    cout << "Welcome to IFAMDS - Intelligent Forest Advisory System" << endl;

    do {
        showMainMenu();
        cin >> choice;

        if (choice == 1) {
            inputEnvironmentalData();
        }
        else if (choice == 2) {
            viewForestGrid();
        }
        else if (choice == 3) {
            eventMemorySystem();
        }
        else if (choice == 4) {
            fireDetectionControl();
        }
        else if (choice == 5) {
            taskSchedulingSystem();
        }
        else if (choice == 6) {
            decisionSystem();
        }
        else if (choice == 7) {
            spatialRoutingSystem();
        }
        else if (choice == 8) {
            hashFastAccessSystem();
        }
        else if (choice == 9) {
            systemMonitoring();
        }
        else if (choice == 10) {
            scenarioSimulation();
        }
        else if (choice == 0) {
            cout << endl << "Exiting IFAMDS. Goodbye!" << endl;
        }
        else {
            cout << endl << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}