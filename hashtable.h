#pragma once
// ============================================================
// hashtable.h
// Department 7: Indexing and Retrieval Acceleration Layer
// Implements hash table with chaining for collision handling
// and a cache for frequently accessed data
// Hash Function: Index = Key mod TableSize
// ============================================================

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
using namespace std;

// ============================================================
// CONSTANTS
// ============================================================

const int TABLE_SIZE = 10; // size of hash table
const int CACHE_SIZE = 5;  // size of fast retrieval cache

// ============================================================
// ZONE DATA RECORD
// Stores all sensor data for one forest zone
// ============================================================

struct ZoneRecord {
    int   zoneID;        // unique zone key
    float temperature;   // current temperature
    float smoke;         // current smoke level
    float humidity;      // current humidity
    float riskScore;     // calculated risk
};

// ============================================================
// HASH NODE
// Each node holds one zone record
// Used for chaining in collision handling
// ============================================================

struct HashNode {
    ZoneRecord data;
    HashNode* next; // chain to next node at same index
};

// ============================================================
// PRIMARY HASH TABLE (H1)
// Array of linked lists for chaining
// ============================================================

struct HashTable {
    HashNode* table[TABLE_SIZE]; // array of chain heads
    int       count;             // total records stored
};

// ============================================================
// CACHE ENTRY
// Stores recently accessed zone data
// ============================================================

struct CacheEntry {
    int        zoneID;     // which zone this cache entry is for
    ZoneRecord data;       // the cached data
    bool       isOccupied; // whether this slot is used
    int        accessCount;// how many times accessed
};

// ============================================================
// FAST RETRIEVAL CACHE (H3)
// Fixed size array of recently used entries
// ============================================================

struct Cache {
    CacheEntry entries[CACHE_SIZE];
    int        size;
};

// ============================================================
// FUNCTION DECLARATIONS
// ============================================================

// Hash function: Index = Key mod TableSize
// Time Complexity: O(1)
int hashFunction(int key);

// --- Hash Table Operations ---

// Initialize hash table
// Time Complexity: O(n) where n = TABLE_SIZE
void initHashTable(HashTable& ht);

// Insert zone record into hash table
// Time Complexity: O(1) average, O(n) worst with collisions
void insertRecord(HashTable& ht, int zoneID, float temp, float smoke, float humidity, float risk);

// Retrieve zone record by zoneID
// Time Complexity: O(1) average, O(n) worst
HashNode* retrieveRecord(HashTable& ht, int zoneID);

// Delete zone record from hash table
// Time Complexity: O(1) average, O(n) worst
void deleteRecord(HashTable& ht, int zoneID);

// Display entire hash table with chains
// Time Complexity: O(n + k) where k = total records
void displayHashTable(HashTable& ht);

// Display collision chains
// Time Complexity: O(n + k)
void displayCollisions(HashTable& ht);

// --- Cache Operations ---

// Initialize cache
// Time Complexity: O(n) where n = CACHE_SIZE
void initCache(Cache& c);

// Add or update entry in cache
// Time Complexity: O(n)
void updateCache(Cache& c, int zoneID, ZoneRecord record);

// Retrieve from cache
// Time Complexity: O(n)
CacheEntry* getFromCache(Cache& c, int zoneID);

// Display cache contents
// Time Complexity: O(n)
void displayCache(Cache& c);

// Clear cache
// Time Complexity: O(n)
void clearCache(Cache& c);

#endif