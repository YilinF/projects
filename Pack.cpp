/* Pack.h
 *
 * Represents a pack of playing cards
 * Project UID 1d9f47bfc76643019cfbf037641defe1
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2014-12-21
 */


#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <array>
#include "Pack.h"
#include "Card.h"

using namespace std;

Pack::Pack() {
    cards[0] = {Card::RANK_NINE, Card::SUIT_SPADES};
    cards[1] = {Card::RANK_TEN, Card::SUIT_SPADES};
    cards[2] = {Card::RANK_JACK, Card::SUIT_SPADES};
    cards[3] = {Card::RANK_QUEEN, Card::SUIT_SPADES};
    cards[4] = {Card::RANK_KING, Card::SUIT_SPADES};
    cards[5] = {Card::RANK_ACE, Card::SUIT_SPADES};
    cards[6] = {Card::RANK_NINE, Card::SUIT_HEARTS};
    cards[7] = {Card::RANK_TEN, Card::SUIT_HEARTS};
    cards[8] = {Card::RANK_JACK, Card::SUIT_HEARTS};
    cards[9] = {Card::RANK_QUEEN, Card::SUIT_HEARTS};
    cards[10] = {Card::RANK_KING, Card::SUIT_HEARTS};
    cards[11] = {Card::RANK_ACE, Card::SUIT_HEARTS};
    cards[12] = {Card::RANK_NINE, Card::SUIT_CLUBS};
    cards[13] = {Card::RANK_TEN, Card::SUIT_CLUBS};
    cards[14] = {Card::RANK_JACK, Card::SUIT_CLUBS};
    cards[15] = {Card::RANK_QUEEN, Card::SUIT_CLUBS};
    cards[16] = {Card::RANK_KING, Card::SUIT_CLUBS};
    cards[17] = {Card::RANK_ACE, Card::SUIT_CLUBS};
    cards[18] = {Card::RANK_NINE, Card::SUIT_DIAMONDS};
    cards[19] = {Card::RANK_TEN, Card::SUIT_DIAMONDS};
    cards[20] = {Card::RANK_JACK, Card::SUIT_DIAMONDS};
    cards[21] = {Card::RANK_QUEEN, Card::SUIT_DIAMONDS};
    cards[22] = {Card::RANK_KING, Card::SUIT_DIAMONDS};
    cards[23] = {Card::RANK_ACE, Card::SUIT_DIAMONDS};
    next = 0;
}

Pack::Pack(istream& pack_input) {
    string rank;
    string temp;
    string suit;
    
    for (int i = 0; i < PACK_SIZE; i++) {
        pack_input >> rank >> temp >> suit;
        cards[i] = Card(rank, suit);
    }
    next = 0;
}

Card Pack::deal_one() {
    next++;
    return cards[next - 1];
}

void Pack::reset() {
    next = 0;
    return;
}

void Pack::shuffle() {
    Card first_half[12];
    Card second_half[12];
        
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            first_half[j] = cards[j];
            second_half[j] = cards[j + 12];
        }
        for (int j = 0; j < 24; j++) {
            if (j % 2 == 0) {
                cards[j] = second_half[j / 2];
            }
            else {
                cards[j] = first_half[(j - 1) / 2];
            }
        }
    }
    return;
}

bool Pack::empty() const {
    return (next == 24);
}
