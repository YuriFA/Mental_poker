#include "CardDeck.h"

class Player{
private:
	CardDeck cards;
	double k;
	void gen_k();
public:
	deck encCards;
	Player();
	void encryptCards();
	void showCards();
};