// ============================================================
// tree.cpp
// Department 5: Hierarchical Decision Intelligence Layer
// Implementation of zone tree, resource tree,
// and decision-making logic
// ============================================================

#include "tree.h"
#include <cstring>

// ============================================================
// initTree()
// Sets root to NULL and size to 0
// Time Complexity: O(1)
// ============================================================
void initTree(Tree& t) {
    t.root = NULL;
    t.size = 0;
}

// ============================================================
// createTreeNode()
// Creates and returns a new zone tree node
// Time Complexity: O(1)
// ============================================================
TreeNode* createTreeNode(int zoneID, const char* name, float temp, float smoke, float humidity) {

    TreeNode* newNode = new TreeNode();
    newNode->zoneID = zoneID;
    newNode->temperature = temp;
    newNode->smoke = smoke;
    newNode->humidity = humidity;
    newNode->isOnFire = false;
    newNode->isEvacuated = false;
    newNode->left = NULL;
    newNode->right = NULL;

    strcpy_s(newNode->zoneName, 30, name);

    // Calculate risk score on creation
    newNode->riskScore = calculateRiskScore(temp, smoke, humidity);

    return newNode;
}

// ============================================================
// insertZone()
// Inserts zone node into BST by zoneID
// Smaller IDs go left, larger go right
// Time Complexity: O(log n) average, O(n) worst case
// ============================================================
TreeNode* insertZone(TreeNode* root, int zoneID, const char* name, float temp, float smoke, float humidity) {

    // Base case - empty spot found
    if (root == NULL) {
        cout << endl << "Zone inserted into tree." << endl;
        cout << "Zone ID   : " << zoneID << endl;
        cout << "Zone Name : " << name << endl;
        cout << "Temp      : " << temp << "C" << endl;
        cout << "Smoke     : " << smoke << endl;
        cout << "Risk Score: " << calculateRiskScore(temp, smoke, humidity) << endl;
        return createTreeNode(zoneID, name, temp, smoke, humidity);
    }

    // Go left if smaller
    if (zoneID < root->zoneID) {
        root->left = insertZone(root->left, zoneID, name, temp, smoke, humidity);
    }
    // Go right if larger
    else if (zoneID > root->zoneID) {
        root->right = insertZone(root->right, zoneID, name, temp, smoke, humidity);
    }
    // Duplicate zone ID
    else {
        cout << endl << "Zone ID " << zoneID << " already exists in tree." << endl;
    }

    return root;
}

// ============================================================
// calculateRiskScore()
// Calculates risk using weighted formula from project doc
// Formula: Score = 0.4(fire) + 0.3(smoke) + 0.3(temp) normalized
// Time Complexity: O(1)
// ============================================================
float calculateRiskScore(float temp, float smoke, float humidity) {

    // Normalize values to 0-1 range
    float normTemp = temp / 100.0;
    float normSmoke = smoke / 100.0;

    // Humidity inversely affects risk (lower humidity = higher risk)
    float normHumidity = 1.0 - (humidity / 100.0);

    // Weighted risk score from project document
    float score = (0.4 * normTemp) + (0.3 * normSmoke) + (0.3 * normHumidity);

    // Cap at 1.0
    if (score > 1.0) {
        score = 1.0;
    }

    return score;
}

// ============================================================
// inorderDisplay()
// Displays all zones in order of zone ID
// Left -> Root -> Right
// Time Complexity: O(n)
// ============================================================
void inorderDisplay(TreeNode* root) {

    if (root == NULL) {
        return;
    }

    inorderDisplay(root->left);

    cout << endl << "Zone [" << root->zoneID << "] " << root->zoneName << endl;
    cout << "  Temp      : " << root->temperature << "C" << endl;
    cout << "  Smoke     : " << root->smoke << endl;
    cout << "  Humidity  : " << root->humidity << "%" << endl;
    cout << "  Risk Score: " << root->riskScore << endl;

    if (root->isOnFire == true) {
        cout << "  Status    : ON FIRE" << endl;
    }
    else if (root->isEvacuated == true) {
        cout << "  Status    : EVACUATED" << endl;
    }
    else {
        cout << "  Status    : Normal" << endl;
    }

    inorderDisplay(root->right);
}

// ============================================================
// displayTreeStructure()
// Displays tree visually with indentation per level
// Time Complexity: O(n)
// ============================================================
void displayTreeStructure(TreeNode* root, int level) {

    if (root == NULL) {
        return;
    }

    // Display right subtree first (appears at top)
    displayTreeStructure(root->right, level + 1);

    // Print indentation based on level
    for (int i = 0; i < level; i++) {
        cout << "     ";
    }

    cout << "[Zone " << root->zoneID << " | Risk: " << root->riskScore << "]" << endl;

    // Display left subtree
    displayTreeStructure(root->left, level + 1);
}

// ============================================================
// searchZone()
// Searches for zone by ID in BST
// Time Complexity: O(log n) average, O(n) worst case
// ============================================================
TreeNode* searchZone(TreeNode* root, int zoneID) {

    if (root == NULL) {
        return NULL;
    }

    if (root->zoneID == zoneID) {
        return root;
    }

    if (zoneID < root->zoneID) {
        return searchZone(root->left, zoneID);
    }
    else {
        return searchZone(root->right, zoneID);
    }
}

// ============================================================
// localZoneDecision()
// Makes decision for a single zone based on its risk score
// Rule: If Risk > 0.6 -> Activate Local Response
// Time Complexity: O(1)
// ============================================================
void localZoneDecision(TreeNode* node) {

    if (node == NULL) {
        cout << endl << "Zone not found." << endl;
        return;
    }

    cout << endl << "--- Local Zone Decision ---" << endl;
    cout << "Zone      : " << node->zoneName << endl;
    cout << "Zone ID   : " << node->zoneID << endl;
    cout << "Risk Score: " << node->riskScore << endl;

    if (node->riskScore > 0.8) {
        node->isOnFire = true;
        cout << "DECISION  : CRITICAL - Zone is on fire!" << endl;
        cout << "ACTION    : Immediate evacuation required." << endl;
    }
    else if (node->riskScore > 0.6) {
        cout << "DECISION  : HIGH RISK - Activate local response." << endl;
        cout << "ACTION    : Send firefighting team to zone." << endl;
    }
    else if (node->riskScore > 0.4) {
        cout << "DECISION  : MODERATE - Increase monitoring." << endl;
        cout << "ACTION    : Deploy surveillance to zone." << endl;
    }
    else {
        cout << "DECISION  : LOW RISK - Continue normal monitoring." << endl;
        cout << "ACTION    : No immediate action needed." << endl;
    }
}

// ============================================================
// regionalDecision()
// Checks all zones in subtree and escalates if needed
// Spread condition: If fire spread rate > 0.5 -> Escalate
// Time Complexity: O(n)
// ============================================================
void regionalDecision(TreeNode* root) {

    if (root == NULL) {
        return;
    }

    // Check left zones
    regionalDecision(root->left);

    // Check this zone
    if (root->riskScore > 0.6) {
        cout << endl << "REGIONAL ALERT - Zone [" << root->zoneID << "] "
            << root->zoneName << endl;
        cout << "Risk Score : " << root->riskScore << endl;
        cout << "Action     : Escalating to regional response." << endl;
    }

    // Check right zones
    regionalDecision(root->right);
}

// ============================================================
// globalEmergencyDecision()
// Scans entire tree and triggers global alert if
// total risk across zones exceeds threshold
// Time Complexity: O(n)
// ============================================================
void globalEmergencyDecision(TreeNode* root) {

    if (root == NULL) {
        return;
    }

    float totalRisk = 0.0;
    int   zoneCount = 0;
    int   dangerZones = 0;

    // Use a simple stack-based traversal
    // to avoid recursion depth issues
    TreeNode* stack[100];
    int       top = -1;
    TreeNode* current = root;

    // Push root
    top++;
    stack[top] = current;

    while (top >= 0) {

        // Pop
        current = stack[top];
        top--;

        totalRisk += current->riskScore;
        zoneCount++;

        if (current->riskScore > 0.6) {
            dangerZones++;
        }

        // Push right first so left is processed first
        if (current->right != NULL) {
            top++;
            stack[top] = current->right;
        }

        if (current->left != NULL) {
            top++;
            stack[top] = current->left;
        }
    }

    float avgRisk = 0.0;
    if (zoneCount > 0) {
        avgRisk = totalRisk / zoneCount;
    }

    cout << endl << "--- Global Emergency Decision ---" << endl;
    cout << "Total Zones   : " << zoneCount << endl;
    cout << "Danger Zones  : " << dangerZones << endl;
    cout << "Average Risk  : " << avgRisk << endl;
    cout << "Total Risk    : " << totalRisk << endl;

    if (avgRisk > 0.6) {
        cout << endl << "GLOBAL ALERT ACTIVATED!" << endl;
        cout << "ACTION: Full system emergency response." << endl;
        cout << "ACTION: All zones to be evacuated." << endl;
        cout << "ACTION: All resources deployed." << endl;
    }
    else if (avgRisk > 0.4) {
        cout << endl << "REGIONAL WARNING ISSUED." << endl;
        cout << "ACTION: Increase monitoring in all zones." << endl;
        cout << "ACTION: Prepare emergency resources." << endl;
    }
    else {
        cout << endl << "System is STABLE." << endl;
        cout << "ACTION: Continue normal monitoring." << endl;
    }
}

// ============================================================
// updateZoneConditions()
// Finds zone and updates its sensor values and risk score
// Time Complexity: O(log n) average
// ============================================================
void updateZoneConditions(TreeNode* root, int zoneID, float temp, float smoke, float humidity) {

    TreeNode* zone = searchZone(root, zoneID);

    if (zone == NULL) {
        cout << endl << "Zone " << zoneID << " not found." << endl;
        return;
    }

    zone->temperature = temp;
    zone->smoke = smoke;
    zone->humidity = humidity;
    zone->riskScore = calculateRiskScore(temp, smoke, humidity);

    cout << endl << "Zone [" << zoneID << "] conditions updated." << endl;
    cout << "New Temp      : " << temp << "C" << endl;
    cout << "New Smoke     : " << smoke << endl;
    cout << "New Humidity  : " << humidity << "%" << endl;
    cout << "New Risk Score: " << zone->riskScore << endl;
}

// ============================================================
// computeRiskScore()
// Takes user input and computes risk score using formula
// Time Complexity: O(1)
// ============================================================
void computeRiskScore() {

    float temp, smoke, humidity;

    cout << endl << "--- Compute Risk Score ---" << endl;
    cout << "Enter Temperature (C) : "; cin >> temp;
    cout << "Enter Smoke Level     : "; cin >> smoke;
    cout << "Enter Humidity (%)    : "; cin >> humidity;

    float score = calculateRiskScore(temp, smoke, humidity);

    cout << endl << "Risk Score : " << score << endl;

    if (score > 0.8) {
        cout << "Level      : CRITICAL" << endl;
    }
    else if (score > 0.6) {
        cout << "Level      : HIGH" << endl;
    }
    else if (score > 0.4) {
        cout << "Level      : MODERATE" << endl;
    }
    else {
        cout << "Level      : LOW" << endl;
    }
}

// ============================================================
// executeFinalAction()
// Executes appropriate action based on risk score and zone
// Time Complexity: O(1)
// ============================================================
void executeFinalAction(float riskScore, int zone) {

    cout << endl << "--- Executing Final Action ---" << endl;
    cout << "Zone       : " << zone << endl;
    cout << "Risk Score : " << riskScore << endl;

    if (riskScore > 0.8) {
        cout << "ACTION: CRITICAL RESPONSE ACTIVATED" << endl;
        cout << "  --> Evacuating Zone " << zone << endl;
        cout << "  --> Deploying all firefighting units" << endl;
        cout << "  --> Alerting emergency services" << endl;
    }
    else if (riskScore > 0.6) {
        cout << "ACTION: HIGH RISK RESPONSE" << endl;
        cout << "  --> Sending firefighting team" << endl;
        cout << "  --> Increasing sensor frequency" << endl;
        cout << "  --> Preparing evacuation routes" << endl;
    }
    else if (riskScore > 0.4) {
        cout << "ACTION: MODERATE RESPONSE" << endl;
        cout << "  --> Deploying surveillance team" << endl;
        cout << "  --> Monitoring neighboring zones" << endl;
    }
    else {
        cout << "ACTION: ROUTINE MONITORING" << endl;
        cout << "  --> No immediate action required" << endl;
        cout << "  --> Continue normal observation" << endl;
    }
}

// ============================================================
// RESOURCE TREE OPERATIONS
// ============================================================

// ============================================================
// initResourceTree()
// Time Complexity: O(1)
// ============================================================
void initResourceTree(ResourceTree& rt) {
    rt.root = NULL;
    rt.size = 0;
}

// ============================================================
// createResourceNode()
// Time Complexity: O(1)
// ============================================================
ResourceNode* createResourceNode(int id, const char* name, float available, float required) {

    ResourceNode* newNode = new ResourceNode();
    newNode->resourceID = id;
    newNode->available = available;
    newNode->required = required;
    newNode->left = NULL;
    newNode->right = NULL;

    strcpy_s(newNode->resourceName, 30, name);

    if (required > 0) {
        newNode->availability = available / required;
    }
    else {
        newNode->availability = 0.0;
    }

    return newNode;
}

// ============================================================
// insertResource()
// Inserts resource into BST by resourceID
// Time Complexity: O(log n) average
// ============================================================
ResourceNode* insertResource(ResourceNode* root, int id, const char* name, float available, float required) {

    if (root == NULL) {
        cout << endl << "Resource added: " << name << endl;
        cout << "Available : " << available << endl;
        cout << "Required  : " << required << endl;
        cout << "Ratio     : " << available / required << endl;
        return createResourceNode(id, name, available, required);
    }

    if (id < root->resourceID) {
        root->left = insertResource(root->left, id, name, available, required);
    }
    else if (id > root->resourceID) {
        root->right = insertResource(root->right, id, name, available, required);
    }
    else {
        cout << endl << "Resource ID " << id << " already exists." << endl;
    }

    return root;
}

// ============================================================
// displayResources()
// Shows all resources in order
// Time Complexity: O(n)
// ============================================================
void displayResources(ResourceNode* root) {

    if (root == NULL) {
        return;
    }

    displayResources(root->left);

    cout << endl << "Resource [" << root->resourceID << "] " << root->resourceName << endl;
    cout << "  Available    : " << root->available << endl;
    cout << "  Required     : " << root->required << endl;
    cout << "  Availability : " << root->availability << endl;

    if (root->availability >= 1.0) {
        cout << "  Status       : Sufficient" << endl;
    }
    else if (root->availability >= 0.5) {
        cout << "  Status       : Limited" << endl;
    }
    else {
        cout << "  Status       : CRITICAL - Low Supply" << endl;
    }

    displayResources(root->right);
}

// ============================================================
// checkResourceAvailability()
// Scans all resources and flags critical ones
// Time Complexity: O(n)
// ============================================================
void checkResourceAvailability(ResourceNode* root) {

    if (root == NULL) {
        return;
    }

    checkResourceAvailability(root->left);

    if (root->availability < 0.5) {
        cout << "CRITICAL - Resource [" << root->resourceName
            << "] is below 50% availability." << endl;
    }

    checkResourceAvailability(root->right);
}