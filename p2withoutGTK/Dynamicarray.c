//
// Created by Dell on 2019/6/23.
//

#include "Dynamicarray.h"



#include <stdlib.h>
#include <stdio.h>

Card *addCard(Card *stackcard, int num, Card onecard,int maximum){
    if (num>=maximum){
        printf("memory not enough...");
        stackcard=realloc(stackcard,(num+4)*sizeof(Card));
    }


    stackcard[num]=onecard;
    return stackcard;
}

Card *deleteCard(Card *stackcard, int stacknum){
    int i=0;
    for (;i<stacknum-1;i++){
        stackcard[i]=stackcard[i+1];
    }
    return stackcard;

}
Card *deleteHandCard(Card *Handcard, int handnum){
    Handcard[handnum-1].num=0;
    Handcard[handnum-1].suit=0;
    return Handcard;
}

Card *playaCard(Card *handcard,int handnum, Card onecard) {
    int i = 0;
    int flag=-1;
    for (; i < handnum; i++) {
        if (handcard[i].num == onecard.num && handcard[i].suit == onecard.suit) {
            handcard[i] = handcard[handnum - 1];
            handcard = deleteHandCard(handcard, handnum);
            flag=1;
            break;
        }
    }
    if (flag==1) {
        return handcard;
    }
    else{
        printf("wrong!\n");
        return handcard;
    }
}


Card *deletebyIndex(Card *cardset, int index, int precardnum, Card *preCard, int *attackadd){
    int count=index-1;   // we need to -1 since this index should not be the corresponding index
    Card temp=preCard[0];
    preCard[0]=cardset[count];
    for(;count<precardnum-1;count++){
        cardset[count]=cardset[count+1];
    }
    if(preCard[0].num==2||preCard[0].num==3){
        if(temp.num==2||temp.num==3){
            *attackadd=*attackadd+preCard[0].num;
        }
        else{
            *attackadd=preCard[0].num;
        }
    }
    else if(preCard[0].num==6){
        *attackadd=1;
    }

    return cardset;
}
