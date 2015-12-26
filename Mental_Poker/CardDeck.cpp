#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <string>
#include "CardDeck.h"
#include "gen_rand.h"

using namespace std;

CardDeck::CardDeck(): vec(deckSize), enc_cards(deckSize){
	this->Init(); 
}

void CardDeck::shuffle(bool isEnc){
    srand(time(0));
    unsigned newPos = rand() % deckSize;
    for(c_deck::size_type i = 0; i!=deckSize; i++, newPos = rand() % deckSize)
        if(!isEnc)
			swap(vec[i], vec[newPos]);
		else
			swap(enc_cards[i],enc_cards[newPos]);
}

void CardDeck::sortDeck(bool isEnc){
	if(!isEnc)
		sort(vec.begin(), vec.end());
	else
		sort(enc_cards.begin(), enc_cards.end());

}

void CardDeck::show(bool isEnc){
    for(c_deck::size_type i = 0; i!=deckSize; i++)
        if(!isEnc)
			cout << i << "\t" << vec[i] << endl;
		else
			cout << i << "\t" << enc_cards[i] << endl;
}

void CardDeck::showAll(){
	cout<<"CARDS"<<"\t"<<"ENCRYPT CARDS"<<"\n";
	for(c_deck::size_type i = 0; i!=deckSize; i++){
		cout << vec[i] << "\t" << enc_cards[i] << endl;
	}
}
   
void CardDeck::Init(){
    for(c_deck::size_type i = 0; i!=deckSize; i++) {
		vec[i] = i+2;
    }
}

void CardDeck::encDeck(double k, double p){
	for(c_deck::size_type i = 0; i!=deckSize; i++) {
		enc_cards[i] = modPow(vec[i],k,p);
    }
}

void CardDeck::decDeck(double z, double p){
	for(c_deck::size_type i = 0; i!=deckSize; i++) {
		enc_cards[i] = modPow(enc_cards[i],z,p);
    }
}
const unsigned CardDeck::deckSize = 52;