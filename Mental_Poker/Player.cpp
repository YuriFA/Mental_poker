#include <iostream>
#include <time.h>
#include "Player.h"
#include "gen_rand.h"
using namespace std;

void MyHandleError(char *s);

Player::Player(){
	this->Init();
}

Player::~Player(){
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
	cout<<"K = "<<this->k<<"\n";
	cout<<"Z = "<<this->z<<"\n";
}

void Player::showCards(bool isEnc){
	deck.show(isEnc);
}

void Player::encryptDeck(double p){
	Player::deck.encDeck(this->k, p);
}

void Player::Init(){	
}