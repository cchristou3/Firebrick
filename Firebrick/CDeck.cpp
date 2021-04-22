#include "CDeck.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include "CBasicMinion.h"
#include "CFireball.h"
#include "CLightning.h"
#include "CBless.h"
#include "CVampire.h"
#include "CWall.h"
#include "CHorde.h"
#include "CLeech.h"
#include "CTrample.h"
#include "CSword.h"
#include "CArmour.h"

CDeck::CDeck()
{
	mTop = 0;
}
CDeck::~CDeck()
{	

}
bool CDeck::IsFull()
{
	return (mTop >= DECK_SIZE);
}
bool CDeck::IsEmpty()
{
	return (mTop == 0);
}
void CDeck::Push(unique_ptr<CCard> newData)
{
	if (!IsFull()) 
	{
		mpData[mTop] = move(newData);
		mTop++;
	}
	else
	{
		cout << "stack is full!" << endl;
	}
}
void CDeck::Pop(unique_ptr<CCard> &oldData)
{
	if (!IsEmpty()) 
	{
		mTop--;
		oldData = move(mpData[mTop]);
	}
	else 
	{
		cout << "stack is empty!" << endl;
	}
}
unique_ptr<CCard> CDeck::Pop()
{
	if (!IsEmpty())
	{		
		mTop--;
		// return the Card that got popped 
		return move(this->mpData[mTop]);
	}
	else
	{
		cout << "stack is empty!" << endl;
		return nullptr;
	}
}
void CDeck::DisplayDeck() 
{
	for (int i = 0; i < mTop; i++)
	{
		// Prints type and name of all cards of the deck
		cout << " " << mpData[i]->GetName() << endl;
	}
	cout << endl;
}

string CDeck::GetCardName(int position)
{
	return this->mpData[position]->GetName();
}

int CDeck::GetTop()
{
	return mTop;
}

// handling player's deck
// puts all the words separeted by " " within a container
template <class Container>
void split(const string& str, Container& cont)
{
	istringstream iss(str);
	copy(std::istream_iterator<std::string>(iss),
		istream_iterator<std::string>(),
		back_inserter(cont));
}

CDeck::CDeck(string textFilePathWay)
{
	mTop = 0;

	enum ECards { BasicMinion = 1, Fireball = 2, Lightning = 3, Bless = 4, Vampire = 5, Wall = 6, 
		Horde = 7, Trample = 8, Leech = 9, Sword = 10, Armour = 11
	};

	// declare the ifstreams for the file
	ifstream file;

	// get access to the text files
	file.open(textFilePathWay);

	// create the deck of the player
	string line;
	// create a vector
	vector<string> words;
	if (file.is_open())
	{
		while (getline(file, line)) // go line by line
		{
			// get all the words from each line and put them in the vector
			split(line, words);
			int type = stoi(words[0]);
			switch (type)
			{
			case BasicMinion:
			{
				// creates a card of type 1
				// polymorphism				
				unique_ptr<CBasicMinion> pCard = make_unique<CBasicMinion>(words[1], stoi(words[2]), stoi(words[3]));
				// puts the card inside the deck
				this->Push(std::move(pCard));
				pCard.release();
				break;
			}
			case Fireball:
			{
				unique_ptr<CFireball> pCard = make_unique<CFireball>(words[1], stoi(words[2]));
				// puts the card inside the deck
				this->Push(std::move(pCard));
				pCard.release();
				break;
			}
			case Lightning:
			{
				unique_ptr<CLightning> pCard = make_unique<CLightning>(words[1], stoi(words[2]));
				// puts the card inside the deck
				this->Push(std::move(pCard));
				pCard.release();
				break;
			}
			case Bless:
			{
				unique_ptr<CBless> pCard = make_unique<CBless>(words[1], stoi(words[2]));
				// puts the card inside the deck
				this->Push(std::move(pCard));
				pCard.release();
				break;
			}
			case Vampire:
			{
				unique_ptr<CVampire> pCard = make_unique<CVampire>(words[1], stoi(words[2]), stoi(words[3]), stoi(words[4]));
				// puts the card inside the deck
				this->Push(std::move(pCard));
				pCard.release();
				break;
			}
			case Wall:
			{
				unique_ptr<CWall> pCard = make_unique<CWall>(words[1], stoi(words[2]), stoi(words[3]));
				// puts the card inside the deck
				this->Push(std::move(pCard));
				pCard.release();
				break;
			}
			case Horde:
			{
				// rat's default attack increment is one attack point
				unique_ptr<CHorde> pCard = make_unique<CHorde>(words[1], stoi(words[2]), stoi(words[3]), 1);
				// puts the card inside the deck
				this->Push(std::move(pCard));
				pCard.release();
				break;
			}
			case Trample:
			{
				unique_ptr<CTrample> pCard = make_unique<CTrample>(words[1], stoi(words[2]), stoi(words[3]));
				// puts the card inside the deck
				this->Push(std::move(pCard));
				pCard.release();
				break;
			}
			case Leech:
			{		
				 // leech's default healling is two health points
				unique_ptr<CLeech> pCard = make_unique<CLeech>(words[1], stoi(words[2]), stoi(words[3]), 2);
				// puts the card inside the deck
				this->Push(std::move(pCard));
				pCard.release();
				break;
			}
			case Sword:
			{			
				unique_ptr<CSword> pCard = make_unique<CSword>(words[1], stoi(words[2]));
				// puts the card inside the deck
				this->Push(std::move(pCard));
				pCard.release();
				break;
			}
			case Armour:
			{
				unique_ptr<CArmour> pCard = make_unique<CArmour>(words[1], stoi(words[2]));
				// puts the card inside the deck
				this->Push(std::move(pCard));
				pCard.release();
				break;
			}
			default:
				break;
			}

			vector<string>::iterator it;
			for (it = words.begin(); it != words.end(); it++)
			{
				it->erase();
			}
			words.clear(); // resets the vector for the next line 
		}
		file.close();
	}
	else
	cout << "Unable to open file with pathway: " << textFilePathWay << endl;
}

void CDeck::Shuffle()
{
	int lastIndex = mTop - 1;
	random_shuffle(this->mpData, this->mpData + lastIndex);
}