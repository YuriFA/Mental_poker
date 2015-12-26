#include <iostream>
#include <time.h>
#include <string>
#include "Player.h"
#include "gen_rand.h"
using namespace std;

Player::Player(): enc_deck(deck.deckSize),enc_hands(handSize), hands(){
}

Player::~Player(){
	this->k = 0;
	this->z = 0;
}

void Player::gen_kz(double p){
	double tmp_k;
	do{
		tmp_k = gen_rand(MIN_VAL,p-1);
	}while( gcd(tmp_k, p-1) != 1 );
	this->k = tmp_k;

	double x, y;
	int g = gcdex (this->k, p-1, x, y);
	if (g != 1)
		cout << "error! no solution";
	else {
		x = fmod( ( fmod(x, (p-1)) + (p-1) ), (p-1) );
		this->z = x;
	}
}

void Player::show_kz(){
	cout<<"\tK = "<<this->k<<"\n";
	cout<<"\tZ = "<<this->z<<"\n";
}

void Player::showCards(bool isEnc){
	deck.show(isEnc);
}

void Player::encryptDeck(double p, bool isHands){
	if(!isHands)
	{
		deck.encDeck(this->k, p);
		showAll();
		deck.shuffle(true);
		for(c_deck::size_type i = 0; i!=deck.deckSize; i++)
		{
			enc_deck[i] = deck.enc_cards[i];
		}
	}
	else
	{
		for(c_deck::size_type i = 0; i < handSize; i++)
		{			
			 enc_hands[i] = modPow(enc_hands[i],k,p);
		}	
	}
}

void Player::showEncCards(){
	for(c_deck::size_type i = 0; i != deck.deckSize; i++) {
		cout << i << "\t" << Player::enc_deck[i]<< "\n";
    }
}

void Player::chooseCards(c_deck other_deck){
	unsigned newPos = rand() % CardDeck::deckSize;
	for(c_deck::size_type i = 0; i < Player::handSize; i++, newPos = rand() % CardDeck::deckSize)
	{
		enc_deck[i] = other_deck[newPos];
		cout<<"\t"<<i<<"\t"<<other_deck[newPos]<<"\n";
	}
}

void Player::setHands(c_deck rand_cards, double p, bool isOur, bool isEnc){
	for(c_deck::size_type i = 0; i < handSize; i++){
		enc_hands[i] = rand_cards[i];
	}
	if(!isOur)
		decryptDeck(p, isEnc);
	else
		encryptDeck(p, true);

}

void Player::decryptDeck(double p, bool isOur){
	if(!isOur)
	{
		for(c_deck::size_type i = 0; i < handSize; i++){			
			hands.insert(make_pair(enc_hands[i], modPow(enc_hands[i],z,p)));
		}
	}
	else
	{
		for(c_deck::size_type i = 0; i < handSize; i++){
			enc_hands[i] = modPow(enc_hands[i],z,p);
		}
	}

}

void Player::showHands(){
	cout<<"\tENCRYPTCARD"<<"\t"<<"CARD\n";
	int j =0;
    for(type_it i = hands.begin(); i!=hands.end(); i++) {        
		cout <<j++<<"\t"<< i->first << "\t\t" << i->second << endl;
	}
}
void Player::showAll(){
	deck.showAll();
}

const unsigned Player::handSize = 5;