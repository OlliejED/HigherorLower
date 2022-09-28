//
//  Deck.hpp
//  HigherorLower
//
//  Created by Oliver ED on 27/09/2022.
//

#pragma once

#include <iostream>

class Deck{
private:
    int cards[13];
    
public:
    Deck();
    int draw();
    void shuffle ();
} ;
