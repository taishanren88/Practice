#include <iostream>
#include <vector>

using namespace std;

/*
Who are the actors:
Card, Deck, Hand,..

Centralized behaviors:
Hand has a score
Deck can shuffle/deal

*/
enum class Suit {

};

struct Card {

public:
	virtual int getGetValue() const;
		Suit suit;
	int value;

};

class Deck{
public:
	virtual void deal() = 0;
	virtual void shuffle() = 0;
};

class Hand {
public:
  	virtual int getScore() const  = 0;
};

class BlackjackCard : public Card 
{
public:
	virtual int getValue() const {

	}
};
class BlackjackDeck : public Deck
{
public:
	virtual void deal() = 0;
	virtual void shuffle() = 0;
};

class BlackJackHand {

public:

	virtual int getScore() const {
		// Scores below the 'bust' boundary
		int maxScoreLt = INT_MIN;
		int minScoreGt = INT_MAX;
		for (const auto& score : possibleScores())
		{
			if (score > maxScoreLt && score < 21)
				maxScoreLt = score;
			else if (score < minScoreGt && score > 21)
				minScoreGt = score;
		}
		if (maxScoreLt != INT_MIN) return maxScoreLt;
		else
			return minScoreGt;
	}

	vector<int> possibleScores() const{
		// TODO: Calculate possibilities for all scores, considering aces
		return vector<int>();
	}
	vector<Card*> cards;

};

int main()
{

}