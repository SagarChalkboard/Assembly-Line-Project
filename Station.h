#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>
#include <string>

namespace sdds {
    class Station {
    private:
        size_t m_id {};
        std::string m_item {};
        std::string m_description {};
        size_t m_serial {};
        size_t m_quantity { 0 };
        inline static size_t m_widthField { 0 };
        inline static size_t id_generator { 0 };

    public:
        Station() = default;
        Station(const std::string& str);

        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}

#endif // SDDS_STATION_H
