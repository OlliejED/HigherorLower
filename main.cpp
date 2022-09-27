#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <ctime>
#include <chrono>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/foreach.hpp>

using boost::property_tree::ptree;
using namespace std;


//    GLOBALS

bool choice;
string higher, lower;
string LOG_FILE = "error.log";
int num_rounds;

//
class Deck {
private:
    // Introducing cards array
    int cards[13];

public:
    Deck() {
        
        srand(time(NULL));
        
        cards[0] = 1;
        cards[1] = 2;
        cards[2] = 3;
        cards[3] = 4;
        cards[4] = 5;
        cards[5] = 6;
        cards[6] = 7;
        cards[7] = 8;
        cards[8] = 9;
        cards[9] = 10;
        cards[10] = 11;
        cards[11] = 12;
        cards[12] = 13;
    }
    // Draw new cards
    int draw() {
        int firstdraw = cards[12];

        for (int i=12; i > 0; i--)
            cards[i] = cards[i-1];
        cards[0] = firstdraw;
        return firstdraw;
    }
    // Shuffle deck
    void shuffle() {
                
        for (int i=12; i > -1; i--) {
            int shuffledcard = rand() % 13;
            int temp = cards[i];
            cards[i] = cards[shuffledcard];
            cards[shuffledcard] = temp;
        }
        cout << "Deck shuffled" << endl;
    }
} ;


//    HEADER FUNCTIONS

bool turn(int carda, int cardb, bool choice);
int royal_conversion(int carda, int cardb);

//    Funct. to convert word to lower case:

string string_to_lower(string lower_me) {

    for (int i=0; i < lower_me.size(); i++) {
        lower_me[i] = tolower(lower_me[i]);
    }
    return lower_me;
}

//    Func. to record an error into a file:
void to_log_file(string severity) {
    ofstream ErrorFile(LOG_FILE, ofstream::app);
    ErrorFile << " There has been a" << severity << " error." << endl;
    ErrorFile.close();
}



//    Func. to convert the card num value into strings:
string converter(int card) {
    string realCard = "";
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
        realCard = to_string(card);
    return realCard;
    }
    return "Converter Error";
}


//    Func. to complete a turn of the game:
bool turn(int carda, int cardb, bool choice) {

    string realCard = converter(cardb);

    if (choice == false && cardb < carda) {
        // Card was lower and user guessed lower
        cout << "Correct!" << endl;
        cout << "The card was a " + realCard << endl << endl;
        return true;
    }
    else if (choice == true && cardb > carda) {
        //Card was higher and guessed higher
        cout << "Correct!" << endl;
        cout << "The card was a " + realCard << endl << endl;
        return true;
    }
    else if (carda == cardb) {
        //Cards are the same
        cout << "The cards are the same, next turn!" << endl;
        cout << "The card was a " + realCard << endl << endl;
        return true;
    }
    else {
        //Any other result
        cout << "Incorrect, you lose!." << endl;
        cout << "The card was a " + realCard << endl << endl;
        return false;
    }
    // Never reached. Just keeps hte compiler happy
    return false;
}


//    Func. MAIN:
int main() {
    // clear buffer
    cout << endl;
    srand(time(NULL));

    try {
        ptree pt;
        
        read_ini("cfg.ini", pt);
        LOG_FILE = pt.get <string>("title.log");
        // cout << LOG_FILE << endl;
        num_rounds = pt.get <int>("title.total_rounds");
        // cout << num_rounds << endl;
    }
    catch(std::exception & e) {
        cout << "file reading error, expected @ cfg.ini" << endl;
        to_log_file("file reading " + string(e.what()));
        return 1;
    }

    Deck stack;
    stack.shuffle();
    
    bool winner = true;
    //Roll starting cards
    int previouscard = stack.draw();
    int nextcard = stack.draw();
    bool repeating_turn = true;
    string card1 = converter(previouscard);

    cout << "The starting card is a " + card1 << endl;

    //Loops through the turns
    for (int i=0; i < 4; i++) {
        cout << "Is the next card higher, or lower?" << endl;
        //Checks to see if the user is repeating a turn
        if (!repeating_turn) {
            previouscard = nextcard;
            nextcard = stack.draw();
        }

        string realChoice = "";
        cin >> realChoice;
        realChoice = string_to_lower(realChoice); // converts to lowercase

        if (realChoice == "quit")
            return 0;
        else if (realChoice == "lower")
            choice = false;
        else if (realChoice == "higher")
            choice = true;
        else {
            cout << "Error, make sure you entered either higher or lower " << endl << endl;
            to_log_file("input");
            i = i-1;
            repeating_turn = true;
            continue;
        }

        repeating_turn = false;
        //Runs the turn() func. to play the turn
        winner = turn(previouscard, nextcard, choice);
        if (!winner) {
            break;
        }
    }
    //Game end messages
    if (winner) { // identical to if (winner == true)
        cout << "Congratulations, you've won!" << endl;
    }
    else {
        cout << "You lost, you suck!" << endl;
    }
}

