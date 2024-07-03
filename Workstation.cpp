#include "Workstation.h"
#include <iostream>

namespace sdds {
    // ========== GLOBAL VARIABLES ===========
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    // Receives a reference to an unmodifiable reference to std::string and passes it to the Station base class
    Workstation::Workstation(const std::string& str) : Station(str) {}

    // Modifier fills the order at the front of the queue if there are CustomerOrders in the queue
    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }

    // Attempts to move the order at the front of the queue to the next station
    bool Workstation::attemptToMoveOrder() {
        bool moved = false;
        if (!m_orders.empty()) {
            if (getQuantity() == 0 || m_orders.front().isItemFilled(getItemName())) {
                if (!m_pNextStation) {
                    if (m_orders.front().isOrderFilled()) {
                        g_completed.push_back(std::move(m_orders.front()));
                    } else {
                        g_incomplete.push_back(std::move(m_orders.front()));
                    }
                } else {
                    *m_pNextStation += std::move(m_orders.front());
                }
                m_orders.pop_front();
                moved = true;
            }
        }
        return moved;
    }

    // Stores the address of the referenced Workstation object in the pointer to the m_pNextStation
    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    // This query returns the address of next Workstation
    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    // This query inserts the name of the Item for which the current object is responsible into stream os
    void Workstation::display(std::ostream& os) const {
        os << getItemName() << " --> ";
        (m_pNextStation) ? (os << m_pNextStation->getItemName()) : (os << "End of Line");
        os << "\n";
    }

    // Moves the CustomerOrder referenced in parameter newOrder to the back of the queue.
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}
