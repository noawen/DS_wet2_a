//
// Created by Dell on 04/06/2018.
//

#ifndef DS_WET2_A_PLAYER_H
#define DS_WET2_A_PLAYER_H

#include "AVLtree.h"
#include "clan.h"

class is_bigger_by_id_player;
class is_bigger_by_score_player;

class Player{
    int id;
    int score;

public:
    Player(int id, int score);

    Player(int id);

    int getId();

    void setId(int id);

    int getScore();

    void setScore(int score);
};



class is_bigger_by_id_player {
        public:
        int operator()(Player* a, Player* b) {
            if ((*a).getId() < (*b).getId()) {
                return -1;
            }
            if ((*a).getId() > (*b).getId()) {
                return 1;
            }
            return 0;
        }
};

class is_bigger_by_score_player {
public:
    int operator()(Player *a, Player *b) {
        if ((*a).getScore() < (*b).getScore()) {
            return -1;
        }
        if ((*a).getScore() > (*b).getScore()) {
            return 1;
        }
        if ((*a).getScore() == (*b).getScore()) {
            if ((*a).getId() < (*b).getId()) {
                return 1;
            } else if(((*a).getId() > (*b).getId())) {
                return -1;
            }
        }
        return 0;
    }
};






#endif //DS_WET2_A_PLAYER_H