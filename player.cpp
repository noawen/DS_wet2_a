//
// Created by Dell on 04/06/2018.
//

#include "player.h"

Player::Player(int id, int score){
    id = id;
    score = score;
}

Player::Player(int id){
    id = id;
    score = 0;
}

int Player::getId() {
    return id;
}

void Player::setId(int id) {
    id = id;
}

int Player::getScore() {
    return score;
}

void Player::setScore(int score) {
    score = score;
}