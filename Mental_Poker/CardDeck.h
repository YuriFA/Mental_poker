#include <vector>

typedef std::vector<unsigned> c_deck;

class CardDeck{
public:
	c_deck enc_cards;
    static const unsigned deckSize;
	CardDeck();
	void shuffle(bool = false);
	void sortDeck(bool = false);
	void show(bool = false);
	void encDeck(double, double);
	void decDeck(double, double);
	void showAll();
private:
    c_deck vec;
    void Init();
};