#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include "Workstation.h"
#include <iostream>
#include <vector>

namespace sdds {
    class LineManager {
        std::vector<Workstation*> m_activeLine {}; // Vector to hold active workstations in the assembly line
        size_t m_cntCustomer { 0 }; // Count of pending customer orders
        Workstation* m_firstStation { nullptr }; // Pointer to the first station in the assembly line

    public:
        // Default Constructor
        LineManager() = default;

        // Constructor: Loads assembly line setup from file, sets up station connections, and identifies first station
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);

        // Reorders workstations in the active assembly line based on station connections
        void reorderStations();

        // Executes one iteration of operations on all workstations in the assembly line
        bool run(std::ostream& os = std::cout);

        // Displays the current state of all active stations in the assembly line
        void display(std::ostream& os = std::cout) const;
    };
}

#endif // SDDS_LINEMANAGER_H
