#include "Utilities.h"
#include <iostream>

namespace sdds {

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        std::string extractedToken;
        size_t endPos = str.find(m_delimiter, next_pos);
        
        if (endPos != std::string::npos) {
            extractedToken = str.substr(next_pos, endPos - next_pos);
            next_pos = endPos + 1;
            more = true;
        } else {
            extractedToken = str.substr(next_pos);
            more = false;
        }
        
        extractedToken = strip(extractedToken);
        
        if (extractedToken.length() > m_widthField) {
            m_widthField = extractedToken.length();
        }
        
        if (extractedToken.empty()) {
            more = false;
            throw std::invalid_argument("ERROR: Token is empty!");
        }
        
        return extractedToken;
    }

    std::string Utilities::strip(const std::string& str) {
        std::string returnVal;
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        
        if (std::string::npos == first) {
            returnVal = str;
        } else {
            returnVal = str.substr(first, (last - first + 1));
        }
        
        return returnVal;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }

} // namespace sdds
