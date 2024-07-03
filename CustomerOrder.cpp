#include "CustomerOrder.h"
#include "Utilities.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using std::endl;

namespace sdds {

    // Initialize static member variable
    size_t CustomerOrder::m_widthField = 0;

    // Constructor: Extracts data from str and initializes object
    CustomerOrder::CustomerOrder(const std::string& str) {
        size_t next_pos = 0;
        bool more = true;
        Utilities util {};

        // Extract customer name and product
        m_name = util.extractToken(str, next_pos, more);
        m_product = util.extractToken(str, next_pos, more);

        // Count number of items
        size_t startCpy = next_pos;
        while (more) {
            util.extractToken(str, next_pos, more);
            m_cntItem++;
        }

        // Reset position
        next_pos = startCpy;
        more = true;

        // Allocate memory for array of pointers to Item objects
        m_lstItem = new Item*[m_cntItem];
        for (size_t i = 0; i < m_cntItem; i++) {
            m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
        }

        // Update m_widthField if necessary
        m_widthField = std::max(m_widthField, util.getFieldWidth());
    }

    // Move constructor: Transfer ownership of resources from 'co' to 'this'
    CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept {
        *this = std::move(co);
    }

    // Move assignment operator: Transfer ownership of resources from 'co' to 'this'
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept {
        if (this != &co) {
            // Deallocate current resources
            for (size_t i = 0; i < m_cntItem; i++) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            // Transfer ownership of 'co' resources to 'this'
            m_name = co.m_name;
            co.m_name = "";
            m_product = co.m_product;
            co.m_product = "";
            m_cntItem = co.m_cntItem;
            co.m_cntItem = 0;
            m_lstItem = co.m_lstItem;
            co.m_lstItem = nullptr;
        }
        return *this;
    }

    // Destructor: Clean up dynamically allocated memory
    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    // Checks if all items in the order have been filled
    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (!m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    // Checks if all items with name 'itemName' have been filled
    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    // Fills an item in the order using the specified station
    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
                } else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << " out of stock" << endl;
                }
            }
        }
    }

    // Displays the state of the current object
    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << endl;
        for (size_t i = 0; i < m_cntItem; i++) {
            os << "[" << std::right << std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber << "] ";
            os << std::left << std::setfill(' ') << std::setw(m_widthField) << m_lstItem[i]->m_itemName << "   - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED");
            os << std::endl;
        }
    }

} // namespace sdds
