#include <iostream>
#include "gen_rand.h"
#include <time.h>
#include <vector>
#include <algorithm>
#include <string>
#include "Player.h"

using namespace std;

int main()
{
	srand(time(0));

	/*CardDeck cards;	
    cards.shuffle();
    cards.show();
    cout << string(80, '-');
    cards.sortDeck();
    cards.show();*/
	
	Player Alice;
	//Player Bob;
	Alice.encryptData();
	//Alice.showCards();

	cout << endl;
	system("pause");
	return 0;
}