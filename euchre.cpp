//Project UID 1d9f47bfc76643019cfbf037641defe1
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
#include "Player.h"

using namespace std;
//./euchre.exe pack.in shuffle 10 Edsger Simple Fran Simple Gabriel
//Simple Herb Simple

class Game {
public:
    Game(vector<Player*> players, ifstream &pack_in) :
    pack(pack_in), all_players(players), player_order(players),
    up_card_player(players[0]), dealer(0), leader(0), hand(0), trick0(0),
    trick1(0), trick2(0), trick3(0), team_1(0), team_2(0), trump("temp"),
    gameover(0) {
    }
    /*
     Pack pack;
     vector<Player*> all_players;
     vector<Player*> player_order;
     Player *up_card_player;
     int dealer = 0;
     int leader = 0;
     int hand = 0;
     int trick0 = 0;
     int trick1 = 0;
     int trick2 = 0;
     int trick3 = 0;
     int team_1 = 0;
     int team_2 = 0;
     string trump = "";
     bool gameover = false;
     */

    void deal_cards() {
        //Dealer will change every hand
        if (dealer == 0) {
            player_order = {all_players[1], all_players[2], all_players[3],
                all_players[0]};
        } else if (dealer == 1) {
            player_order = {all_players[2], all_players[3], all_players[0],
                all_players[1]};
        } else if (dealer == 2) {
            player_order = {all_players[3], all_players[0], all_players[1],
                all_players[2]};
        } else {
            player_order = {all_players[0], all_players[1], all_players[2],
                all_players[3]};
        }
        Card c;
        //3,2,3,2 first deal
        for (int i = 0; i < 4; i++) {
            if (i == 0 || i == 2) {
                for (int j = 0; j < 3; j++) {
                    player_order[i]->add_card(pack.deal_one());
                }
            } else {
                for (int j = 0; j < 2; j++) {
                    player_order[i]->add_card(pack.deal_one());
                }
            }
        }
        //2,3,2,3 second deal
        for (int i = 0; i < 4; i++) {
            if (i == 0 || i == 2) {
                for (int j = 0; j < 2; j++) {
                    player_order[i]->add_card(pack.deal_one());
                }
            } else {
                for (int j = 0; j < 3; j++) {
                    player_order[i]->add_card(pack.deal_one());
                }
            }
        }
    }
    Card new_hand(string shuffle) {
        if (shuffle == "noshuffle") {
            pack.reset();
        } else if (shuffle == "shuffle") {
            pack.shuffle();
        }
        deal_cards();
        Card up_card = pack.deal_one();
        cout << "Hand " << hand << endl;
        cout << *all_players[dealer] << " deals" << endl;
        cout << up_card << " turns up" << endl;
        dealer++;
        hand++;
        return up_card;
    }
    /*
     2. Making Trump
    */
    int choose_trump_round_one(Card up_card) {
        bool dealer = false;
        string trumpsuit = up_card.get_suit();
        for (int i = 0; i < 4; i++) {
            if (i == 3) {
                dealer = true;
            }
            if (player_order[i]->make_trump(up_card, dealer, 1, trumpsuit)) {
                cout << *player_order[i] << " orders up " << trumpsuit << endl
                << endl;
                player_order[3]->add_and_discard(up_card);
                trump = trumpsuit;
                return i;
            } else {
                cout << *player_order[i] << " passes" << endl;
            }
        }
        return 555;
    }
    int choose_trump_round_two(Card up_card) {
        bool dealer = false;
        string trumpsuit = up_card.get_suit();
        for (int i = 0; i < 4; i++) {
            if (i == 3) {
                dealer = true;
            }
            if (player_order[i]->make_trump(up_card, dealer, 2, trumpsuit)) {
                cout << *player_order[i] << " orders up " << trumpsuit <<
                endl << endl;
                
                return i;
            } else {
                cout << *player_order[i] << " passes" << endl;
            }
        }
        return 555;
    }
    
    Player *who_chose_trump(Card up_card) {
        int round1 = 0;
        int i = 0;
        round1 = choose_trump_round_one(up_card);
        if (round1 == 555) {
            i = choose_trump_round_two(up_card);
            up_card_player = player_order[i];
            return player_order[i];
        }
        up_card_player = player_order[round1];
        return player_order[round1];
    }
    /*
     Trick Taking
     */
    int trick(int trick_leader) {
        vector<int> order;
        if (trick_leader == 0) {
                order = {0,1,2,3};
                leader = 0;
            }
            else if (trick_leader == 1) {
                order = {1,2,3,0};
                leader = 1;
            }
            else if (trick_leader == 2) {
                order = {2,3,0,1};
                leader = 2;
            }
            else {
                order = {3,0,1,2};
                leader = 3;
            }
        Card led_card;
        Card c;
        int winner = 0;
        Card current_winning_card;
        for (int i = 0; i < 3; i++) {
            if (i != 0) {
                c = all_players[order[i]]->play_card(led_card, trump);
                cout << c << " played by " << *all_players[order[i]] <<
                " " << endl;
                if (Card_less(current_winning_card, c, led_card, trump)) {
                    winner = order[i];
                    current_winning_card = c;
                }
            } else {
                //leader
                    led_card = all_players[order[0]]->lead_card(trump);
                    cout << led_card << " led by " << *all_players[order[i]] <<
                    " " << endl;
                    winner = order[i];
                    current_winning_card = led_card;
                }
            }
        //winner of trick
        cout << *all_players[winner] << " takes the trick" << endl << endl;
        if (all_players[winner] == all_players[0]) {
            trick0++;
            team_1++;
        } else if (all_players[winner] == all_players[1]) {
            trick1++;
            team_2++;
        } else if (all_players[winner] == all_players[2]) {
            trick2++;
            team_1++;
        } else if (all_players[winner] == all_players[3]) {
            trick3++;
            team_2++;
        }
        return winner;
    }
    
    void trick_leading_order() {
        team_1 = 0;
        team_2 = 0;
        for (int i = 0; i < 4; i++) {
            leader = trick(leader);
        }
    }
    
    void hand_scoring(int points_to_win) {
        trick_leading_order();
        int winning_team = 0;
        if (team_1 > team_2) {
            cout << all_players[0] << " and " << all_players[2] <<
            " win the hand" << endl;
            winning_team = 1;
        } else if (team_2 > team_1) {
            cout << all_players[1] << " and " << all_players[3] <<
            " win the hand" << endl;
            winning_team = 2;
        }
        
        if (winning_team == 1 && trick0 + trick2 >= 3) {
            if (up_card_player == all_players[0] ||
                up_card_player == all_players[2]) {
                team_1 += 1;
                if (trick0 + trick2 >= 5) {
                    cout << "march!" << endl;
                    team_1 += 2;
                }
            } else if (winning_team == 2 && trick1 + trick3 >= 3) {
            if (up_card_player == all_players[1] ||
                up_card_player == all_players[3]) {
                team_2 += 1;
                if (trick1 + trick3 >= 5) {
                    cout << "march!" << endl;
                    team_2 += 2;
                    }
                }
            }
        }
        if (winning_team == 1 && trick0 + trick2 >= 3) {
            team_1 += 2;
            cout << "euchred!" << endl;
        } else if (winning_team == 1 && trick0 + trick2 >= 3) {
            team_2 += 2;
            cout << "euchred!" << endl;
        }
        
        if (team_1 >= points_to_win) {
            cout << all_players[0] << " and " << all_players[2] << " win!"
            << endl;
            gameover = true;
        } else if (team_2 >= points_to_win) {
            cout << all_players[1] << " and " << all_players[3] << " win!"
            << endl;
            gameover = true;
        }
    }
    bool get_gameover() {
        return gameover;
    }
    
private:
    Pack pack;
    vector<Player*> all_players;
    vector<Player*> player_order;
    Player *up_card_player;
    int dealer = 0;
    int leader = 0;
    int hand = 0;
    int trick0 = 0;
    int trick1 = 0;
    int trick2 = 0;
    int trick3 = 0;
    int team_1 = 0;
    int team_2 = 0;
    string trump = "";
    bool gameover = false;
    Card trumpcard = Card();
};

int main(int argc, char *argv[]) {
    string filename = argv[1];
    int points_to_win = atoi(argv[3]);
    string shuffle_or_not = argv[2];
    string player_0_name = argv[4];
    string player_0_strategy = argv[5];
    string player_1_name = argv[6];
    string player_1_strategy = argv[7];
    string player_2_name = argv[8];
    string player_2_strategy = argv[9];
    string player_3_name = argv[10];
    string player_3_strategy = argv[11];

    //Error message if pack does not open
    ifstream pack;
    pack.open(filename);
    if(!pack.is_open()) {
        cout << "Error opening " << filename << endl;
        return 1;
    }
    //Checks all command line arguments are valid according to the spec
    if (argc != 12 && points_to_win > 0 && points_to_win < 100 &&
        shuffle_or_not != "shuffle" && shuffle_or_not != "noshuffle" &&
        player_0_strategy != "Simple" && player_0_strategy != "Human" &&
        player_1_strategy != "Simple" && player_1_strategy != "Human" &&
        player_2_strategy != "Simple" && player_2_strategy != "Human" &&
        player_3_strategy != "Simple" && player_3_strategy != "Human") {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }
    
    //Fill players and run the game
    Player *player0 = Player_factory(player_0_name, player_0_strategy);
    Player *player1 = Player_factory(player_1_name, player_1_strategy);
    Player *player2 = Player_factory(player_2_name, player_2_strategy);
    Player *player3 = Player_factory(player_3_name, player_3_strategy);
    vector<Player*> all_players;
    all_players = {player0, player1, player2, player3};
    Game run_game(all_players, pack);
    
    //Print command line at top
    for(int i = 0; i < 12; i++){
         cout << argv[i] << " ";
    }
    cout << endl;
    
    bool gameover = run_game.get_gameover();
    while (!gameover) {
        Card up_card = run_game.new_hand(shuffle_or_not);
        run_game.who_chose_trump(up_card);
        run_game.trick_leading_order();
        run_game.hand_scoring(points_to_win);
    }
    return 0;
}
