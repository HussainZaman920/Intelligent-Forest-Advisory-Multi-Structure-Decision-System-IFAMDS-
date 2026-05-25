// Department 1: Array-Based Environmental Processing Layer

#include "arrays.h"
// STATIC BASELINE - fixed normal forest conditions

float baselineTemp = 25.0;
float baselineSmoke = 0.0;
float baselineHumidity = 60.0;
float baselineWind = 10.0;

// ============================================================
// DYNAMIC ARRAYS - live sensor data
// ============================================================
float tempReadings[MAX_READINGS];
float smokeReadings[MAX_READINGS];
float humidityReadings[MAX_READINGS];
float windReadings[MAX_READINGS];
int   readingCount = 0;

// 2D grid initialized with baseline values
float tempGrid[3][3] = {
    {25.0, 25.0, 25.0},
    {25.0, 25.0, 25.0},
    {25.0, 25.0, 25.0}
};

float smokeGrid[3][3] = {
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0}
};

// ============================================================
// getReadingCount()
// Returns how many readings are stored
// Used in main.cpp to display count without extern
// Time Complexity: O(1)
// ============================================================
int getReadingCount() {
    return readingCount;
}

// ============================================================
// addSensorReading()
// Adds new sensor reading to all dynamic arrays
// Time Complexity: O(1)
// ============================================================
void addSensorReading(float temp, float smoke, float humidity, float wind) {

    if (readingCount >= MAX_READINGS) {
        cout << "Sensor array is full. Cannot add more readings." << endl;
        return;
    }

    tempReadings[readingCount] = temp;
    smokeReadings[readingCount] = smoke;
    humidityReadings[readingCount] = humidity;
    windReadings[readingCount] = wind;
    readingCount++;

    cout << endl << "Sensor reading added successfully." << endl;
    cout << "Temperature : " << temp << " C" << endl;
    cout << "Smoke Level : " << smoke << endl;
    cout << "Humidity    : " << humidity << " %" << endl;
    cout << "Wind Speed  : " << wind << " km/h" << endl;
    cout << "Total readings stored: " << readingCount << endl;
}

// ============================================================
// compareWithBaseline()
// Compares latest reading against static baseline values
// Time Complexity: O(1)
// ============================================================
void compareWithBaseline() {

    if (readingCount == 0) {
        cout << endl << "No sensor readings available. Please add readings first." << endl;
        return;
    }

    int latest = readingCount - 1;

    cout << endl << "--- Baseline vs Latest Reading ---" << endl;
    cout << "---------------------------------------------------" << endl;

    // Temperature
    cout << "Temperature  Baseline: " << baselineTemp << "C   Current: " << tempReadings[latest] << "C   Status: ";
    if (tempReadings[latest] > TEMP_THRESHOLD) {
        cout << "DANGER - Fire Risk" << endl;
    }
    else if (tempReadings[latest] > baselineTemp) {
        cout << "WARNING - Above Normal" << endl;
    }
    else {
        cout << "NORMAL" << endl;
    }

    // Smoke
    cout << "Smoke        Baseline: " << baselineSmoke << "   Current: " << smokeReadings[latest] << "   Status: ";
    if (smokeReadings[latest] > SMOKE_THRESHOLD) {
        cout << "DANGER - Possible Fire" << endl;
    }
    else if (smokeReadings[latest] > baselineSmoke) {
        cout << "WARNING - Smoke Detected" << endl;
    }
    else {
        cout << "NORMAL" << endl;
    }

    // Humidity
    cout << "Humidity     Baseline: " << baselineHumidity << "%   Current: " << humidityReadings[latest] << "%   Status: ";
    if (humidityReadings[latest] < HUMIDITY_THRESHOLD) {
        cout << "DANGER - Very Dry" << endl;
    }
    else if (humidityReadings[latest] < baselineHumidity) {
        cout << "WARNING - Below Normal" << endl;
    }
    else {
        cout << "NORMAL" << endl;
    }

    // Wind
    cout << "Wind         Baseline: " << baselineWind << "km/h   Current: " << windReadings[latest] << "km/h   Status: ";
    if (windReadings[latest] > baselineWind) {
        cout << "WARNING - High Wind" << endl;
    }
    else {
        cout << "NORMAL" << endl;
    }
}

// ============================================================
// validateAndFilterNoise()
// Scans all readings and flags anomalies
// Time Complexity: O(n)
// ============================================================
void validateAndFilterNoise() {

    if (readingCount == 0) {
        cout << endl << "No readings to validate." << endl;
        return;
    }

    cout << endl << "--- Validating Sensor Readings ---" << endl;
    int anomalyCount = 0;

    for (int i = 0; i < readingCount; i++) {

        bool anomaly = false;

        cout << endl << "Reading [" << i + 1 << "]:" << endl;

        if (tempReadings[i] < 0) {
            cout << "  INVALID  - Temperature " << tempReadings[i] << "C is physically impossible" << endl;
            anomaly = true;
        }
        else if (tempReadings[i] > TEMP_THRESHOLD) {
            cout << "  ANOMALY  - Temperature " << tempReadings[i] << "C exceeds safe limit of " << TEMP_THRESHOLD << "C" << endl;
            anomaly = true;
        }

        if (smokeReadings[i] < 0) {
            cout << "  INVALID  - Smoke level cannot be negative" << endl;
            anomaly = true;
        }
        else if (smokeReadings[i] > SMOKE_THRESHOLD) {
            cout << "  ANOMALY  - Smoke " << smokeReadings[i] << " exceeds safe limit of " << SMOKE_THRESHOLD << endl;
            anomaly = true;
        }

        if (humidityReadings[i] < HUMIDITY_THRESHOLD) {
            cout << "  ANOMALY  - Humidity " << humidityReadings[i] << "% is below safe limit of " << HUMIDITY_THRESHOLD << "%" << endl;
            anomaly = true;
        }

        if (anomaly == false) {
            cout << "  All values normal." << endl;
        }
        else {
            anomalyCount++;
        }
    }

    cout << endl << "Validation complete." << endl;
    cout << "Total anomalies found: " << anomalyCount << " out of " << readingCount << " readings." << endl;
}

// ============================================================
// display1DTimeSeries()
// Prints all sensor readings in time order
// Time Complexity: O(n)
// ============================================================
void display1DTimeSeries() {

    if (readingCount == 0) {
        cout << endl << "No readings available." << endl;
        return;
    }

    cout << endl << "--- 1D Time Series Data ---" << endl;
    cout << "Reading   Temp(C)   Smoke   Humidity(%)   Wind(km/h)" << endl;
    cout << "-------------------------------------------------------" << endl;

    for (int i = 0; i < readingCount; i++) {
        cout << "  [" << i + 1 << "]      "
            << tempReadings[i] << "        "
            << smokeReadings[i] << "       "
            << humidityReadings[i] << "            "
            << windReadings[i] << endl;
    }
}

// ============================================================
// display2DForestGrid()
// Prints 3x3 forest zone map for temperature and smoke
// Time Complexity: O(rows x cols) = O(9)
// ============================================================
void display2DForestGrid() {

    cout << endl << "--- 2D Forest Zone Grid (Temperature) ---" << endl;
    cout << "        Col0     Col1     Col2" << endl;

    for (int i = 0; i < 3; i++) {
        cout << "Row" << i << "    ";
        for (int j = 0; j < 3; j++) {
            cout << tempGrid[i][j] << "C    ";
        }
        cout << endl;
    }

    cout << endl << "--- 2D Forest Zone Grid (Smoke Level) ---" << endl;
    cout << "        Col0     Col1     Col2" << endl;

    for (int i = 0; i < 3; i++) {
        cout << "Row" << i << "    ";
        for (int j = 0; j < 3; j++) {
            cout << smokeGrid[i][j] << "     ";
        }
        cout << endl;
    }
}

// ============================================================
// displayZoneConditions()
// Shows status summary for every stored reading
// Time Complexity: O(n)
// ============================================================
void displayZoneConditions() {

    if (readingCount == 0) {
        cout << endl << "No zone data available." << endl;
        return;
    }

    cout << endl << "--- Zone-wise Conditions Summary ---" << endl;

    for (int i = 0; i < readingCount; i++) {

        cout << endl << "Zone Reading [" << i + 1 << "]:" << endl;

        if (tempReadings[i] > TEMP_THRESHOLD) {
            cout << "  Temperature : " << tempReadings[i] << "C  --> FIRE RISK" << endl;
        }
        else if (tempReadings[i] > baselineTemp) {
            cout << "  Temperature : " << tempReadings[i] << "C  --> Above Normal" << endl;
        }
        else {
            cout << "  Temperature : " << tempReadings[i] << "C  --> Normal" << endl;
        }

        if (smokeReadings[i] > SMOKE_THRESHOLD) {
            cout << "  Smoke Level : " << smokeReadings[i] << "  --> FIRE POSSIBLE" << endl;
        }
        else if (smokeReadings[i] > 0) {
            cout << "  Smoke Level : " << smokeReadings[i] << "  --> Slight Smoke" << endl;
        }
        else {
            cout << "  Smoke Level : " << smokeReadings[i] << "  --> Clear" << endl;
        }

        if (humidityReadings[i] < HUMIDITY_THRESHOLD) {
            cout << "  Humidity    : " << humidityReadings[i] << "%  --> VERY DRY" << endl;
        }
        else {
            cout << "  Humidity    : " << humidityReadings[i] << "%  --> Normal" << endl;
        }
    }
}

// ============================================================
// spatialInterpolation()
// Estimates missing zone value using surrounding neighbors
// Formula: value = sum of valid neighbors / number of neighbors
// Time Complexity: O(1)
// ============================================================
void spatialInterpolation(int row, int col) {

    float sum = 0.0;
    int   count = 0;

    // Top neighbor
    if (row - 1 >= 0) {
        sum += tempGrid[row - 1][col];
        count++;
    }

    // Bottom neighbor
    if (row + 1 < 3) {
        sum += tempGrid[row + 1][col];
        count++;
    }

    // Left neighbor
    if (col - 1 >= 0) {
        sum += tempGrid[row][col - 1];
        count++;
    }

    // Right neighbor
    if (col + 1 < 3) {
        sum += tempGrid[row][col + 1];
        count++;
    }

    if (count == 0) {
        cout << endl << "No neighbors found for interpolation." << endl;
        return;
    }

    float estimated = sum / count;
    tempGrid[row][col] = estimated;

    cout << endl << "Spatial Interpolation for Zone [" << row << "][" << col << "]:" << endl;
    cout << "Neighbors found  : " << count << endl;
    cout << "Estimated Temp   : " << estimated << "C" << endl;
    cout << "Grid updated with estimated value." << endl;
}

// ============================================================
// boundaryDetection()
// Finds zones where temperature difference exceeds 10 degrees
// Signals possible fire spread boundary
// Time Complexity: O(rows x cols)
// ============================================================
void boundaryDetection() {

    cout << endl << "--- Boundary Detection (Temperature Grid) ---" << endl;

    bool  boundaryFound = false;
    float boundaryLimit = 10.0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            // Check right neighbor
            if (j + 1 < 3) {
                float diff = tempGrid[i][j] - tempGrid[i][j + 1];
                if (diff < 0) {
                    diff = -diff;
                }
                if (diff > boundaryLimit) {
                    cout << "BOUNDARY - Zone[" << i << "][" << j << "] = "
                        << tempGrid[i][j] << "C  vs  Zone["
                        << i << "][" << j + 1 << "] = "
                        << tempGrid[i][j + 1] << "C" << endl;
                    boundaryFound = true;
                }
            }

            // Check bottom neighbor
            if (i + 1 < 3) {
                float diff = tempGrid[i][j] - tempGrid[i + 1][j];
                if (diff < 0) {
                    diff = -diff;
                }
                if (diff > boundaryLimit) {
                    cout << "BOUNDARY - Zone[" << i << "][" << j << "] = "
                        << tempGrid[i][j] << "C  vs  Zone["
                        << i + 1 << "][" << j << "] = "
                        << tempGrid[i + 1][j] << "C" << endl;
                    boundaryFound = true;
                }
            }
        }
    }

    if (boundaryFound == false) {
        cout << "No boundaries detected. Forest conditions are uniform." << endl;
    }
}

// ============================================================
// updateGrid()
// Updates temperature and smoke for a specific zone
// Time Complexity: O(1)
// ============================================================
void updateGrid(int row, int col, float tempVal, float smokeVal) {

    if (row < 0 || row >= 3 || col < 0 || col >= 3) {
        cout << endl << "Invalid zone coordinates." << endl;
        return;
    }

    tempGrid[row][col] = tempVal;
    smokeGrid[row][col] = smokeVal;

    cout << endl << "Zone [" << row << "][" << col << "] updated." << endl;
    cout << "Temperature : " << tempVal << "C" << endl;
    cout << "Smoke Level : " << smokeVal << endl;
}