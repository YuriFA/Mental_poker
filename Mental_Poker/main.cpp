#include <iostream>
#include "gen_rand.h"
#include <time.h>
using namespace std;

class Client{//класс описывающий клиента для обмена ключа
private:
	double c,d;
public:
	double q1, q2, q3, p, u1,u2,u3;
	Client(double p)
	{
		this->p = p;
		this->gen_c();
		this->gen_d();
		cout << "\n\tsecret c : " << this->c << "\n\t d : " << this->d;
	}
	void gen_d()
	{
		//this->v = modPow(this->s,2,this->n);
	}
	void gen_c()
	{
		double c;
		do{
			c = gen_rand(1, (this->p - 1));
		} while (gcd(c,this->p)!=1);
		this->c = c;
	}
	void gen_Q()
	{
		this->q1 = gen_prime(1,p-1);
		this->q2 = gen_prime(1,p-1);
		this->q3 = gen_prime(1,p-1);
	}
	void gen_U()
	{
		this->u1 = modPow(this->q1, this->c, p);
		this->u2 = modPow(this->q2, this->c, p);
		this->u3 = modPow(this->q3, this->c, p);
	}
};

int main()
{
	srand(time(NULL));
	double p = gen_prime(100, 1000);
	
	cout << "p : " << p;
	cout << "\n\nAlice : ";	
	Client Alice(p);
	Client Bob(p);
	Alice.gen_Q();
	Bob.q1 = Alice.q1;
	Bob.q2 = Alice.q2;
	Bob.q3 = Alice.q3;
	Alice.gen_U();

	system("pause");
	return 0;
}