#include <iostream>
#include <time.h>
#include <algorithm>
#include <string>
#include "Player.h"
#include "gen_rand.h"

using namespace std;

int main()
{
	srand(time(0));

	double p;
	p = gen_prime(MIN_VAL, 999999);
	/*CardDeck cards;	
    cards.shuffle();
    cards.show();
    cout << string(80, '-');
    cards.sortDeck();
    cards.show();*/
	
	Player Alice;
	//Player Bob;
	//Alice.showCards();
	Alice.gen_kz(p);
	Alice.show_kz();
	Alice.encryptDeck(p);
	Alice.showCards(false);
	Alice.showCards(true);
	cout << endl;
	system("pause");
	return 0;
}