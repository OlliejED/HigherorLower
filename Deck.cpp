//
//  Deck.cpp
//  HigherorLower
//
//  Created by Oliver ED on 27/09/2022.
//

#include "Deck.hpp"


Deck::Deck() {
        
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
int Deck::draw() {
    int firstdraw = cards[12];
    
    for (int i=12; i > 0; i--)
        cards[i] = cards[i-1];
    cards[0] = firstdraw;
    return firstdraw;
}
    // Shuffle deck
void Deck::shuffle() {
                
    for (int i=12; i > -1; i--) {
        int shuffledcard = rand() % 13;
        int temp = cards[i];
        cards[i] = cards[shuffledcard];
        cards[shuffledcard] = temp;
    }
    std::cout << "Deck shuffled" << std::endl;
}
