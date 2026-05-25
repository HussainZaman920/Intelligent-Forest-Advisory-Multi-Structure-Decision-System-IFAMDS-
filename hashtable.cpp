// ============================================================
// hashtable.cpp
// Department 7: Indexing and Retrieval Acceleration Layer
// Implementation of hash table and cache operations
// ============================================================

#include "hashtable.h"

// ============================================================
// hashFunction()
// Calculates storage index using modulo operation
// Formula: Index = Key mod TableSize
// Time Complexity: O(1)
// ============================================================
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// ============================================================
// initHashTable()
// Sets all table slots to NULL
// Time Complexity: O(n) where n = TABLE_SIZE
// ============================================================
void initHashTable(HashTable& ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht.table[i] = NULL;
    }
    ht.count = 0;
    cout << endl << "Hash table initialized." << endl;
    cout << "Table size: " << TABLE_SIZE << endl;
}

// ============================================================
// insertRecord()
// Inserts zone record into hash table using chaining
// If two keys map to same index, new node is added to chain
// Time Complexity: O(1) average
// ============================================================
void insertRecord(HashTable& ht, int zoneID, float temp, float smoke, float humidity, float risk) {

    // Calculate index using hash function
    int index = hashFunction(zoneID);

    // Create new hash node
    HashNode* newNode = new HashNode();
    newNode->data.zoneID = zoneID;
    newNode->data.temperature = temp;
    newNode->data.smoke = smoke;
    newNode->data.humidity = humidity;
    newNode->data.riskScore = risk;
    newNode->next = NULL;

    // If slot is empty - no collision
    if (ht.table[index] == NULL) {
        ht.table[index] = newNode;
        ht.count++;

        cout << endl << "Record inserted." << endl;
        cout << "Zone ID   : " << zoneID << endl;
        cout << "Index     : " << index << endl;
        cout << "No collision at this index." << endl;
        return;
    }

    // Slot is occupied - collision detected
    // Check if zoneID already exists - update if so
    HashNode* current = ht.table[index];

    while (current != NULL) {
        if (current->data.zoneID == zoneID) {
            // Update existing record
            current->data.temperature = temp;
            current->data.smoke = smoke;
            current->data.humidity = humidity;
            current->data.riskScore = risk;

            cout << endl << "Record updated for Zone " << zoneID << endl;
            cout << "Index: " << index << endl;
            delete newNode;
            return;
        }
        current = current->next;
    }

    // Chain new node at front (collision handling)
    newNode->next = ht.table[index];
    ht.table[index] = newNode;
    ht.count++;

    cout << endl << "Record inserted with collision handled." << endl;
    cout << "Zone ID   : " << zoneID << endl;
    cout << "Index     : " << index << endl;
    cout << "Chained to existing record at this index." << endl;
}

// ============================================================
// retrieveRecord()
// Finds and returns zone record by zoneID
// Time Complexity: O(1) average, O(n) worst
// ============================================================
HashNode* retrieveRecord(HashTable& ht, int zoneID) {

    // Calculate index
    int index = hashFunction(zoneID);

    HashNode* current = ht.table[index];

    // Search chain at this index
    while (current != NULL) {
        if (current->data.zoneID == zoneID) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// ============================================================
// deleteRecord()
// Removes zone record from hash table
// Time Complexity: O(1) average, O(n) worst
// ============================================================
void deleteRecord(HashTable& ht, int zoneID) {

    int index = hashFunction(zoneID);

    if (ht.table[index] == NULL) {
        cout << endl << "Zone " << zoneID << " not found in table." << endl;
        return;
    }

    HashNode* current = ht.table[index];
    HashNode* previous = NULL;

    while (current != NULL) {

        if (current->data.zoneID == zoneID) {

            if (previous == NULL) {
                // Node is at head of chain
                ht.table[index] = current->next;
            }
            else {
                // Node is in middle or end of chain
                previous->next = current->next;
            }

            delete current;
            ht.count--;

            cout << endl << "Zone " << zoneID << " deleted from hash table." << endl;
            cout << "Index: " << index << endl;
            return;
        }

        previous = current;
        current = current->next;
    }

    cout << endl << "Zone " << zoneID << " not found." << endl;
}

// ============================================================
// displayHashTable()
// Prints all slots and their chains
// Time Complexity: O(n + k)
// ============================================================
void displayHashTable(HashTable& ht) {

    cout << endl << "--- Hash Table Contents ---" << endl;
    cout << "Total records: " << ht.count << endl;
    cout << "Table size   : " << TABLE_SIZE << endl;
    cout << "---------------------------" << endl;

    for (int i = 0; i < TABLE_SIZE; i++) {

        cout << "Index [" << i << "] --> ";

        if (ht.table[i] == NULL) {
            cout << "Empty" << endl;
            continue;
        }

        HashNode* current = ht.table[i];

        while (current != NULL) {
            cout << "Zone " << current->data.zoneID
                << " (T:" << current->data.temperature
                << " S:" << current->data.smoke
                << " H:" << current->data.humidity
                << " R:" << current->data.riskScore << ")";

            if (current->next != NULL) {
                cout << " --> ";
            }

            current = current->next;
        }

        cout << endl;
    }
}

// ============================================================
// displayCollisions()
// Shows only slots that have more than one record (collisions)
// Time Complexity: O(n + k)
// ============================================================
void displayCollisions(HashTable& ht) {

    cout << endl << "--- Collision Chains ---" << endl;

    bool anyCollision = false;

    for (int i = 0; i < TABLE_SIZE; i++) {

        if (ht.table[i] != NULL && ht.table[i]->next != NULL) {

            anyCollision = true;

            cout << endl << "Collision at Index [" << i << "]:" << endl;

            HashNode* current = ht.table[i];
            int chainPos = 1;

            while (current != NULL) {
                cout << "  Chain [" << chainPos << "] Zone "
                    << current->data.zoneID
                    << "  Temp: " << current->data.temperature
                    << "  Smoke: " << current->data.smoke << endl;
                current = current->next;
                chainPos++;
            }
        }
    }

    if (anyCollision == false) {
        cout << "No collisions detected in current table." << endl;
    }
}

// ============================================================
// initCache()
// Sets all cache slots to unoccupied
// Time Complexity: O(n)
// ============================================================
void initCache(Cache& c) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        c.entries[i].isOccupied = false;
        c.entries[i].zoneID = -1;
        c.entries[i].accessCount = 0;
    }
    c.size = 0;
    cout << endl << "Cache initialized. Size: " << CACHE_SIZE << endl;
}

// ============================================================
// updateCache()
// Adds or updates a zone record in cache
// If cache is full, replaces least accessed entry
// Time Complexity: O(n)
// ============================================================
void updateCache(Cache& c, int zoneID, ZoneRecord record) {

    // Check if zone already in cache - update it
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (c.entries[i].isOccupied == true && c.entries[i].zoneID == zoneID) {
            c.entries[i].data = record;
            c.entries[i].accessCount++;
            cout << endl << "Cache updated for Zone " << zoneID << endl;
            return;
        }
    }

    // Find empty slot
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (c.entries[i].isOccupied == false) {
            c.entries[i].zoneID = zoneID;
            c.entries[i].data = record;
            c.entries[i].isOccupied = true;
            c.entries[i].accessCount = 1;
            c.size++;
            cout << endl << "Zone " << zoneID << " added to cache." << endl;
            return;
        }
    }

    // Cache is full - replace least accessed entry
    int minAccess = c.entries[0].accessCount;
    int minIndex = 0;

    for (int i = 1; i < CACHE_SIZE; i++) {
        if (c.entries[i].accessCount < minAccess) {
            minAccess = c.entries[i].accessCount;
            minIndex = i;
        }
    }

    cout << endl << "Cache full. Replacing Zone "
        << c.entries[minIndex].zoneID
        << " with Zone " << zoneID << endl;

    c.entries[minIndex].zoneID = zoneID;
    c.entries[minIndex].data = record;
    c.entries[minIndex].isOccupied = true;
    c.entries[minIndex].accessCount = 1;
}

// ============================================================
// getFromCache()
// Retrieves zone data from cache if available
// Time Complexity: O(n)
// ============================================================
CacheEntry* getFromCache(Cache& c, int zoneID) {

    for (int i = 0; i < CACHE_SIZE; i++) {
        if (c.entries[i].isOccupied == true && c.entries[i].zoneID == zoneID) {
            c.entries[i].accessCount++;
            return &c.entries[i];
        }
    }

    return NULL;
}

// ============================================================
// displayCache()
// Shows all entries currently in cache
// Time Complexity: O(n)
// ============================================================
void displayCache(Cache& c) {

    cout << endl << "--- Cache Contents ---" << endl;
    cout << "Cache size: " << CACHE_SIZE << endl;
    cout << "Used slots: " << c.size << endl;
    cout << "---------------------" << endl;

    bool anyEntry = false;

    for (int i = 0; i < CACHE_SIZE; i++) {
        if (c.entries[i].isOccupied == true) {
            cout << endl << "Slot [" << i << "]:" << endl;
            cout << "  Zone ID      : " << c.entries[i].zoneID << endl;
            cout << "  Temperature  : " << c.entries[i].data.temperature << "C" << endl;
            cout << "  Smoke        : " << c.entries[i].data.smoke << endl;
            cout << "  Humidity     : " << c.entries[i].data.humidity << "%" << endl;
            cout << "  Risk Score   : " << c.entries[i].data.riskScore << endl;
            cout << "  Access Count : " << c.entries[i].accessCount << endl;
            anyEntry = true;
        }
    }

    if (anyEntry == false) {
        cout << "Cache is empty." << endl;
    }
}

// ============================================================
// clearCache()
// Resets all cache entries
// Time Complexity: O(n)
// ============================================================
void clearCache(Cache& c) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        c.entries[i].isOccupied = false;
        c.entries[i].zoneID = -1;
        c.entries[i].accessCount = 0;
    }
    c.size = 0;
    cout << endl << "Cache cleared." << endl;
}