#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <iostream>

namespace sdds {
    class Utilities {
    private:
        size_t m_widthField { 1 };
        inline static char m_delimiter {};
    public:
        Utilities() = default;
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        std::string strip(const std::string& str);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };
}

#endif // SDDS_UTILITIES_H
