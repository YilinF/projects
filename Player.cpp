/* Player.h
 *
 * Euchre player interface
 * Project UID 1d9f47bfc76643019cfbf037641defe1
 *
 * by Andrew DeOrio
 * awdeorio@umich.edu
 * 2014-12-21
 */


#include "Card.h"
#include "Player.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

class Human : public Player {
public:
    Human(const string &name): name(name){}

    const string & get_name() const override {
        return name;
    }
    
    void add_card(const Card &c) override {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
        sort(hand.begin(), hand.end());
        return;
    }
    
    void print_cards(const vector<Card> &c, std::string name) const{
        for (size_t i = 0; i < c.size(); i++) {
            cout << "Human player " << name << " 's hand: [" << i << "]"
            << c[i] << endl;
        }
    }
    
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, string &order_up_suit) const override {
        assert(round == 1 || round == 2);
        string choice = "";
        bool ordered_up;
        
        print_cards(hand, name);
        cout << "Human player " << name << ", please enter a suit, "
            << "or \"pass\":";
        cin >> choice;
        
        if (is_dealer && round == 2 && choice == "pass") {
            while (choice == "pass") {
                cout << "Human player " << name << ", please enter a suit, "
                    << "or \"pass\":";
                cin >> choice;
            }
        }
        
        if (choice == "Diamonds") {
            order_up_suit = Card::SUIT_DIAMONDS;
            ordered_up = true;
        }
        else if (choice == "Clubs") {
            order_up_suit = Card::SUIT_CLUBS;
            ordered_up = true;
        }
        else if (choice == "Hearts") {
            order_up_suit = Card::SUIT_HEARTS;
            ordered_up = true;
        }
        else if (choice == "Spades") {
            order_up_suit = Card::SUIT_SPADES;
            ordered_up = true;
        }
        else if (choice == "pass") {
            ordered_up = false;
        }
        else {
            ordered_up = false;
        }
        return ordered_up;
    }
    
    void add_and_discard(const Card &upcard) override {
        assert(hand.size() >= 1);
        int index;
        print_cards(hand, name);
        
        cout << "Discard upcard: [-1]" << endl;
        cout << "Human player " << name
        << ", please select a card to discard:" << endl << endl;
        cin >> index;
        
        hand.erase(hand.begin() + index);
        hand.push_back(upcard);
        sort(hand.begin(), hand.end());
        return;
    }
    
    Card lead_card(const string &trump) override {
        assert(hand.size() >= 1);
        int index = 0;
        Card card_led;
        
        print_cards(hand, name);
        
        cout << "Human player " << name << ", please select a card:" << endl;
        cin >> index;
        
        for (size_t i = 0; i < hand.size(); i++) {
            card_led = hand[index];
            hand.erase(hand.begin() + i);
        }
        return card_led;
    }
    
    Card play_card(const Card &led_card, const string &trump) override {
        assert(hand.size() >= 1);
        int index = 0;
        Card card_played;
        
        print_cards(hand, name);
        
        cout << "Human player " << name << ", please select a card:" << endl;
        cin >> index;
        
        for (size_t i = 0; i < hand.size(); i++) {
            card_played = hand[index];
            hand.erase(hand.begin() + i);
        }
        return card_played;
    }

private:
    string name;
    vector<Card> hand;
};

class SimplePlayer : public Player {
public:
    SimplePlayer(const string &name): name(name){}

    const string & get_name() const override {
        return name;
    }
    
    void add_card(const Card &c) override {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
        sort(hand.begin(), hand.end());
        return;
    }
    
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, string &order_up_suit) const override {
        assert(round == 1 || round == 2);
        int num_trump_face_cards = 0;
        string trump;
        
        if (round == 1) {
            trump = upcard.get_suit();
            for (int i = 0; i < hand.size(); i++) {
                if (hand.at(i).is_face()
                    && hand.at(i).get_suit() == trump) {
                    num_trump_face_cards++;
                }
            }
            if (num_trump_face_cards >= 2) {
                order_up_suit = trump;
                return true;
            } else {
                return false;
            }
        } else {
            trump = Suit_next(upcard.get_suit());
            num_trump_face_cards = 0;
            for (int i = 0; i < hand.size(); i++) {
                if (hand.at(i).is_face() && hand.at(i).is_trump(trump)) {
                    num_trump_face_cards++;
                }
            }
            if (is_dealer) {
                order_up_suit = trump;
                return true;
            }
            if (num_trump_face_cards >= 1) {
                order_up_suit = trump;
                return true;
            } else {
                return false;
            }
        }
        return false;
    }
    
    size_t find_in_hand(const Card &c) {
        size_t index = 0;
        for (size_t i = 0; i < hand.size(); i++) {
            if (c.get_suit() == hand.at(i).get_suit()
                && c.get_rank() == hand.at(i).get_suit()) {
                hand.at(i) = c;
                index = i;
            }
        }
        return index;
    }
    
    size_t find_right_bower(vector<Card> &c, const string &trump) {
        for (size_t i = 0; i < c.size(); i++) {
            if (hand.at(i).Card::is_right_bower(trump)) {
                return i;
            }
        }
        return -1;
    }
    
    size_t find_left_bower(vector<Card> &c, const string &trump) {
        for (size_t i = 0; i < c.size(); i++) {
            if (hand.at(i).Card::is_left_bower(trump)) {
                return i;
            }
        }
        return -1;
    }
        
    bool found_left_bower(vector<Card> &c, const string &trump) {
        return (find_left_bower(c, trump) != -1);
    }
        
    size_t min_in_hand(vector<Card> vec, const string &trump) {
        sort(vec.begin(), vec.end());
        // return lowest index if no trump
        for (size_t i = 0; i < vec.size(); i++) {
            if(!vec.at(i).is_trump(trump)) {
                return i;
            }
        }
        //return lowest index if all trump
        for(size_t i = 0; i < vec.size(); i++) {
            if(!vec.at(i).is_left_bower(trump) &&
                 !vec.at(i).is_right_bower(trump)) {
            return i;
            }
        }
       // return lowest bower
        assert(vec.size() <= 2);
        if (vec.at(1).is_left_bower(trump)) {
            return 1;
        }
        return 0;
    }
    
    void add_and_discard(const Card &upcard) override {
        assert(hand.size() >= 1);
        string trump_suit = upcard.get_suit();
        hand.erase(hand.begin() + min_in_hand(hand, trump_suit));
        hand.push_back(upcard);
        sort(hand.begin(), hand.end());
        return;
    }
    
    size_t find_highest_trump(vector<Card> &vec, const string &trump) {
        size_t index = 0;
        sort(vec.begin(), vec.end());
        
        if (find_right_bower(vec, trump) != -1) {
            index = find_right_bower(vec, trump);
        }
        else if (find_left_bower(vec, trump) != -1) {
            index = find_left_bower(vec, trump);
        }
        else {
            index = vec.size() - 1;
        }
        return index;
    }
    
    Card lead_card(const string &trump) override {
        Card card_led;
        int trump_count = 0;
        vector<Card> not_trump_sorted;
        
        for (size_t i = 0; i < hand.size(); i++) {
            if (hand.at(i).is_trump(trump)) {
                trump_count++;
            }
            else {
                not_trump_sorted.push_back(hand.at(i));
            }
        }
        
        sort(hand.begin(), hand.end());
        if (trump_count == hand.size()) {
            card_led = hand.at(find_highest_trump(hand, trump));
        }
        else {
            assert(not_trump_sorted.size() >= 1);
            sort(not_trump_sorted.begin(), not_trump_sorted.end());
            card_led = not_trump_sorted.at(not_trump_sorted.size() - 1);
        }
        hand.erase(hand.begin() + find_in_hand(card_led));
        return card_led;
    }
    
    Card play_card(const Card &led_card, const string &trump) override {
        Card card_played;
        int led_count = 0;
        int trump_count = 0;
        vector<Card> led_sorted;
        
        for (size_t i = 0; i < hand.size(); i++) {
            if (hand.at(i).get_suit(trump) == led_card.get_suit(trump)) {
                led_count++;
                led_sorted.push_back(hand.at(i));
            }
            if (hand.at(i).get_suit(trump) == trump) {
                trump_count++;
            }
        }
        
        sort(hand.begin(), hand.end());
        if (led_card.get_suit(trump) == trump ||
             found_left_bower(hand, trump)) {
            if (trump_count == 0) {
                card_played = hand.at(0);
            }
            else {
                card_played = hand.at(find_highest_trump(hand, trump));
            }
        }
        else {
            if (led_count == 0) {
                card_played = hand.at(min_in_hand(hand,trump));
            }
            else {
                assert(led_sorted.size() >= 1);
                sort(led_sorted.begin(), led_sorted.end());
                card_played = led_sorted.at(led_sorted.size() - 1);
            }
        }
        hand.erase(hand.begin() + find_in_hand(card_played));
        return card_played;
    }
    
private:
    string name;
    vector<Card> hand;
};

Player * Player_factory(const std::string &name, const std::string &strategy) {
    if (strategy == "Simple") {
        return new SimplePlayer(name);
    }
    else if (strategy == "Human") {
        return new Human(name);
    }
    return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
    return os << p.get_name();
}
