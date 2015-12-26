#include "CardDeck.h"
#include <map>
#include <float.h>

#define MIN_VAL 999999

typedef std::map<unsigned, unsigned> c_section;
typedef std::map<unsigned, unsigned>::iterator type_it;

class Player{
private:
	CardDeck			deck;	//колода
	c_section			hands; //карты на руке
	double				k; // k : gcd(k, p-1) = 1
	double				z; // z : k*z = 1 mod(p-1)
public:
	c_deck				enc_hands;
	c_deck				enc_deck;
    static const unsigned handSize;
	Player();
	~Player();
	void				gen_kz(double);//генерация k и z
	void				show_kz();//вывод k и z
	void				encryptDeck(double, bool = false);// зашифровать колоду если 2 пар-р true то карты на руке
	void				decryptDeck(double, bool = false);//расшифровать
	void				showCards(bool = false);//вывод на экран колоды
	void				showEncCards();//вывод на экран зашифрованных карт
	void				chooseCards(c_deck);//выборка карт из чужой колоды
	void				setHands(c_deck, double, bool = false, bool = false);// передача карт на руки либо для себя либо для другого игрока
	void				showHands();//вывод карт на руке
	void				showAll();//вывод колоды зашифрованной и нешифрованной

};