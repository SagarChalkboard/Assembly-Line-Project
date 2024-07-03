#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include "Station.h"
#include <iostream>

namespace sdds {
    struct Item {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};
        Item(const std::string& src) : m_itemName(src) {};
    };

    class CustomerOrder {
        std::string m_name {};
        std::string m_product {};
        size_t m_cntItem { 0 };
        Item** m_lstItem { nullptr };
        static size_t m_widthField;
    public:
        CustomerOrder() = default;
        CustomerOrder(const std::string& str);
        CustomerOrder(const CustomerOrder&);
        CustomerOrder& operator=(const CustomerOrder&) = delete;
        CustomerOrder(CustomerOrder&& co) noexcept;
        CustomerOrder& operator=(CustomerOrder&& co) noexcept;
        virtual ~CustomerOrder();
        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os = std::cout) const;
    };
}

#endif // SDDS_CUSTOMERORDER_H
