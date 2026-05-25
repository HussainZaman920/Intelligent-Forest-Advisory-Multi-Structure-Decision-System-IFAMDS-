#pragma once
// ============================================================
// graph.h
// Department 6: Spatial Connectivity and Graph-Based
//               Routing Layer
// Implements adjacency list, adjacency matrix,
// BFS, DFS, path cost, and blocked route updates
// ============================================================

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;

// ============================================================
// CONSTANTS
// ============================================================

const int MAX_GRAPH_ZONES = 10; // maximum number of forest zones

// ============================================================
// ADJACENCY LIST NODE
// Represents one connection (edge) to a neighbor zone
// ============================================================

struct AdjNode {
    int      neighborZone; // zone this edge connects to
    float    distance;     // physical distance between zones
    float    danger;       // danger level on this path (fire etc)
    float    pathCost;     // total cost = distance + danger
    bool     isBlocked;    // whether this route is blocked
    AdjNode* next;         // next neighbor in list
};

// ============================================================
// ADJACENCY LIST GRAPH
// Each zone has a linked list of its neighbors
// ============================================================

struct AdjListGraph {
    AdjNode* heads[MAX_GRAPH_ZONES]; // head of neighbor list per zone
    int      zoneCount;              // number of zones
    float    fireLevel[MAX_GRAPH_ZONES]; // fire level per zone
};

// ============================================================
// ADJACENCY MATRIX GRAPH
// 2D table showing connections between all zone pairs
// 0 = no connection, 1 = connected
// ============================================================

struct AdjMatrixGraph {
    int   matrix[MAX_GRAPH_ZONES][MAX_GRAPH_ZONES];
    float cost[MAX_GRAPH_ZONES][MAX_GRAPH_ZONES];
    int   zoneCount;
};

// ============================================================
// FUNCTION DECLARATIONS
// ============================================================

// --- Adjacency List Graph ---

// Initialize adjacency list graph
// Time Complexity: O(V) where V = number of zones
void initAdjListGraph(AdjListGraph& g, int zoneCount);

// Add edge between two zones in adjacency list
// Time Complexity: O(1)
void addEdgeList(AdjListGraph& g, int from, int to, float distance, float danger);

// Display adjacency list
// Time Complexity: O(V + E)
void displayAdjList(AdjListGraph& g);

// BFS traversal from a starting zone
// Used for fire spread simulation level by level
// Time Complexity: O(V + E)
void BFS(AdjListGraph& g, int startZone);

// DFS traversal from a starting zone
// Used for deep path analysis
// Time Complexity: O(V + E)
void DFS(AdjListGraph& g, int startZone, bool visited[]);

// Compute safe path (lowest cost path) from source
// Time Complexity: O(V^2)
void computeSafePath(AdjListGraph& g, int startZone);

// Update blocked routes when fire level increases
// Time Complexity: O(E)
void updateBlockedRoutes(AdjListGraph& g, int zone, float fireLevel);

// --- Adjacency Matrix Graph ---

// Initialize adjacency matrix graph
// Time Complexity: O(V^2)
void initAdjMatrixGraph(AdjMatrixGraph& g, int zoneCount);

// Add edge in adjacency matrix
// Time Complexity: O(1)
void addEdgeMatrix(AdjMatrixGraph& g, int from, int to, float cost);

// Display adjacency matrix
// Time Complexity: O(V^2)
void displayAdjMatrix(AdjMatrixGraph& g);

#endif