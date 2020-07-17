//
// Created by Dell on 2019/6/26.
//

#include "manmachine.h"
#include "Dynamicarray.h"
#include "playerList.h"
#include <stdlib.h>
#include <stdio.h>

int manmachineMode(int player_num, int roundnum, int initialcard, int decks,FILE *fp){
    printWelcome();
    int myround=0;
    Player *PLAYERHEAD=initPlayer(player_num);
    int stacknum,discardnum,attack;
    attack=1;
    int prediscardnum=decks*52;
        int decknum=decks;
    int *attackadd=&attack;
    for(myround=0;myround<roundnum;myround++){
        printf("ROUND %d starts :\n",myround+1);
        Card *All_Card=(Card *)malloc(sizeof(All_Card)*52*decknum);
        All_Card=makeCard(All_Card,decknum);
        Card *stack_card=shuffleCard(All_Card,52*decknum);
        Card *discard=(Card *)malloc(sizeof(Card)*52*decknum);
        stacknum=decknum*52;
        discardnum=0;
        Card *card_to_draw=(Card *)malloc(sizeof(Card)*10);//still need to add more...
        Card *preCard;
        preCard = (Card *) calloc(decknum,sizeof(Card));//
        //printCard(stack_card,52*decknum);
        int clockwise=1;
        int detect;
        int cycletime=0;
        int i=0;
        Player *temp=PLAYERHEAD;
        Card *allocard=(Card *)malloc(sizeof(Card)*initialcard);
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
        int playcardsornot;
        temp=temp->next;
        preCard[0]=temp->handcards[0];
        while(cycletime<5000){  //in case that some players repetively play cards
            //card_to_draw=realloc(card_to_draw,attack);
            cycletime++;
            fprintf(fp,"player %d handcard:\n",temp->name);
            fprintCard(temp->handcards,temp->handnum,fp);
            if(clockwise==1)temp=temp->next;
            else temp=temp->last;
            if(temp->name==1){
                printf("your hand cards:\n");
                printAsci(temp->handcards,temp->handnum);
                int mydetect=detectPlay(preCard,temp->handcards,temp->handnum);
                printf("the previous user play:\n");
                printAsci(preCard,1);  //need to change, and add a variable to record the preCard num..
                printf("would you want to play cards? enter 1 for yes and 2 for no");
                
                scanf("%d",&playcardsornot);
                getchar();
                while(playcardsornot!=1&&playcardsornot!=2){
                    printf(" please enter 1 for play and 2 for no");
                    scanf("%d",&playcardsornot);
                    getchar();
                }
                if(mydetect==0){
                    printf("You have no proper cards to play sadly....\n");
                }
                if(mydetect==0||playcardsornot==2){
                    int drawnum=0;
                    for(;drawnum<attack;drawnum++){
                        card_to_draw[drawnum]=stack_card[0];
                        printf("one card is drawed....\n");
                        stack_card=deleteCard(stack_card,stacknum);
                        stacknum--;
                        temp->handcards=addCard(temp->handcards,temp->handnum,card_to_draw[drawnum],52);
                        temp->handnum++;
                    }
                    if(attack>1){
                        attack=1;
                    }
                    fprintf(fp,"Player draw newcards");
                }
                else if(mydetect==1&&playcardsornot==1){
                    int playmore=1;
                    int moredetect=1;
                    while(playmore==1&&moredetect==1) {
                        printf("Choose one card by enter ..");
                        int choosecardnum;
                        int inputresult = scanf("%d", &choosecardnum);
                        getchar();
                        if (inputresult != 1) {
                            printf("input wrong,please restart the game......\n");
                            
                            inputresult = scanf("%d", &choosecardnum);
                        }  // why here the repetitive loops???
                        while (rightChoice(temp->handcards,temp->handnum,choosecardnum,preCard)!= 1 ||
                               choosecardnum > temp->handnum) {
                            printf("you cannot play this card....");
                            if(choosecardnum>temp->handnum){
                                exit(-1);  //
                            }

                            inputresult = scanf("%d", &choosecardnum);
                            getchar();
                        }
                        addCard(discard, discardnum, preCard[0], prediscardnum);
                        temp->handcards = deletebyIndex(temp->handcards, choosecardnum, temp->handnum, preCard,attackadd);
                        
                        discardnum++;
                        temp->handnum--;
                        if(temp->handnum==0){
                            printf("no card left hhh why play? ");
                            break;
                        }
                        printf("you have played one card:\n");
                        printCard(preCard,1);
                        printf("play more cards or not? Enter 1 for play and press enter, enter other number for quit\n");

                        while(scanf("%d",&playmore)!=1){
                            printf("you enter wrong thing!");
                            getchar();
                        }
                        getchar();
                        moredetect=detectPlay(preCard,temp->handcards,temp->handnum);
                        if(moredetect==0){
                            printf("you can not play more cards...\n");
                        }
                        if(moredetect==1){
                            printf("now you cards turn into: \n");
                            printAsci(temp->handcards,temp->handnum);

                        }
                    }
                    if (temp->handnum==0){
                        printf("You win this round!\n");
                        break;
                    }
                }
                getchar();

                system("cls");
            }
            else if(temp->name!=1){
                detect=playorNot(PLAYERHEAD,temp->name,preCard,attackadd);
                if(detect==0){
                    int drawnum=0;
                    printf("Player %d draw %d cards...\n",temp->name,attack);
                    getchar();
                    for(;drawnum<attack;drawnum++){
                        card_to_draw[drawnum]=stack_card[0];
                        //printf("one drawed...\n");
                        stack_card=deleteCard(stack_card,stacknum);
                        stacknum--;

                       // printf("the stack num %d",stacknum);

                        temp->handcards=addCard(temp->handcards,temp->handnum,card_to_draw[drawnum],52);
                        temp->handnum++;
                    }
                    if(attack>1){
                        attack=1;
                    }
                }
                else if(detect==1){
                    temp->handcards=playaCard(temp->handcards,temp->handnum,preCard[0]);
                    temp->handnum--;
                    printf("playCard:user %d plays card:  ",temp->name);
                    getchar();
                    printCard(preCard,1);
                    fprintf(fp,"playCard:user %d plays card:  ",temp->name);
                    fprintCard(preCard,1,fp);
                    if (temp->handnum==0){
                        printf("Player %d win this round\n   ",temp->name);
                        break;
                    }
                    discard=addCard(discard,discardnum,preCard[0],prediscardnum);
                    discardnum++;
                    
                }
            }
            if ((preCard[0].num==11&&detect==1&&temp->name!=1)||(preCard[0].num==11&&temp->name==1&&playcardsornot==1)){   //add detect==1, to ensure this special card would not repetitively function
                printf("change direction!\n");
                if(clockwise==1){
                    clockwise=0;
                }
                else
                    clockwise=1;
            }
            if ((preCard[0].num==10&&detect==1&&temp->name!=1)||(preCard[0].num==11&&temp->name==1&&playcardsornot==1)){
                printf("Jump through the next player!\n");
                if (clockwise==0){
                    temp=temp->last;
                }
                else if(clockwise==1){
                    temp=temp->next;
                }
            }
            if (stacknum<=attack||stacknum<3){
                // the stackcard num not enough, shuffle the cards again
                printf("shuffling...");
                //system("Pause");
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
            //printf("Player %d new cards\n", temp->name);  //here, add the fprintf...
            sortCard(PLAYERHEAD,player_num);
            //printCard(temp->handcards,temp->handnum);   no need to print out the card of the AI mode
            //fflush(stdout);
            
            fprintf(fp,"player %d new cards\n", temp->name);
            fprintCard(temp->handcards,temp->handnum,fp);
            //system("Pause");

        }
        PLAYERHEAD=countscore(PLAYERHEAD,player_num);
        printScore(PLAYERHEAD,player_num);
        free(All_Card);
        free(stack_card);
        free(discard);
        free(card_to_draw);
        free(preCard);
        freeHandcard(PLAYERHEAD,player_num);
    }
    whoWins(PLAYERHEAD,player_num);
    
    return 0;
}
/* 
int checkInput(Card * preCard, Card *handCard, int index){
    if(preCard[0].num==0) return 1;
    if(preCard[0].suit==handCard[index-1].suit||preCard[0].num==handCard[index-1].num){
        return 1;
    }
    else return 0;
}*/

/*int sumhandnum(Player *playerhead){
    int total=0;
    Player *temp
}*/
