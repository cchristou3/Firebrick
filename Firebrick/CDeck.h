#pragma once
#include <iostream>
#include <string>
#include "CCard.h"
using namespace std;
const int DECK_SIZE = 35;
class CDeck {
private:
	int mTop;
	unique_ptr<CCard> mpData[DECK_SIZE];
public:
	// Constructor of the class CDeck, only initializes the mTop (deck's size) to 0.
	CDeck();

	// 2nd constructor of the class CDeck, parameter: the pathway of the text file that contains the cards details.
	// Reads all the data from the text file and inserts it into the mpData data structure (aka the player's deck).
	CDeck(string textFilePathWay);
	
	// Destructor
	~CDeck();
	
	// Puts an element on the top of the stack/deck, parameter: an object of type CCard*.
	void Push(unique_ptr<CCard> newData);

	// Removes the last Card that was inserted into the stack/deck
	// Parameter: the card that is about to get removed
	void Pop(unique_ptr<CCard> &oldData);

	// Returns a pointer of the latest Card that was inserted into the stack/deck,
	// while also removing it from the stack/deck.
	unique_ptr<CCard> Pop();

	// Returns true if the stack/deck is empty. Otherwise, it returns false
	bool IsEmpty();

	// Returns true if the stack/deck is full. Otherwise, it returns false
	bool IsFull();

	// Displays all the contents of the stack/deck
	void DisplayDeck();

	// Returns the name of the card in a position, parameter: the position of the card in the deck
	string GetCardName(int position);	

	// Returns the size of the deck
	int GetTop();

	// Shuffles the deck
	void Shuffle();
};

