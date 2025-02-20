#include <cmath>
#include <cstdio>
#include <type_traits>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


/*

Design (and implement) data structures representing a deck of playing cards.

“Deck of Playing Cards” Requirements:
* A card has a value and suit
* There are 4 different suits which consists of: diamonds, clubs, hearts, and spades
* The value of each card is between 1-13
* The value 1 represents an A (Ace)
* Values from 11 to 13 correspond to J (Jack), Q (Queen), and K (King) respectively
* A deck initially consists of 52 unique cards in total
* A card can be dealt from the deck (i.e. take the top card off the deck - removes from deck)
* A deck can be shuffled (i.e. randomize the order of the remaining cards in deck)


Add 2 Jokers into the code below.


 */
 // I think we'll need primitives here: 
 // Suit (Diamond, Heart, Club , Spade ), Rank/ Value 1-13
 
 enum Suit  {
        DIAMOND = 0, 
        HEART,
        CLUB,
        SPADE,
        INVALID_SUIT,
        
 };
 
 enum Rank {
    ACE = 0,
    TWO,
    THREE,
    FOUR, 
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN, 
    KING,
    INVALID_RANK,
 };
 
 struct Card 
 {
    Card()
    :Card(INVALID_SUIT, INVALID_RANK) {
        
    }
    Card(Suit iSuit, Rank iRank)
    :suit(iSuit), rank(iRank){
        
    }
    
    Card(int joker_index)
    :joker_val(joker_index) {
        
    }
  
    bool isJoker() {
        return joker_val >= 1;
    }
    
    int getJokerVal(){
        return joker_val;
    }
    
    Suit getSuit() {
        return suit;
    }
    
    Rank getRank() {
        return rank;
    }
    bool isValid() {
        return suit != INVALID_SUIT && rank != INVALID_RANK;
    }
    
    
    private:
    Suit suit;
    Rank rank;
    int joker_val;
 };
 
 struct Deck {
    
    Deck() {
        initialize();
    }
    void initialize() {
         // initialize Deck of cards 
        for (int i = 0; i < 13; i++ ){
            // TODO: See if we can avoid magic number
            for (int j =0 ;j < 4; j++) {
                cards.push_back({ (Suit)j,  (Rank)i});
            }
        }
        cards.push_back( {1});
        cards.push_back( {2});
    }
    
    void shuffle() {
        srand(time(NULL));
           for (int i = 0 ; i < cards.size() ;i ++ ) {
             //  0-> size_ -1
            auto shuffled_index = rand () % cards.size() ; 
            swap(cards[shuffled_index], cards[i]);
        }
    }
    
    bool hasMore() {
        return !cards.empty();
    }
    int getSize() {
        return cards.size();
    }
    Card  deal() {
         // Top of the deck is the one at the end
        auto top  = cards.back();
        cards.pop_back();
        return top;  
    }
    
    /*
      pair<Card, bool>  deal() {
      if (!hasMore() ){
      return make_pair(Card(-1,-1), false);
      }
         // Top of the deck is the one at the end
        auto top  = cards.back();
        cards.pop_back();
        return make_pair(top, true);  
    } 
    
        /*
      Card  deal() {
      if (!hasMore() ){
      return make_pair(Card(-1,-1), false);
      }
         // Top of the deck is the one at the end
        auto top  = cards.back();
        cards.pop_back();
        return make_pair(top, true);  
    } 
    */
    void debugPrint() {
        for (int i = 0 ; i < cards.size(); i++) {
            if (cards[i].isJoker()) {
                cout <<  " Joker val " << cards[i].getJokerVal() << endl;
            } else {
            cout  <<  " Rank " << (int) cards[i].getRank() << " Suit " << (int) cards[i].getSuit()<<  endl;
            }
        }
    }
    
    private:
        vector<Card> cards;
    
 };
 
int main() {
    cout << "Initialized " << endl;
    Deck d;
    // d.debugPrint();
    d.shuffle();
    cout << "After shuffle once " << endl;
    d.debugPrint();
    
    while (d.hasMore()) {
         auto card_deck_size = d.getSize(); 
         auto top_deck = d.deal();
         cout << " Size " << card_deck_size <<  ", Dealed " << " Rrank: " <<  top_deck.getRank() << " Suit: " << top_deck.getSuit() << endl;
    }
}

