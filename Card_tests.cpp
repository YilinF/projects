// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}
TEST(test_card_istream_ctor) {
    string rank_in = "Ace";
    string suit_in = "Hearts";
    
    Card c(rank_in, suit_in);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}
TEST(test_get_rank) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    Card c2(Card::RANK_TWO, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_TWO, c2.get_rank());
    Card c3(Card::RANK_THREE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_THREE, c3.get_rank());
    Card c4(Card::RANK_FOUR, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_FOUR, c4.get_rank());
}
TEST(test_get_suit) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
    Card c2(Card::RANK_TWO, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card::SUIT_CLUBS, c2.get_suit());
    Card c3(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card::SUIT_SPADES, c3.get_suit());
    Card c4(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c4.get_suit());
}
TEST(test_get_suit_trump) {
    //returns trump suit when encountering a left bower
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_HEARTS), Card::SUIT_HEARTS);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(c2.get_suit(Card::SUIT_SPADES), Card::SUIT_SPADES);
    Card c3(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_EQUAL(c3.get_suit(Card::SUIT_SPADES), Card::SUIT_SPADES);
    Card c4(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(c4.get_suit(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_FIVE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c5.get_suit(Card::SUIT_SPADES), Card::SUIT_HEARTS);
    Card c6(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c6.get_suit(Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS);
    Card c7(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(c7.get_suit(Card::SUIT_HEARTS), Card::SUIT_HEARTS);
    Card c8(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(c8.get_suit(Card::SUIT_CLUBS), Card::SUIT_CLUBS);
}
TEST(test_is_face) {
    //Tests face cards against is_face()
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(c.is_face());
    Card c2(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(c2.is_face());
    Card c3(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_TRUE(c3.is_face());
    Card c4(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c4.is_face());
    //Tests non-face card against is_face()
    Card c5(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_FALSE(c5.is_face());
}
TEST(test_is_right_bower) {
    //Tests non-jack card to non-trump suit
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_DIAMONDS));
    //Tests non-jack card to trump suit
    Card c2(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_FALSE(c2.is_right_bower(Card::SUIT_HEARTS));
    //Tests jack card to non-trump suit
    Card c3(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c3.is_right_bower(Card::SUIT_CLUBS));
    //Tests jack card to trump suit -- right bower!
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(c4.is_right_bower(Card::SUIT_CLUBS));
}
TEST(test_is_left_bower) {
    //Tests jack card to opposite suit -- left bower!
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(c.is_left_bower(Card::SUIT_CLUBS));
    //Tests non-jack card to opposite suit
    Card c2(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c2.is_left_bower(Card::SUIT_SPADES));
    //Tests non-jack card to non-opposite suit
    Card c3(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(c3.is_left_bower(Card::SUIT_DIAMONDS));
    //Tests jack card to non-opposite suit
    Card c4(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(c4.is_left_bower(Card::SUIT_CLUBS));
    Card c5(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(c4.is_left_bower(Card::SUIT_HEARTS));
}
TEST(test_is_trump) {
    //Tests non-trump suit to is_trump(trump suit)
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_trump(Card::SUIT_HEARTS));
    //Tests trump suit to is_trump(trump suit) -- is trump!
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(c2.is_trump(Card::SUIT_HEARTS));
}
TEST(test_card_less_trump_only) {
    //b is the RB
    Card a(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card b(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(a, b, Card::SUIT_SPADES));
    //b2 is the LB, a isn't RB and isn't LB
    Card a2(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card b2(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(a2, b2, Card::SUIT_SPADES));
    //a3 is trump, b3 is trump, a3 rank is less than b3 rank
    Card a3(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card b3(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(a3, b3, Card::SUIT_HEARTS));
    //a4 is not trump, b4 is trump
    Card a4(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card b4(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(a4, b4, Card::SUIT_DIAMONDS));
    //a3 is not trump, b3 is not trump, a3 rank is less than b3 rank
    Card a5(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card b5(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(a5, b5, Card::SUIT_DIAMONDS));
}
TEST(test_card_less_ledcard) {
    //a is not trump, b is not trump, a is not led card, b is not led card,
    //a rank is less than b rank
    Card a(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card b(Card::RANK_TEN, Card::SUIT_SPADES);
    Card led_card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(a, b, led_card, Card::SUIT_CLUBS));
}
TEST(test_self_comparison) {
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_FALSE(ten_clubs < ten_clubs);
    ASSERT_TRUE(ten_clubs <= ten_clubs);
    ASSERT_FALSE(ten_clubs > ten_clubs);
    ASSERT_TRUE(ten_clubs >= ten_clubs);
    ASSERT_TRUE(ten_clubs == ten_clubs);
    ASSERT_FALSE(ten_clubs != ten_clubs);
}
TEST(test_operator) {
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card seven_clubs = Card(Card::RANK_SEVEN, Card::SUIT_CLUBS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    
    ASSERT_TRUE(jack_diamonds != ace_spades);
    ASSERT_FALSE(seven_clubs == jack_hearts);
    ASSERT_FALSE(jack_hearts >= jack_diamonds);
    ASSERT_TRUE(jack_hearts < jack_diamonds);
    ASSERT_FALSE(seven_clubs > ace_spades);
    ASSERT_TRUE(jack_diamonds <= ace_spades);
}


// Add more test cases here

TEST_MAIN()

