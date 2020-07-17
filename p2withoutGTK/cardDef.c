//
// Created by Dell on 2019/6/22.
//
#define RAND_TIME 1000
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "cardDef.h"
Card *makeCard(Card *All_card, int decknum){
    enum suits s;
    int count=0;
    int num=0;
    for(;count<decknum;count++){
    for (s=SPADES;s<=CLUBS;s++){
        for(int j=1;j<=13;j++){
            All_card[num].suit=s;
            //printf("%d ",j);
            All_card[num].num=j;
            num++;
        }
    }
    }
    return All_card;  //return the exercise
}
Card *shuffleCard(Card *Cards,int cardnum){
    int ch1,ch2;
    srand((unsigned)time(NULL));
    for(int i=1;i<RAND_TIME;i++){
        ch1=rand()%(2*cardnum-4);
        ch2=rand()%(2*cardnum-4);
        if(ch1>(cardnum-1)){
            ch1=2*cardnum-4-ch1;
        }
        if(ch2>(cardnum-1)){   //change from 52 into cardnum-1...
            ch2=2*cardnum-4-ch2;
        }
        if(ch1==ch2){
            continue;
        }
        Card terminal=Cards[ch1];
        Cards[ch1]=Cards[ch2];
        Cards[ch2]=terminal;
    }
    return Cards;
}

int printCard(Card *cardset, int cardnum){
    int count=0;
    char *suit[4]={"Spades","Hearts","Diamonds","Clubs"};
    char *number[13]={"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
    if (cardnum==0) return 0;
    for(count=0;count<cardnum;count++){
        printf("%d: ",count+1);
        if (cardset[count].suit<=3&&cardset[count].suit>=0){
        printf("<%s ",suit[cardset[count].suit]);
        }
        if (cardset[count].num<=13&&cardset[count].num>=1){
        printf("%s >",number[cardset[count].num-1]);
        }

    }
    printf("--\n");
    return 0;
}


int comp(const void *p1, const void *p2){
    Card *c=(Card *)p1;
    Card *d=(Card *)p2;
    if (c->suit==d->suit){
        return (c->num-d->num);
    }
    else {
        return (c->suit-d->suit);
    }
}

int fprintCard(Card *cardset, int cardnum, FILE *fp){
    int count=0;
    char *suit[4]={"Spades","Hearts","Diamonds","Clubs"};
    char *number[13]={"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
    if(cardnum==0) return 0;
    for(count=0;count<cardnum;count++){
            if (cardset[count].suit<=3&&cardset[count].suit>=0){
        fprintf(fp,"%s ",suit[cardset[count].suit]);
        }
        if (cardset[count].num<=13&&cardset[count].num>=1){
        fprintf(fp,"%s ",number[cardset[count].num-1]);
        }
    }
    fprintf(fp,"-----------------------\n");
    fprintf(fp,"\n");
    return 0;
}

void printWelcome(void){
    printf("########################\n");
    printf("#                      #\n");
    printf("# Welcome to One Card! #\n");
    printf("#                      #\n");
    printf("########################\n");
}

int printAsci(Card *cardset, int cardnum) {
    char *number[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    int i=0;
    for(i=0;i<cardnum;i++){
        printf(" ___ ");
        printf(" ");
    }
    printf("\n");

    for(i=0;i<cardnum;i++){
        printf("|");
        printf("%s",number[cardset[i].num-1]);
        if(cardset[i].num==9){
            printf(" ");

        }
        else{
            printf("  ");
        }
        printf("| ");
    }
    printf("\n");

    for(i=0;i<cardnum;i++){
        switch (cardset[i].suit) {
            case 0:
                printf("| ^ | ");
                break;
            case 1:
                printf("|(`)| ");
                break;
            case 2:
                printf("| /\\| ");
                break;
            case 3:
                printf("| O | ");
                break;
        }
    }
    printf("\n");
    for(i=0;i<cardnum;i++){
        switch(cardset[i].suit) {
            case 0:
                printf("|(,)| ");
                break;
            case 1:
                printf("|_\\_| ");
                break;
            case 2:
                printf("|_\\/| ");
                break;
            case 3:
                printf("|O,O| ");
                break;

        }
    }
    printf("\n");
    for(i=0;i<cardnum;i++){
        printf("  %d   ",i+1);
    }
    printf("\n");
    return 0;
}

