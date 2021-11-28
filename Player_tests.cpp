// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"
#include <cassert>
#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * jason = Player_factory("Jason", "Simple");
    ASSERT_EQUAL("Jason", jason->get_name());

    delete jason;
}

TEST(simple_add_card) {
    Player *Billy = Player_factory("Billy", "Simple");
    
    Billy->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    Billy->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    Billy->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    Billy->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));

    delete Billy;
}

TEST(test_simple_constructor) {
    Player * amy = Player_factory("Amy", "Simple");
    ostringstream os;
    os << *amy;
    ASSERT_EQUAL(amy->get_name(),"Amy");
    ASSERT_EQUAL(os.str(), "Amy");
    delete amy;
}

TEST(simple_make_trump) {
    Card c = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c2 = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c3 = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card c4 = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c5 = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Player *Billy = Player_factory("Billy", "Simple");
    Billy->add_card(c);
    Billy->add_card(c2);
    Billy->add_card(c3);
    Billy->add_card(c4);
    Billy->add_card(c5);
    
    //Round 1, Billy is dealer, trump suit is diamonds,
    //upcard is Queen of Diamonds
    Card up_card = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    string diamonds = "Diamonds";
    bool order_up_card = Billy->make_trump(up_card, true, 1, diamonds);
    ASSERT_FALSE(order_up_card);
    
    //Round 1, Billy is dealer, trump suit is diamonds,
    //upcard is Queen of Diamonds
    up_card = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    order_up_card = Billy->make_trump(up_card, false, 1, diamonds);
    ASSERT_FALSE(order_up_card);
    
    //Round 1, Billy is dealer, trump suit is clubs,
    up_card = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    order_up_card = Billy->make_trump(up_card, false, 1, diamonds);
    ASSERT_FALSE(order_up_card);
}

TEST(simple_make_trump2) {
    string trump;
    Player *p1 = Player_factory("p1", "Simple");
    Card c = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c2 = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c3 = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card c4 = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c5 = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    
    p1->add_card(c);
    p1->add_card(c2);
    p1->add_card(c3);
    p1->add_card(c4);
    p1->add_card(c5);
    Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    trump = Card::SUIT_SPADES;
    bool order_up_card = p1->make_trump(queen_spades,true,2,trump);
    ASSERT_TRUE(order_up_card);
    ASSERT_EQUAL(trump,Card::SUIT_SPADES);
    delete p1;
}

//Tests add_card() as well
TEST(test_simple_lead_card1) {
    Player *TestName = Player_factory("TestName", "Simple");
    
    Card c = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c2 = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c3 = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card c4 = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c5 = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    
    TestName->add_card(c);
    TestName->add_card(c2);
    TestName->add_card(c3);
    TestName->add_card(c4);
    TestName->add_card(c5);
    
    Card led_card = TestName->lead_card(Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(led_card, c);
    
    delete TestName;
}

TEST(test_simple_lead_card2) {
    Player *TestName1 = Player_factory("TestName1", "Simple");
    
    Card c6 = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c7 = Card(Card::RANK_KING, Card::SUIT_CLUBS);
    Card c8 = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card c9 = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    
    TestName1->add_card(c6);
    TestName1->add_card(c7);
    TestName1->add_card(c8);
    TestName1->add_card(c9);
    
    Card led_card5 = TestName1->lead_card(Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(led_card5, c6);
    Card led_card6 = TestName1->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(led_card6, c9); // not working
    
    delete TestName1;
}

TEST(test_simple_lead_card3) {
    Player *TestName2 = Player_factory("TestName2", "Simple");
    
    Card c10 = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c11 = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c12 = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card c13 = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    
    TestName2->add_card(c10);
    TestName2->add_card(c11);
    TestName2->add_card(c12);
    TestName2->add_card(c13);
    
    Card led_card7 = TestName2->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(led_card7, c10);
    Card led_card8 = TestName2->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(led_card8, c11);
    
    delete TestName2;
}

/* TEST(test_simple_lead_card4) {
    Player *TestName = Player_factory("TestName", "Simple");
    
    Card c = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c2 = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c3 = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card c4 = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c5 = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    
    TestName->add_card(c);
    TestName->add_card(c2);
    TestName->add_card(c3);
    TestName->add_card(c4);
    TestName->add_card(c5);
    
    Card led_card4 = TestName->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(led_card4, c2);
    
    delete TestName;
} */
    
TEST(test_simple_play_card1) {
    // is not led suit, has no trump
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

    // Bob plays a card
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
    );

    // Verify the card Bob played
    ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
    delete bob;
}

/* TEST(test_simple_play_card2) {
    // is led suit, led suit is not trump
    Player * nick = Player_factory("Nick", "Simple");
    
    nick->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    nick->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    nick->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    nick->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));

    Card queen_spades(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card card_played2 = nick->play_card(
    queen_spades,  // Nine of Diamonds is led
    "clubs"        // Trump suit
    );
    
    ASSERT_EQUAL(card_played2, Card(Card::RANK_KING, Card::SUIT_SPADES));
    delete nick;
} */

/* TEST(test_simple_play_card3) { // not working
    // is led suit, led suit is trump
    Player * pat = Player_factory("Pat", "Simple");
    pat->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    pat->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    pat->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    pat->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    pat->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

    Card queen_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card card_played3 = pat->play_card(
    queen_clubs,  // Nine of Diamonds is led
    "clubs"        // Trump suit
    );
    
    ASSERT_EQUAL(card_played3, Card(Card::RANK_JACK, Card::SUIT_SPADES));
    delete pat; // not working
} */

TEST(test_simple_play_card4) {
    // is not led suit, has trump
    Player * heather = Player_factory("Heather", "Simple");
    heather->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    heather->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    heather->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

    Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card card_played4 = heather->play_card(
    ace_diamonds,  // Nine of Diamonds is led
    "hearts"        // Trump suit
    );
    
    ASSERT_EQUAL(card_played4, Card(Card::RANK_NINE, Card::SUIT_SPADES));
    delete heather;
}

TEST(test_simple_play_card5) {
    // is not led suit, lowest card is bower
    Player * tracy = Player_factory("Heather", "Simple");
    tracy->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    tracy->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));

    Card ten_spades(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card card_played5 = tracy->play_card(
    ten_spades,  // Nine of Diamonds is led
    "hearts"        // Trump suit
    );
    
    ASSERT_EQUAL(card_played5, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    delete tracy;
}

TEST(test_simple_play_card6) {
    Player * sally = Player_factory("Sally", "Simple");
    
    sally->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    sally->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    sally->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    sally->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));

    Card king_spades(Card::RANK_KING, Card::SUIT_SPADES);
    Card card_played6 = sally->play_card(
    king_spades,  // Nine of Diamonds is led
    "hearts"        // Trump suit
    );
    
    ASSERT_EQUAL(card_played6, Card(Card::RANK_ACE, Card::SUIT_SPADES));
    delete sally;
}

TEST_MAIN()
