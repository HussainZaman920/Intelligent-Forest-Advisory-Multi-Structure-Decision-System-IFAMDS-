#pragma once
// ============================================================
// tree.h
// Department 5: Hierarchical Decision Intelligence Layer
// Implements zone hierarchy tree, resource tree,
// and decision tree for forest management
// ============================================================

#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;

// ============================================================
// TREE NODE STRUCTURE
// Each node represents a forest zone or decision point
// ============================================================

struct TreeNode {
    int       zoneID;       // unique zone identifier
    char      zoneName[30]; // name of zone
    float     riskScore;    // calculated risk for this zone
    float     temperature;  // current temperature
    float     smoke;        // current smoke level
    float     humidity;     // current humidity
    bool      isOnFire;     // whether zone is on fire
    bool      isEvacuated;  // whether zone is evacuated
    TreeNode* left;         // left child
    TreeNode* right;        // right child
};

// ============================================================
// TREE STRUCTURE
// Root pointer and size
// ============================================================

struct Tree {
    TreeNode* root;
    int       size;
};

// ============================================================
// RESOURCE NODE
// Used for water and equipment resource trees
// ============================================================

struct ResourceNode {
    int          resourceID;
    char         resourceName[30];
    float        available;    // available amount
    float        required;     // required amount
    float        availability; // available / required ratio
    ResourceNode* left;
    ResourceNode* right;
};

// ============================================================
// RESOURCE TREE
// ============================================================

struct ResourceTree {
    ResourceNode* root;
    int           size;
};

// ============================================================
// FUNCTION DECLARATIONS
// ============================================================

// --- Zone Hierarchy Tree ---

// Initialize tree
// Time Complexity: O(1)
void initTree(Tree& t);

// Create a new tree node
// Time Complexity: O(1)
TreeNode* createTreeNode(int zoneID, const char* name, float temp, float smoke, float humidity);

// Insert zone node into tree (by zoneID)
// Time Complexity: O(log n) balanced, O(n) worst
TreeNode* insertZone(TreeNode* root, int zoneID, const char* name, float temp, float smoke, float humidity);

// Calculate risk score for a zone
// Formula: Score = 0.4(fire) + 0.3(smoke) + 0.3(temp) normalized
// Time Complexity: O(1)
float calculateRiskScore(float temp, float smoke, float humidity);

// Display tree in order (left, root, right)
// Time Complexity: O(n)
void inorderDisplay(TreeNode* root);

// Display tree structure with levels
// Time Complexity: O(n)
void displayTreeStructure(TreeNode* root, int level);

// Search for a zone by ID
// Time Complexity: O(log n) balanced, O(n) worst
TreeNode* searchZone(TreeNode* root, int zoneID);

// Make local zone decision
// Time Complexity: O(1)
void localZoneDecision(TreeNode* node);

// Make regional decision (checks subtree)
// Time Complexity: O(n)
void regionalDecision(TreeNode* root);

// Make global emergency decision (checks entire tree)
// Time Complexity: O(n)
void globalEmergencyDecision(TreeNode* root);

// Update zone conditions
// Time Complexity: O(log n)
void updateZoneConditions(TreeNode* root, int zoneID, float temp, float smoke, float humidity);

// Compute overall risk score for display
// Time Complexity: O(1)
void computeRiskScore();

// Execute final action based on risk
// Time Complexity: O(1)
void executeFinalAction(float riskScore, int zone);

// --- Resource Tree ---

// Initialize resource tree
// Time Complexity: O(1)
void initResourceTree(ResourceTree& rt);

// Create resource node
// Time Complexity: O(1)
ResourceNode* createResourceNode(int id, const char* name, float available, float required);

// Insert resource into tree
// Time Complexity: O(log n)
ResourceNode* insertResource(ResourceNode* root, int id, const char* name, float available, float required);

// Display all resources
// Time Complexity: O(n)
void displayResources(ResourceNode* root);

// Check resource availability
// Time Complexity: O(n)
void checkResourceAvailability(ResourceNode* root);

#endif

