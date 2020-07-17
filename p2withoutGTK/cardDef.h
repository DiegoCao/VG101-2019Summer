//
// Created by Dell on 2019/6/22.
//
#include <stdio.h>
#ifndef HWX_CARDDEF_H
#define HWX_CARDDEF_H
enum suits{SPADES,HEARTS,DIAMONDS,CLUBS};
typedef struct onecard{
    enum suits suit;
    int num;
}Card;
Card *makeCard(Card *All_card, int decknum);
Card *shuffleCard(Card *Cards,int cardnum);
int printCard(Card *cardset, int cardnum);
int fprintCard(Card *cardset, int cardnum, FILE *fp);
int comp(const void *p1, const void *p2);
void printWelcome(void);
int printAsci(Card *cardset, int cardnum);
#endif //HWX_CARDDEF_H
