//
// Created by Dell on 12/06/2018.
//

#include <iostream>
#include "library2.h"
#include <cassert>
#include <ctime>
#include <thread>

void* testInit1(){
    int arr[]={5,2,1,4,3};
    int bad_arr[]={5,2,-1};
    assert(init(3,NULL)==NULL);
    assert(init(1,arr)==NULL);
    assert(init(0,arr)==NULL);
    assert(init(-1,arr)==NULL);
    assert(init(3,bad_arr)==NULL);
    bad_arr[1]=0; //just for csl..
    return init(5,arr);
}
void* testInit2(){ //this is the main init we will use
    int arr[20];
    for(int i=0; i<20; i++){
        arr[19-i]=i;
    }
    std::cout<<"Passed initial test..."<<std::endl;
    return init(20,arr);
}
void testAddClan1(void* oasis){
    assert(addClan(oasis,1)==FAILURE);
    assert(addClan(oasis,2)==FAILURE);
    assert(addClan(oasis,3)==FAILURE);
    assert(addClan(oasis,4)==FAILURE);
    assert(addClan(oasis,5)==FAILURE);
    assert(addClan(NULL,1)==INVALID_INPUT);
    assert(addClan(oasis,-1)==INVALID_INPUT);
}
void testAddClan2(void* oasis){
    for(int i=0;i<20;i++){
        assert(addClan(oasis,i)==FAILURE);
    }
    for(int i=100;i<110;i++){
        assert(addClan(oasis,i)==SUCCESS);
    }
    std::cout<<"Passed add clan test..."<<std::endl;
}
void testAddPlayer(void* oasis){
    assert(addPlayer(NULL, 1, 1, 1)==INVALID_INPUT);
    assert(addPlayer(oasis, -1, 1, 1)==INVALID_INPUT);
    assert(addPlayer(oasis, 1, -1, 1)==INVALID_INPUT);
    assert(addPlayer(oasis, 1, 1, -1)==INVALID_INPUT);
    assert(addPlayer(oasis, 1, 1, 20)==FAILURE);
    for (int i = 0; i < 10; ++i) {
        assert(addPlayer(oasis,60+i,55+i,0)==SUCCESS);
        //  player(i) with id 60+i score 55+i clan0
    }
    for (int i = 0; i < 10; ++i) {
        assert(addPlayer(oasis,100+i,100+i,1)==SUCCESS);
        //  player(i) with id 100+i score 100+i clan1
    }
    for (int i = 0; i < 5; ++i) {
        assert(addPlayer(oasis,20+i,20+i,2)==SUCCESS);
        //  player(i) with id 20+i score 20+i clan2
    }
    //check if the players are in the system
    for (int i = 0; i < 10; ++i) {
        assert(addPlayer(oasis,60+i,55+i,0)==FAILURE);
        assert(addPlayer(oasis,100+i,100+i,1)==FAILURE);
        if(i<5)
            assert(addPlayer(oasis,20+i,20+i,2)==FAILURE);
    }
    for (int i = 3; i < 19; ++i) {
        assert(addPlayer(oasis,i,i,i)==SUCCESS);
        //the clans 3-18 get one player each that have id as the clan and score as the clan
        assert(addPlayer(oasis,i,i,i==FAILURE));
    }
    std::cout<<"Passed add player test..."<<std::endl;
}
void testFightAndMin(void* oasis){
    assert(clanFight(NULL, 0, 1, 1, 1)==INVALID_INPUT);
    assert(clanFight(oasis, -1, 1, 1, 1)==INVALID_INPUT);
    assert(clanFight(oasis, 0, -1, 1, 1)==INVALID_INPUT);
    assert(clanFight(oasis, 0, 1,0, 1)==INVALID_INPUT);
    assert(clanFight(oasis, 0, 1, 1, 0)==INVALID_INPUT);
    assert(clanFight(oasis, 0, 1, 11, 1)==FAILURE);
    assert(clanFight(oasis, 0, 1, 1, 11)==FAILURE);
    assert(clanFight(oasis,0,90,1,1)==FAILURE);
    assert(clanFight(oasis,90,0,1,1)==FAILURE);
    assert(getMinClan(oasis,NULL)==INVALID_INPUT);
    int min_alive;
    assert(getMinClan(NULL,&min_alive)==INVALID_INPUT);
    assert(getMinClan(oasis,&min_alive)==SUCCESS);
    assert(min_alive==0);
    assert(clanFight(oasis, 0, 1, 5, 5)==SUCCESS);    //first fight clan 1 won
    assert(getMinClan(oasis,&min_alive)==SUCCESS);
    assert(min_alive==1);
    assert(addClan(oasis,0)==FAILURE);
    assert(clanFight(oasis, 2, 1, 5, 1)==SUCCESS);    //clan2 won
    assert(getMinClan(oasis,&min_alive)==SUCCESS);
    assert(min_alive==2);
    assert(addClan(oasis,1)==FAILURE);
    assert(addPlayer(oasis,500,1000,19)==SUCCESS);
    assert(addPlayer(oasis,456,2,18)==SUCCESS);
    assert(clanFight(oasis,19,18,1,1)==SUCCESS);
    for (int i = 2; i < 17; ++i) {
        assert(clanFight(oasis, i, 19, 1, 1)==SUCCESS);    //clan19 won
        assert(clanFight(oasis,i-2,i-1,1,1)==FAILURE);      //they cant fight
        assert(getMinClan(oasis,&min_alive)==SUCCESS);
        assert(min_alive==i+1);
        assert(addClan(oasis,i)==FAILURE); //check clan exist
        assert(addPlayer(oasis,900+i,900+i,i)==SUCCESS); //check we can add players to clan
    }
    assert(clanFight(oasis, 17, 19, 1, 1)==SUCCESS); //19 win
    //clan 19 the only able to fight
    assert(addClan(oasis,50)==SUCCESS);
    assert(addClan(oasis,51)==SUCCESS);
    assert(addPlayer(oasis,777,9900,50)==SUCCESS);
    assert(clanFight(oasis,19,50,1,1)==SUCCESS);    //50 won
    assert(getMinClan(oasis,&min_alive)==SUCCESS);
    assert(min_alive==50);
    assert(addPlayer(oasis,776,9900,51)==SUCCESS);
    assert(clanFight(oasis,51,50,1,1)==SUCCESS);    //50 won - check who win if the have the same score
    assert(clanFight(oasis,51,50,1,1)==FAILURE);
    assert(getMinClan(oasis,&min_alive)==SUCCESS);
    assert(min_alive==50);
    std::cout<<"Passed fight and minimum clan alive test..."<<std::endl;
    min_alive=0; //just for csl..
}
void testQuit(void* oasis){
    void** tmp=NULL;
    void* temp=NULL;
    quit(tmp);
    quit(&temp);
    quit(&oasis);
    assert(oasis==NULL);
}



int main(){
    void* oasis=testInit1();
    assert(oasis);
    testAddClan1(oasis);
    quit(&oasis);
    oasis=testInit2(); //on oasis we got 0-19 clans till now
    assert(oasis);
    testAddClan2(oasis); //add some more clans that we wont use and check if all 0-19 are in
    testAddPlayer(oasis);
    testFightAndMin(oasis);
    testQuit(oasis);


    return 0;
}