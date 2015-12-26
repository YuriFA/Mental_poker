#include <vector>

typedef std::vector<unsigned> c_deck;

class CardDeck{
public:
	c_deck enc_cards;//зашифрованная колода
    static const unsigned deckSize;// размер колоды
	CardDeck();
	void shuffle(bool = false);// перетасовка колоды
	void sortDeck(bool = false); // сортировка колоды
	void show(bool = false); // вывод на экран колоды
	void encDeck(double, double); // шифрование колоды
	void decDeck(double, double); // дешифрование колоды
	void showAll(); //вывод на экран всех колод
private:
    c_deck vec; // обычная колода
    void Init();
};