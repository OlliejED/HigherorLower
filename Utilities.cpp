//
//  Utilities.cpp
//  HigherorLower
//
//  Created by Oliver ED on 27/09/2022.
//

#include "Utilities.hpp"

std::string string_to_lower(std::string lower_me) {

    for (int i=0; i < lower_me.size(); i++) {
        lower_me[i] = tolower(lower_me[i]);
    }
    return lower_me;
}

void to_log_file(std::string severity) {
    std::ofstream ErrorFile(LOG_FILE, std::ofstream::app);
    ErrorFile << " There has been a" << severity << " error." << std::endl;
    ErrorFile.close();
}

std::string converter(int card) {
    std::string realCard = "";
    if (card == 1)
        return "Ace";
    else if (card == 11)
        return "Jack";
    else if (card == 12)
        return "Queen";
    else if (card == 13)
        return "King";
    else if (card > 13)
        return "Error, value above 13.";
    else if (card < 1)
        return "Error, value below 1.";
    else {
        realCard = std::to_string(card);
    return realCard;
    }
    return "Converter Error";
}
