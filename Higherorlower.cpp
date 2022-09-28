#include "Higherorlower.hpp"
#include "Utilities.hpp"
#include "Deck.hpp"

using boost::property_tree::ptree;


//    GLOBALS

bool choice;

//    Func. to complete a turn of the game:
bool turn(int carda, int cardb, bool choice) {

    std::string realCard = converter(cardb);

    if (choice == false && cardb < carda) {
        // Card was lower and user guessed lower
        std::cout << "Correct!" << std::endl;
        std::cout << "The card was a " + realCard << std::endl << std::endl;
        return true;
    }
    else if (choice == true && cardb > carda) {
        //Card was higher and guessed higher
        std::cout << "Correct!" << std::endl;
        std::cout << "The card was a " + realCard << std::endl << std::endl;
        return true;
    }
    else if (carda == cardb) {
        //Cards are the same
        std::cout << "The cards are the same, next turn!" << std::endl;
        std::cout << "The card was a " + realCard << std::endl << std::endl;
        return true;
    }
    else {
        //Any other result
        std::cout << "Incorrect, you lose!." << std::endl;
        std::cout << "The card was a " + realCard << std::endl << std::endl;
        return false;
    }
    // Never reached. Just keeps hte compiler happy
    return false;
}


//    Func. MAIN:
int game() {
    // clear buffer
    std::cout << std::endl;
    srand(time(NULL));

    try {
        ptree pt;
        
        read_ini("cfg.ini", pt);
        LOG_FILE = pt.get <std::string>("title.log");
        // cout << LOG_FILE << endl;
        // int num_rounds = pt.get <int>("title.total_rounds");
        // cout << num_rounds << endl;
    }
    catch(std::exception & e) {
        std::cout << "file reading error, expected @ cfg.ini" << std::endl;
        to_log_file("file reading " + std::string(e.what()));
        return 1;
    }

    Deck stack;
    stack.shuffle();
    
    bool winner = true;
    //Roll starting cards
    int previouscard = stack.draw();
    int nextcard = stack.draw();
    bool repeating_turn = true;
    std::string card1 = converter(previouscard);

    std::cout << "The starting card is a " + card1 << std::endl;

    //Loops through the turns
    for (int i=0; i < 4; i++) {
        std::cout << "Is the next card higher, or lower?" << std::endl;
        //Checks to see if the user is repeating a turn
        if (!repeating_turn) {
            previouscard = nextcard;
            nextcard = stack.draw();
        }

        std::string realChoice = "";
        std::cin >> realChoice;
        realChoice = string_to_lower(realChoice); // converts to lowercase

        if (realChoice == "quit")
            return 0;
        else if (realChoice == "lower")
            choice = false;
        else if (realChoice == "higher")
            choice = true;
        else {
            std::cout << "Error, make sure you entered either higher or lower " << std::endl << std::endl;
            Utilities:to_log_file("input");
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
        std::cout << "Congratulations, you've won!" << std::endl;
    }
    else {
        std::cout << "You lost, you suck!" << std::endl;
    }
    return 0;
}

