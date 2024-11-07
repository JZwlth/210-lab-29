// Need change scrollback to 2000 in vscode setting

// Include necessary headers for file handling, data structures, etc.
#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

// Define a function
// Parameters: map of regions, number of time periods
void simulateDiseaseSpread(map<string, array<list<string>, 3>>& regions, int timePeriods);

int main() {
    // Initialize random seed
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialize a map to store reion information, each associated with an array of lists for susceptible, infected, and recovered individuals
    map<string, array<list<string>, 3>> regions;

    // Open an external file to read initial data about individuals and populate the map
    ifstream inputFile("population_data.txt");
    // If file does not open, print an error and exit
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the data file.\n";
        return 1;
    }

    // Read data from file and populate map
    string line;
    while (getline(inputFile, line)) {
        // For each line, extract IndividualID, RegionName, and DiseaseState
        istringstream ss(line);
        string individualID, regionName, diseaseStateStr;
        if (getline(ss, individualID, ',') &&
            getline(ss, regionName, ',') &&
            getline(ss, diseaseStateStr)) {

            char diseaseState = diseaseStateStr[0];
            // Ensure the region exists in the map
            regions[regionName];

            // Insert IndividualID into the appropriate list in the array for their region based on DiseaseState (S, I, or R)
            if (diseaseState == 'S') {
                regions[regionName][0].push_back(individualID);
            } else if (diseaseState == 'I') {
                regions[regionName][1].push_back(individualID);
            } else if (diseaseState == 'R') {
                regions[regionName][2].push_back(individualID);
            }
        }
    }

    // Close the file
    inputFile.close();

    // Display the initial state of the simulation
    cout << "=== Initial State ===\n";
    // For each region, display the counts of susceptible, infected, and recovered individuals
    for (const auto& regionPair : regions) {
        string regionName = regionPair.first;
        const auto& diseaseStates = regionPair.second;
        cout << "Region: " << regionName << "\n";
        cout << "  Susceptible: " << diseaseStates[0].size() << "\n";
        cout << "  Infected:    " << diseaseStates[1].size() << "\n";
        cout << "  Recovered:   " << diseaseStates[2].size() << "\n";
    }

    // Begin a time-based simulation for disease spread
    simulateDiseaseSpread(regions, 25);

    // End of main function
    return 0;
}

// Define a function to simulate disease spread over time
void simulateDiseaseSpread(map<string, array<list<string>, 3>>& regions, int timePeriods) {
    const double infectionProbability = 0.3; // 30% chance to infect
    const double recoveryProbability = 0.1;  // 10% chance to recover

    // For 25 time periods
    for (int t = 1; t <= timePeriods; ++t) {
        cout << "\n=== Time Period: " << t << " ===\n";

        // Temporary data structures to hold state changes
        map<string, list<string>> toInfect;
        map<string, list<string>> toRecover;

        // Iterate through each region in the map
        for (auto& regionPair : regions) {
            string regionName = regionPair.first;
            auto& diseaseStates = regionPair.second;

            // Infection Phase:
            // For each infected individual in the region
            for (const auto& infectedIndividual : diseaseStates[1]) {
                // Attempt to infect susceptible individuals in the same region
                for (const auto& susceptibleIndividual : diseaseStates[0]) {
                    // Generate a random number to determine if infection occurs based on infection probability
                    if ((rand() % 100) < (infectionProbability * 100)) {
                        // If infection occurs:
                        toInfect[regionName].push_back(susceptibleIndividual);
                        // Log that the individual became infected
                        cout << infectedIndividual << " infected " << susceptibleIndividual << " in " << regionName << ".\n";
                    }
                }
            }

            // Recovery Phase:
            // For each infected individual in the region
            for (const auto& infectedIndividual : diseaseStates[1]) {
                // Generate a random number to determine if recovery occurs based on recovery probability
                if ((rand() % 100) < (recoveryProbability * 100)) {
                    // If recovery occurs:
                    toRecover[regionName].push_back(infectedIndividual);
                    // Log that the individual recovered
                }
            }
        }

        // Update disease states based on new infections and recoveries
        for (const auto& regionPair : toInfect) {
            string regionName = regionPair.first;
            for (const auto& individual : regionPair.second) {
                regions[regionName][0].remove(individual); // Move individual from susceptible list to infected list
                regions[regionName][1].push_back(individual);
            }
        }

        for (const auto& regionPair : toRecover) {
            string regionName = regionPair.first;
            for (const auto& individual : regionPair.second) {
                regions[regionName][1].remove(individual); // Move individual from infected list to recovered list
                regions[regionName][2].push_back(individual);
                cout << individual << " in " << regionName << " recovered.\n";
            }
        }

        // Display the state of each region after the current time period
        cout << "\n--- State at Time Period " << t << " ---\n";
        for (const auto& regionPair : regions) {
            string regionName = regionPair.first;
            const auto& diseaseStates = regionPair.second;
            cout << "Region: " << regionName << "\n";
            cout << "  Susceptible: " << diseaseStates[0].size() << "\n";
            cout << "  Infected:    " << diseaseStates[1].size() << "\n";
            cout << "  Recovered:   " << diseaseStates[2].size() << "\n";
        }

        // Optional: Wait or pause briefly to simulate the passage of time between periods
    }
}
