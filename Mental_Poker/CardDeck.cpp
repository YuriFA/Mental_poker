#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <string>
#include "CardDeck.h"

using namespace std;

CardDeck::CardDeck(): vec(deckSize){
	this->Init(); 
}

void CardDeck::shuffle(bool eDeck){
    srand(time(0));
    unsigned newPos = rand() % deckSize;
    for(deck::size_type i = 0; i!=deckSize; i++, newPos = rand() % deckSize)
        if(!eDeck)
			swap(vec[i], vec[newPos]);
		else
			swap(enc_carts[i],enc_carts[newPos]);
}

void CardDeck::sortDeck(){
	sort(vec.begin(), vec.end());
}

void CardDeck::show(){
    for(deck::size_type i = 0; i!=deckSize; i++)
        cout << i << "\t" << vec[i] << endl;
}
   
void CardDeck::Init(){
    for(deck::size_type i = 0; i!=deckSize; i++) {
		vec[i] = i;
    }
}

const unsigned CardDeck::deckSize = 52;