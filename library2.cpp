//
// Created by Dell on 12/06/2018.
//

#include "library2.h"
#include "oasis.h"

void* init(int n, int *clanIDs){
    Oasis *DS;
    try {
        DS = new Oasis(n, clanIDs);
    } catch(OasisExceptions&) {
        return NULL;
    }
    return (void*)DS;
}

StatusType addClan(void *DS, int clanID){
    if (!DS){
        return INVALID_INPUT;
    }
    try {
        ((Oasis*) DS)->addClan(clanID);
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
    catch(INVALID_INPUT_OASIS&){
        return INVALID_INPUT;
    }
    catch(FAILURE_OASIS&){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType addPlayer(void *DS, int playerID, int score, int clan){
    if (!DS){
        return INVALID_INPUT;
    }
    try{
        ((Oasis*)DS)->addPlayer(playerID,score,clan);
    }
    catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
     catch (INVALID_INPUT_OASIS&){
        return INVALID_INPUT;
    }
    catch (FAILURE_OASIS&){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType clanFight(void *DS, int clan1, int clan2, int k1, int k2){
    if(!DS){
        return INVALID_INPUT;
    }
    try{
        ((Oasis*)DS)->clanFight(clan1,clan2,k1,k2);
    } catch (INVALID_INPUT_OASIS&){
        return INVALID_INPUT;
    } catch (FAILURE_OASIS&){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType getMinClan(void *DS, int *clan){
    if(!DS){
        return INVALID_INPUT;
    }
    try{ ((Oasis*)DS)->getMinClan(clan);
    }
    catch (INVALID_INPUT_OASIS&){
        return INVALID_INPUT;
    }
    catch (FAILURE_OASIS&){
        return FAILURE;
    }
    return SUCCESS;
}

void quit(void** DS) {
    if (DS != NULL) {
        delete (Oasis*) (*DS);
        *DS = NULL;
    }
}