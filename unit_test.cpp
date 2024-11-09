#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to simulate disease spread over time (same as in main.cpp)
void simulateDiseaseSpread(map<string, array<list<string>, 3>>& regions, int timePeriods);

int main() {
    // Initialize random seed with a fixed value for reproducibility
    srand(0);

    // Create a test region with known individuals
    map<string, array<list<string>, 3>> testRegions;
    testRegions["TestRegion"][0] = {"Person1", "Person2"}; // Susceptible
    testRegions["TestRegion"][1] = {"Person3"};           // Infected
    testRegions["TestRegion"][2] = {};                    // Recovered

    // Display initial state
    cout << "=== Initial Test State ===\n";
    cout << "Region: TestRegion\n";
    cout << "  Susceptible: " << testRegions["TestRegion"][0].size() << "\n";
    cout << "  Infected:    " << testRegions["TestRegion"][1].size() << "\n";
    cout << "  Recovered:   " << testRegions["TestRegion"][2].size() << "\n";

    // Run the simulation for a fixed number of time periods
    simulateDiseaseSpread(testRegions, 5);

    // Display final state
    cout << "\n=== Final Test State ===\n";
    cout << "Region: TestRegion\n";
    cout << "  Susceptible: " << testRegions["TestRegion"][0].size() << "\n";
    cout << "  Infected:    " << testRegions["TestRegion"][1].size() << "\n";
    cout << "  Recovered:   " << testRegions["TestRegion"][2].size() << "\n";

    return 0;
}

void simulateDiseaseSpread(map<string, array<list<string>, 3>>& regions, int timePeriods) {
    const double infectionProbability = 0.3; // 30% chance to infect
    const double recoveryProbability = 0.1;  // 10% chance to recover

    // For the specified number of time periods
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
                    cout << infectedIndividual << " in " << regionName << " recovered.\n";
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
    }
}
