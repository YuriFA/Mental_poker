#include <vector>

typedef std::vector<unsigned> deck;

class CardDeck{
public:
	CardDeck();
	void shuffle(bool);
	void sortDeck();
	void show(bool);
	void encDeck(double, double);
	void decDeck(double, double);
	deck enc_cards;

private:
    static const unsigned deckSize;
    deck vec;
    void Init();
};