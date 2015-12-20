#include "CardDeck.h"
#include <vector>
#include <map>

typedef std::map<unsigned, unsigned> sign_deck;

class Player{
private:
	CardDeck deck;
	double k;
	void gen_k();
public:
	sign_deck encDeck;
	Player();
	void encryptCards();
	void showCards();
};