// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
using namespace std;

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

Card::Card() : rank(RANK_TWO), suit(SUIT_SPADES){
}

Card::Card(const std::string &rank_in, const std::string &suit_in)
: rank(rank_in), suit(suit_in){
}

string Card::get_rank() const {
    return rank;
}

string Card::get_suit() const {
    return suit;
}

string Card::get_suit(const std::string &trump) const {
    if (is_left_bower(trump)) {
        return trump;
    }
    else {
        return suit;
    }
}

bool Card::is_face() const {
    return (rank == RANK_JACK || rank == RANK_QUEEN || rank == RANK_KING
            || rank == RANK_ACE);
}

bool Card::is_right_bower(const string &trump) const {
    return (rank == RANK_JACK && suit == trump);
}

bool Card::is_left_bower(const std::string &trump) const {
    if (rank == RANK_JACK) {
        if (trump == SUIT_SPADES) {
            return (suit == SUIT_CLUBS);
        }
        else if (trump == SUIT_CLUBS) {
            return (suit == SUIT_SPADES);
        }
        else if (trump == SUIT_HEARTS) {
            return (suit == SUIT_DIAMONDS);
        }
        else if (trump == SUIT_DIAMONDS) {
            return (suit == SUIT_HEARTS);
        }
    }
    return false;
}

bool Card::is_trump(const std::string &trump) const {
    return (suit == trump || is_left_bower(trump));
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

static int find_rank(const Card &c) {
    int r = 0;
    if (c.get_rank() == Card::RANK_NINE) {
        r = 9;
    }
    else if (c.get_rank() == Card::RANK_TEN) {
        r = 10;
    }
    else if (c.get_rank() == Card::RANK_JACK) {
        r = 11;
    }
    else if (c.get_rank() == Card::RANK_QUEEN) {
        r = 12;
    }
    else if (c.get_rank() == Card::RANK_KING) {
        r = 13;
    }
    else if (c.get_rank() == Card::RANK_ACE) {
        r = 14;
    }
    return r;
}

static int find_suit(const Card &c) {
    int s = 0;
    if (c.get_suit() == Card::SUIT_SPADES) {
        s = 1;
    }
    else if (c.get_suit() == Card::SUIT_HEARTS) {
        s = 2;
    }
    else if (c.get_suit() == Card::SUIT_CLUBS) {
        s = 3;
    }
    else if (c.get_suit() == Card::SUIT_DIAMONDS) {
        s = 4;
    }
    return s;
}

bool operator<(const Card &lhs, const Card &rhs) {
    return (find_rank(lhs) < find_rank(rhs) ||
    (find_rank(lhs) == find_rank(rhs) && find_suit(lhs) < find_suit(rhs)));
}

bool operator<=(const Card &lhs, const Card &rhs) {
    return (find_rank(lhs) < find_rank(rhs) ||
    (find_rank(lhs) == find_rank(rhs) && find_suit(lhs) <= find_suit(rhs)));
}

bool operator>(const Card &lhs, const Card &rhs) {
    return (find_rank(lhs) > find_rank(rhs) ||
    (find_rank(lhs) == find_rank(rhs) && find_suit(lhs) > find_suit(rhs)));
}

bool operator>=(const Card &lhs, const Card &rhs) {
    return (find_rank(lhs) > find_rank(rhs) ||
    (find_rank(lhs) == find_rank(rhs) && find_suit(lhs) >= find_suit(rhs)));
}

bool operator==(const Card &lhs, const Card &rhs) {
    return (lhs.get_rank() == rhs.get_rank()) &&
    (lhs.get_suit() == rhs.get_suit());
}

bool operator!=(const Card &lhs, const Card &rhs) {
    return (lhs.get_rank() != rhs.get_rank()) ||
    (lhs.get_suit() != rhs.get_suit());
}

string Suit_next(const string& suit) {
    if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    }
    else if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    else if (suit == Card::SUIT_HEARTS) {
        return Card::SUIT_DIAMONDS;
    }
    else {
        return Card::SUIT_HEARTS;
    }
}

ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

bool Card_less(const Card &a, const Card &b, const std::string &trump) {
    return (b.Card::is_right_bower(trump)) ||
    ((b.Card::is_left_bower(trump)) && (!a.Card::is_right_bower(trump)) &&
        (!a.Card::is_left_bower(trump))) ||
    ((a.Card::is_trump(trump)) && (b.Card::is_trump(trump)) && (a < b)) ||
    (!(a.Card::is_trump(trump)) && (b.Card::is_trump(trump))) ||
    (!(a.Card::is_trump(trump)) && !(b.Card::is_trump(trump)) && (a < b));
}

bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    return (b.Card::is_right_bower(trump)) ||
    ((b.Card::is_left_bower(trump)) && (!a.Card::is_right_bower(trump)) &&
        (!a.Card::is_left_bower(trump))) ||
    ((a.Card::is_trump(trump)) && (b.Card::is_trump(trump)) && (a < b)) ||
    ((a.Card::is_trump(led_card.Card::get_suit())) &&
        (b.Card::is_trump(trump))) ||
    ((a.Card::is_trump(led_card.Card::get_suit())) &&
        (b.Card::is_trump(led_card.Card::get_suit())) && (a < b)) ||
    (!a.Card::is_trump(trump) && !b.Card::is_trump(trump) &&
     !a.Card::is_trump(led_card.Card::get_suit()) &&
     !b.Card::is_trump(led_card.Card::get_suit()) && (a < b));
}

