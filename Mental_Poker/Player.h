#include "CardDeck.h"
#include <map>
#include <float.h>

#define MIN_VAL 99999

typedef std::map<unsigned, unsigned> sign_deck;

class Player{
private:
	CardDeck			deck;
	double				k;
	double				z;
    void				Init();		
public:
	Player();
	~Player();
	void				gen_kz(double);
	void				show_kz();
	void				encryptDeck(double);
	void				showCards(bool);
};