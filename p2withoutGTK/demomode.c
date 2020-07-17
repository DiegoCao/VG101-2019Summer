//
// Created by Dell on 2019/6/25.
//
#include "demomode.h"
#include "Dynamicarray.h"
#include "cardDef.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "playerList.h"

int demo(int player_num, int roundnum, int initialcard, int decks){
    printWelcome();
    int myround=0;
    int cycletime;
    Player *PLAYERHEAD=initPlayer(player_num);
    int stacknum,discardnum,attack;
    attack=1;
    int *attackadd=&attack;
    int clockwise=1;
    int decknum=decks;
    int prediscardnum=decknum*52;
    int detect;    //detect whether the player can play or not
    while(myround<roundnum){
        Player *temp=PLAYERHEAD;
        myround++;
        Card *All_Card=(Card *)malloc(sizeof(Card)*decknum*52);
        All_Card=makeCard(All_Card,decknum);
        printCard(All_Card,decknum*52);
        Card *stack_card=shuffleCard(All_Card,decknum*52);
        printCard(stack_card,decknum*52);
        Card *discard=(Card *)malloc(sizeof(Card)*prediscardnum);
        Card *allocard=(Card *)malloc(sizeof(Card)*initialcard);
        stacknum=52*decknum;
        discardnum=0;
        Card *preCard=(Card *)malloc(sizeof(Card)*3);
        int i=0;
        for (;i<player_num;i++) {
            temp = temp->next;
            int j = 0;
            for (j = 0; j < initialcard; j++) {
                allocard[j] = stack_card[0];
                stack_card = deleteCard(stack_card, stacknum);
                stacknum--;
            }
            //printCard(allocard,initialcard);
            printf("\n");
            int k = 0;
            for (k = 0; k < initialcard; k++) {
                temp->handcards = addCard(temp->handcards, temp->handnum, allocard[k], 52);
                temp->handnum++;
            }
        }
        printf("%d\n",stacknum);
        printCard(temp->handcards,temp->handnum);
        temp=PLAYERHEAD;
        temp=temp->next;
        preCard[0]=temp->handcards[0];
        printf("the preCard\n");
        printCard(preCard,1);
        cycletime=0;

        Card *card_to_draw=(Card *)calloc(52,sizeof(Card));
        while(1){
            cycletime++;
            //printCard(preCard,1);
            if (clockwise==1){
                temp=temp->next;
            }
            if(clockwise==0){
                temp=temp->last;
            }
            printf("Player %d handcard:\n",temp->name);
            printCard(temp->handcards,temp->handnum);
            printf("the car that the last player plays:\n");
            printCard(preCard,1);

            detect=playorNot(PLAYERHEAD,temp->name,preCard,attackadd);

            if(detect==0){
                printf("sadly cannot play cards...");
                int drawnum=0;
                printf("Player %d draw %d cards...\n",temp->name,attack);
                for(;drawnum<attack;drawnum++){
                    card_to_draw[drawnum]=stack_card[0];
                    printf("one drawed....\n");
                    stack_card=deleteCard(stack_card,stacknum);
                    stacknum--;
                    temp->handcards=addCard(temp->handcards,temp->handnum,card_to_draw[drawnum],52);
                    temp->handnum++;
                }
                attack=1;
            }
            else if(detect==1){
                temp->handcards=playaCard(temp->handcards,temp->handnum,preCard[0]);
                temp->handnum--;
                printf("playCard:user %d plays card:  ",temp->name);
                printCard(preCard,1);
                if (temp->handnum==0){
                    printf("Player %d win this round\n   ",temp->name);
                    break;
                }
                addCard(discard,discardnum,preCard[0],prediscardnum);
                discardnum++;
                //printCard(discard,discardnum);
                printf("done!");
            }
            else if(detect==2){
                printf("detect wrong!");
                break;
            }
            if (preCard[0].num==11&&detect==1){
                printf("change direction!\n");
                if(clockwise==1){
                    clockwise=0;
                }
                else
                    clockwise=1;
            }
            if (preCard[0].num==10&&detect==1){  //the last player can draw cards
                printf("Jump through the next player!\n");
                if (clockwise==0){
                    temp=temp->last;
                }
                else if(clockwise==1){
                    temp=temp->next;
                }
            }

            if (stacknum<=attack){// the stackcard num not enough, shuffle the cards again
                printf("shuffling...");
                Card *tempcard=(Card *)malloc(sizeof(Card)*(discardnum+stacknum));
                int t=0;
                for(;t<stacknum;t++){
                    tempcard[t]=stack_card[t];
                }
                for(t=stacknum;t<stacknum+discardnum;t++){
                    tempcard[t]=discard[t-stacknum];
                }
                shuffleCard(tempcard,stacknum+discardnum);
                 for(i=0;i<stacknum+discardnum;i++){
                    stack_card[i]=tempcard[i];
                }
 
                stacknum=stacknum+discardnum;
                discardnum=0;

            }
            printf("Player %d new cards: ", temp->name);
            sortCard(PLAYERHEAD,player_num);
            printCard(temp->handcards,temp->handnum);
            //printf("Discard numbers :%d\n",discardnum);
            //printf("the discard cards\n");
            //printCard(discard,discardnum);
            printf("one loop done!");
            printf("************************\n");

            printf("\n");
            getchar();
            getchar();
        }

        printf("one round done!");
        PLAYERHEAD=countscore(PLAYERHEAD,player_num);
        printScore(PLAYERHEAD,player_num);
        /*free(stack_card);
        free(discard);
        free(preCard);
        free(allocard);
        free(card_to_draw);
        free(All_Card);*/
        freeHandcard(PLAYERHEAD,player_num);

    }
    whoWins(PLAYERHEAD,player_num);
    return 0;
}


