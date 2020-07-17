//
// Created by Dell on 2019/6/23.
//
#include "cardDef.h"
#ifndef HWX_DYNAMICARRAY_H
#define HWX_DYNAMICARRAY_H
Card *addCard(Card *stackcard, int num, Card onecard,int maximum);
Card *deleteCard(Card *stackcard, int stacknum);

Card *playaCard(Card *handcard,int handnum, Card onecard);
Card *deletebyIndex(Card *cardset, int index, int precardnum, Card *preCard, int *attackadd);
#endif //HWX_DYNAMICARRAY_H
