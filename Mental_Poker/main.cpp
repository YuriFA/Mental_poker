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
	p = gen_prime(MIN_VAL, 9999999);//выбираем p
	
	cout<<"Alice:\n";//Создаем игрока Alice.
	Player Alice;
	Alice.gen_kz(p);//Генерируем k : gcd(k,p-1)=1 и z : k*z = 1 (mod p-1)
	Alice.show_kz();//Выводим

	
	cout<<"Bob:\n";//Создаем игрока Bob.
	Player Bob;
	Bob.gen_kz(p);//Генерируем k : gcd(k,p-1)=1 и z : k*z = 1 (mod p-1)
	Bob.show_kz();//Выводим

	cout << string(80, '-');
	cout << endl;

	Alice.encryptDeck(p);//Алиса шифрует колоду и передает Бобу
	
	cout << string(80, '-');
	cout << endl;
	cout<<"Bob choose for Alice : \n\n";
	Bob.chooseCards(Alice.enc_deck);//Боб выбирает 5 случайных карт из колоды Алисы(зашифрованной) и передает Алисе
	Alice.setHands(Bob.enc_deck, p);//Алиса получает 5 карт 

	cout << string(80, '-');
	cout << endl;
	cout<<"ALICE HANDS:\n\n";

	Alice.showHands();//Выводим карты Алисы в руке
	
	cout << string(80, '-');
	cout << endl;
	cout<<"Bob choose for himself : \n\n";
	Bob.chooseCards(Alice.enc_deck);//Боб выбирает карты для себя
	Bob.setHands(Bob.enc_deck, p, true);//Шифрует их своим ключом и передает Алисе

	Alice.setHands(Bob.enc_hands, p, false, true);//Алиса дешифрует карты переданные Бобом и передает ему

	Bob.setHands(Alice.enc_hands,p);//Боб дешифрует полученные карты и теперь он знает что это за карты

	cout << string(80, '-');
	cout << endl;
	cout<<"BOB HANDS:\n\n";
	Bob.showHands();//Выводим карты Боба в руке

	cout << endl;
	system("pause");
	return 0;
}