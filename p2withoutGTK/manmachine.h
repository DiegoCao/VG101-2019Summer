//
// Created by Dell on 2019/6/26.
//
#include "cardDef.h"
#include <stdio.h>
#ifndef HWX_MANMACHINE_H
#define HWX_MANMACHINE_H
int manmachineMode(int player_num, int roundnum, int initialcard, int decks, FILE *fp);
int checkInput(Card * preCard, Card *handCard, int index);
#endif //HWX_MANMACHINE_H
