#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include "CustomerOrder.h"
#include "Station.h"
#include <deque>
#include <iostream>

namespace sdds {
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station {
    private:
        std::deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation = nullptr;

    public:
        Workstation() = default;
        Workstation(const std::string& str);
        Workstation(const Workstation&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(Workstation&&) = delete;
        
        void fill(std::ostream& os = std::cout);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os = std::cout) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
    };
}

#endif // SDDS_WORKSTATION_H
