// ============================================================
// graph.cpp
// Department 6: Spatial Connectivity and Graph-Based
//               Routing Layer
// Implementation of graph operations for forest routing
// ============================================================

#include "graph.h"

// ============================================================
// initAdjListGraph()
// Sets all head pointers to NULL
// Initializes fire levels to 0
// Time Complexity: O(V)
// ============================================================
void initAdjListGraph(AdjListGraph& g, int zoneCount) {
    g.zoneCount = zoneCount;

    for (int i = 0; i < zoneCount; i++) {
        g.heads[i] = NULL;
        g.fireLevel[i] = 0.0;
    }

    cout << endl << "Adjacency list graph initialized." << endl;
    cout << "Zones: " << zoneCount << endl;
}

// ============================================================
// addEdgeList()
// Adds a bidirectional edge between two zones
// Path cost = distance + danger
// Time Complexity: O(1)
// ============================================================
void addEdgeList(AdjListGraph& g, int from, int to, float distance, float danger) {

    if (from < 0 || from >= g.zoneCount || to < 0 || to >= g.zoneCount) {
        cout << endl << "Invalid zone numbers." << endl;
        return;
    }

    float cost = distance + danger;

    // Add edge from -> to
    AdjNode* newNode1 = new AdjNode();
    newNode1->neighborZone = to;
    newNode1->distance = distance;
    newNode1->danger = danger;
    newNode1->pathCost = cost;
    newNode1->isBlocked = false;
    newNode1->next = g.heads[from];
    g.heads[from] = newNode1;

    // Add edge to -> from (undirected graph)
    AdjNode* newNode2 = new AdjNode();
    newNode2->neighborZone = from;
    newNode2->distance = distance;
    newNode2->danger = danger;
    newNode2->pathCost = cost;
    newNode2->isBlocked = false;
    newNode2->next = g.heads[to];
    g.heads[to] = newNode2;

    cout << endl << "Edge added: Zone " << from << " <--> Zone " << to << endl;
    cout << "Distance  : " << distance << endl;
    cout << "Danger    : " << danger << endl;
    cout << "Path Cost : " << cost << endl;
}

// ============================================================
// displayAdjList()
// Prints all zones and their neighbor connections
// Time Complexity: O(V + E)
// ============================================================
void displayAdjList(AdjListGraph& g) {

    cout << endl << "--- Adjacency List Graph ---" << endl;

    for (int i = 0; i < g.zoneCount; i++) {

        cout << "Zone " << i << " --> ";

        if (g.heads[i] == NULL) {
            cout << "No connections" << endl;
            continue;
        }

        AdjNode* current = g.heads[i];

        while (current != NULL) {

            cout << "Zone " << current->neighborZone
                << " (Cost: " << current->pathCost << ")";

            if (current->isBlocked == true) {
                cout << " [BLOCKED]";
            }

            if (current->next != NULL) {
                cout << " --> ";
            }

            current = current->next;
        }

        cout << endl;
    }
}

// ============================================================
// BFS()
// Breadth First Search from starting zone
// Shows how fire spreads level by level to neighbors
// Uses a simple array-based queue
// Time Complexity: O(V + E)
// ============================================================
void BFS(AdjListGraph& g, int startZone) {

    if (startZone < 0 || startZone >= g.zoneCount) {
        cout << endl << "Invalid start zone." << endl;
        return;
    }

    cout << endl << "--- BFS Fire Spread from Zone " << startZone << " ---" << endl;

    // Track visited zones
    bool visited[MAX_GRAPH_ZONES];
    for (int i = 0; i < g.zoneCount; i++) {
        visited[i] = false;
    }

    // Simple array-based queue
    int queue[MAX_GRAPH_ZONES];
    int front = 0;
    int rear = 0;

    // Start BFS from startZone
    visited[startZone] = true;
    queue[rear] = startZone;
    rear++;

    int level = 0;

    while (front < rear) {

        int levelSize = rear - front;

        cout << endl << "Level " << level << " (Fire reaches):" << endl;

        for (int i = 0; i < levelSize; i++) {

            int current = queue[front];
            front++;

            cout << "  Zone " << current;

            if (current == startZone) {
                cout << " [FIRE ORIGIN]" << endl;
            }
            else {
                cout << " [FIRE SPREADING]" << endl;
            }

            // Add unvisited neighbors to queue
            AdjNode* neighbor = g.heads[current];

            while (neighbor != NULL) {

                if (visited[neighbor->neighborZone] == false
                    && neighbor->isBlocked == false) {

                    visited[neighbor->neighborZone] = true;
                    queue[rear] = neighbor->neighborZone;
                    rear++;
                }

                neighbor = neighbor->next;
            }
        }

        level++;
    }

    cout << endl << "BFS complete. Fire spread analysis done." << endl;
}

// ============================================================
// DFS()
// Depth First Search from starting zone
// Follows one path deeply before trying others
// Time Complexity: O(V + E)
// ============================================================
void DFS(AdjListGraph& g, int startZone, bool visited[]) {

    // Mark current zone as visited
    visited[startZone] = true;

    cout << "  Analyzing Zone " << startZone << endl;

    // Visit all unvisited unblocked neighbors
    AdjNode* current = g.heads[startZone];

    while (current != NULL) {

        if (visited[current->neighborZone] == false
            && current->isBlocked == false) {

            cout << "  --> Moving to Zone " << current->neighborZone
                << " (Cost: " << current->pathCost << ")" << endl;

            DFS(g, current->neighborZone, visited);
        }

        current = current->next;
    }
}

// ============================================================
// computeSafePath()
// Finds lowest cost path from start zone to all others
// Uses simple greedy approach (not full Dijkstra)
// Path Cost = Distance + Danger
// Fire-aware: Updated Cost = Distance x (1 + FireLevel)
// Time Complexity: O(V^2)
// ============================================================
void computeSafePath(AdjListGraph& g, int startZone) {

    if (startZone < 0 || startZone >= g.zoneCount) {
        cout << endl << "Invalid start zone." << endl;
        return;
    }

    cout << endl << "--- Safe Path Computation from Zone " << startZone << " ---" << endl;

    float dist[MAX_GRAPH_ZONES];
    bool  visited[MAX_GRAPH_ZONES];

    // Initialize all distances to very large number
    for (int i = 0; i < g.zoneCount; i++) {
        dist[i] = 99999.0;
        visited[i] = false;
    }

    dist[startZone] = 0.0;

    for (int count = 0; count < g.zoneCount; count++) {

        // Find unvisited zone with minimum distance
        int   minZone = -1;
        float minDist = 99999.0;

        for (int i = 0; i < g.zoneCount; i++) {
            if (visited[i] == false && dist[i] < minDist) {
                minDist = dist[i];
                minZone = i;
            }
        }

        if (minZone == -1) {
            break;
        }

        visited[minZone] = true;

        // Update distances for neighbors
        AdjNode* neighbor = g.heads[minZone];

        while (neighbor != NULL) {

            int   to = neighbor->neighborZone;
            float fireCost = 0.0;

            // Fire-aware cost update from project doc
            // Updated Cost = Distance x (1 + FireLevel)
            if (g.fireLevel[to] > 0) {
                fireCost = neighbor->distance * (1.0 + g.fireLevel[to]);
            }
            else {
                fireCost = neighbor->pathCost;
            }

            if (visited[to] == false && dist[minZone] + fireCost < dist[to]) {
                dist[to] = dist[minZone] + fireCost;
            }

            neighbor = neighbor->next;
        }
    }

    // Display results
    cout << "Zone   Safe Path Cost from Zone " << startZone << endl;
    cout << "--------------------------------------" << endl;

    for (int i = 0; i < g.zoneCount; i++) {
        cout << "Zone " << i << "  -->  ";

        if (dist[i] == 99999.0) {
            cout << "Not reachable" << endl;
        }
        else {
            cout << dist[i] << endl;
        }
    }
}

// ============================================================
// updateBlockedRoutes()
// When fire level increases in a zone, increases path cost
// and blocks routes that are too dangerous
// Updated Cost = Distance x (1 + FireLevel)
// Time Complexity: O(E)
// ============================================================
void updateBlockedRoutes(AdjListGraph& g, int zone, float fireLevel) {

    if (zone < 0 || zone >= g.zoneCount) {
        cout << endl << "Invalid zone." << endl;
        return;
    }

    g.fireLevel[zone] = fireLevel;

    cout << endl << "--- Updating Routes for Zone " << zone << " ---" << endl;
    cout << "Fire Level: " << fireLevel << endl;

    // Update all edges connected to this zone
    for (int i = 0; i < g.zoneCount; i++) {

        AdjNode* current = g.heads[i];

        while (current != NULL) {

            if (current->neighborZone == zone) {

                // Fire-aware cost = distance x (1 + fire level)
                float newCost = current->distance * (1.0 + fireLevel);
                current->pathCost = newCost;

                // Block route if fire level is critical
                if (fireLevel > 0.7) {
                    current->isBlocked = true;
                    cout << "Route Zone " << i << " --> Zone " << zone
                        << " BLOCKED (fire level too high)" << endl;
                }
                else {
                    cout << "Route Zone " << i << " --> Zone " << zone
                        << " updated cost: " << newCost << endl;
                }
            }

            current = current->next;
        }
    }
}

// ============================================================
// initAdjMatrixGraph()
// Sets all matrix values to 0
// Time Complexity: O(V^2)
// ============================================================
void initAdjMatrixGraph(AdjMatrixGraph& g, int zoneCount) {
    g.zoneCount = zoneCount;

    for (int i = 0; i < zoneCount; i++) {
        for (int j = 0; j < zoneCount; j++) {
            g.matrix[i][j] = 0;
            g.cost[i][j] = 0.0;
        }
    }

    cout << endl << "Adjacency matrix graph initialized." << endl;
    cout << "Zones: " << zoneCount << endl;
}

// ============================================================
// addEdgeMatrix()
// Adds bidirectional edge in matrix
// Time Complexity: O(1)
// ============================================================
void addEdgeMatrix(AdjMatrixGraph& g, int from, int to, float cost) {

    if (from < 0 || from >= g.zoneCount || to < 0 || to >= g.zoneCount) {
        cout << endl << "Invalid zone numbers." << endl;
        return;
    }

    g.matrix[from][to] = 1;
    g.matrix[to][from] = 1;
    g.cost[from][to] = cost;
    g.cost[to][from] = cost;

    cout << endl << "Matrix edge added: Zone " << from << " <--> Zone " << to << endl;
    cout << "Cost: " << cost << endl;
}

// ============================================================
// displayAdjMatrix()
// Prints the full connection matrix
// Time Complexity: O(V^2)
// ============================================================
void displayAdjMatrix(AdjMatrixGraph& g) {

    cout << endl << "--- Adjacency Matrix ---" << endl;
    cout << "     ";

    for (int i = 0; i < g.zoneCount; i++) {
        cout << "Z" << i << "  ";
    }
    cout << endl;

    for (int i = 0; i < g.zoneCount; i++) {
        cout << "Z" << i << "   ";
        for (int j = 0; j < g.zoneCount; j++) {
            cout << g.matrix[i][j] << "   ";
        }
        cout << endl;
    }

    cout << endl << "--- Cost Matrix ---" << endl;
    cout << "     ";

    for (int i = 0; i < g.zoneCount; i++) {
        cout << "Z" << i << "    ";
    }
    cout << endl;

    for (int i = 0; i < g.zoneCount; i++) {
        cout << "Z" << i << "   ";
        for (int j = 0; j < g.zoneCount; j++) {
            cout << g.cost[i][j] << "  ";
        }
        cout << endl;
    }
}