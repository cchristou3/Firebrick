#include "CCard.h"
#include "CPlayer.h"

// constructor 
CCard::CCard(string mName) : mName(mName)
{

}
// destructor
CCard::~CCard()
{
	this->mName.clear();
}

void CCard::Activate(CPlayer* enemyPlayer, CPlayer* currentPlayer)
{
	
}

int CCard::Random(const int n)
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * (n + 1));
}
// setter
void CCard::SetName(string mName) { this->mName = mName; }

// getter
string CCard::GetName() { return this->mName; }


