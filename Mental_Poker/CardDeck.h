#include <vector>

typedef std::vector<unsigned> deck;

class CardDeck{
public:
	CardDeck();
	void shuffle();
	void sortDeck();
	void show();
	void encDeck();
	deck enc_carts;

private:
    static const unsigned deckSize;
    deck vec;
    void Init();
};