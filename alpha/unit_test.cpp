#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>

// Function prototype
void simulateDiseaseSpread(std::map<std::string, std::array<std::list<std::string>, 3>>& regions, int timePeriods);

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Initialize a controlled regions map
    std::map<std::string, std::array<std::list<std::string>, 3>> regions;

    // Test Case 1: Verify infection and recovery over one time period
    regions["TestRegion"][0] = {"Susceptible1", "Susceptible2"};
    regions["TestRegion"][1] = {"Infected1"};
    regions["TestRegion"][2] = {};

    // Display initial state
    std::cout << "=== Unit Test: Initial State ===\n";
    for (const auto& regionPair : regions) {
        std::string regionName = regionPair.first;
        const auto& diseaseStates = regionPair.second;
        std::cout << "Region: " << regionName << "\n";
        std::cout << "  Susceptible: " << diseaseStates[0].size() << "\n";
        std::cout << "  Infected:    " << diseaseStates[1].size() << "\n";
        std::cout << "  Recovered:   " << diseaseStates[2].size() << "\n";
    }

    // Call the simulateDiseaseSpread function for 1 time period
    simulateDiseaseSpread(regions, 1);

    // Verify the results
    std::cout << "\n=== Unit Test: Post-Simulation State ===\n";
    for (const auto& regionPair : regions) {
        std::string regionName = regionPair.first;
        const auto& diseaseStates = regionPair.second;
        std::cout << "Region: " << regionName << "\n";
        std::cout << "  Susceptible: " << diseaseStates[0].size() << "\n";
        std::cout << "  Infected:    " << diseaseStates[1].size() << "\n";
        std::cout << "  Recovered:   " << diseaseStates[2].size() << "\n";
    }

    // Assertions (Example, actual results may vary due to randomness)
    // Since the simulation uses randomness, we can't predict exact outcomes,
    // but we can check that the total number of individuals remains constant.
    size_t totalIndividuals = regions["TestRegion"][0].size() +
                              regions["TestRegion"][1].size() +
                              regions["TestRegion"][2].size();
    assert(totalIndividuals == 3); // We started with 3 individuals

    std::cout << "\nUnit test completed successfully.\n";

    return 0;
}
