// Department 1: Array-Based Environmental Processing Layer
#ifndef ARRAYS_H
#define ARRAYS_H
#include <iostream>
using namespace std;

const int MAX_ZONES = 9;
const int MAX_READINGS = 50;

// Anomaly thresholds
const float TEMP_THRESHOLD = 45.0;
const float SMOKE_THRESHOLD = 70.0;
const float HUMIDITY_THRESHOLD = 20.0;

// Add a new sensor reading
// Time Complexity: O(1)
void addSensorReading(float temp, float smoke, float humidity, float wind);

// Compare latest reading with static baseline
// Time Complexity: O(1)
void compareWithBaseline();

// Check all readings for anomalies
// Time Complexity: O(n)
void validateAndFilterNoise();

// Display 1D time series
// Time Complexity: O(n)
void display1DTimeSeries();

// Display 2D forest grid
// Time Complexity: O(rows x cols)
void display2DForestGrid();

// Display zone-wise conditions
// Time Complexity: O(n)
void displayZoneConditions();

// Estimate missing zone value using neighbors
// Time Complexity: O(1)
void spatialInterpolation(int row, int col);

// Detect sharp value changes between zones
// Time Complexity: O(rows x cols)
void boundaryDetection();

// Update a specific zone in the grid
// Time Complexity: O(1)
void updateGrid(int row, int col, float tempVal, float smokeVal);

// Get current reading count (used in main.cpp)
// Time Complexity: O(1)
int getReadingCount();
#endif