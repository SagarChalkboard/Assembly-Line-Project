#include "LineManager.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <algorithm>

namespace sdds {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::ifstream infile(file);
        // Check if the file opened successfully
        if (!infile) {
            throw "ERROR: Unable to open file";
        }

        Utilities utils {};
        std::string str {};
        size_t next_pos { 0 };
        bool more { true };

        // Vectors to determine the first station
        std::vector<std::string> leftStations;
        std::vector<std::string> rightStations;

        // Read each line from the file
        while (std::getline(infile, str)) {
            next_pos = 0;
            std::string tempCurrStation = utils.extractToken(str, next_pos, more);
            if (more) {
                std::string tempNextStation = utils.extractToken(str, next_pos, more);
                leftStations.push_back(tempCurrStation);
                rightStations.push_back(tempNextStation);
            }

            // Find current station in stations vector and add to active line
            auto currStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station){
                return station->getItemName() == tempCurrStation;
            });
            m_activeLine.push_back(*currStation);

            // Find next station in stations vector and set as next station
            if (more) {
                auto nextStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station){
                    return station->getItemName() == tempNextStation;
                });
                (*currStation)->setNextStation(*nextStation);
            }
        }

        // Determine the first station based on station connections
        std::string firstStationName;
        for (const auto& leftStation : leftStations) {
            if (std::find(rightStations.begin(), rightStations.end(), leftStation) == rightStations.end()) {
                firstStationName = leftStation;
                break;
            }
        }

        // Set the first station
        auto firstStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station){
            return station->getItemName() == firstStationName;
        });
        m_firstStation = *firstStation;

        // Set count of pending customer orders
        m_cntCustomer = g_pending.size();
    }

    // Reorders the workstations in active line based on connections
    void LineManager::reorderStations() {
        std::vector<Workstation*> reorderedStations;
        Workstation* currentStation = m_firstStation;
        while (currentStation != nullptr) {
            reorderedStations.push_back(currentStation);
            currentStation = currentStation->getNextStation();
        }
        m_activeLine = reorderedStations;
    }

    // Performs one iteration of operations on all workstations in active line
    bool LineManager::run(std::ostream& os) {
        static size_t iterationCount = 1;
        os << "Line Manager Iteration: " << iterationCount << std::endl;
        ++iterationCount;

        // Move pending orders to first station
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        // Execute fill() and attemptToMoveOrder() on each workstation
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto& station){
            station->fill(os);
            station->attemptToMoveOrder();
        });

        // Check if all customer orders have been completed or are incomplete
        return g_completed.size() + g_incomplete.size() == m_cntCustomer;
    }

    // Display all stations in active line
    void LineManager::display(std::ostream& os) const {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto station){
            station->display(os);
        });
    }
}
