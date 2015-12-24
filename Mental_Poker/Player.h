#include "CardDeck.h"
#include <vector>
#include <map>
#include <Windows.h>
#include <wincrypt.h>

typedef std::map<unsigned, unsigned> sign_deck;

class Player{
private:
	CardDeck			deck;
	double				r;
    HCRYPTPROV          m_hProv;
    HCRYPTKEY           m_hKey;
	void				gen_k();	
    void				Init();		
public:
	sign_deck			encDeck;
	Player();
	~Player();
	void				encryptCards();
	void				showCards();
	void _stdcall		encryptData();
	void _stdcall		decryptData();
};