//
// Created by Dell on 2019/6/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<getopt.h>

#include "cardDef.h"
#include "playerList.h"
#include "Dynamicarray.h"
#include "demomode.h"
#include "time.h"
#include "manmachine.h"
#define CARDTYPE sizeof(Card)
#define INTTYPE sizeof(int)


#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* Flag set by ‘--verbose’. */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* Flag set by ‘--verbose’. */


int
main (int argc, char **argv)
{
  int c;
  int playernum=4;
  int initialcardnum=5;
  int roundnum=1;
  int decknum=2;
  int startornot=0;
  int AIhuman=0;
  char logfile[30];    // the name of the logfile should be longer than 30..
  

  while (1)
    {
      static struct option long_options[] =
        {
          /* These options set a flag. */

          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"auto",     no_argument,       0, 'a'},
          {"help",  no_argument,       0, 'h'},
          {"decks",  required_argument, 0, 'd'},
          {"initial-card", required_argument, 0, 'c'},
          {"player-number",required_argument  ,0,'n'},
          {"log",    required_argument, 0, 'l'},
          {"rounds",required_argument,0,'r'},     
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "ahd:c:n:l:r:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 'a':
          puts ("option -a\n");
          AIhuman=1;
          startornot=1;
          break;

        case 'h':
          puts ("option -h\n");
          puts("-h|--help print this help message\n");
        puts("--log filename write the logs in filename (default: onecard.log)\n");
        puts("-n n|--player-number=n n players, n must be larger than 2 (default: 4)");
        puts("-l filename|--log=filename write the logs in filename (default: onecard.log)\n");
        puts("-c c|--initial-cards=c deal c cards per player, c must be at least 2 (default: 5)");
        puts("-d d|--decks=d use d decks 52 cards each, d must be at least 2 (default: 2)");
        puts("-r r|--rounds=r play r rounds, r must be at least 1 (default: 1)");
        puts("-a|--auto run in demo mode)");
          AIhuman=-2;
          break;

        case 'c':
        startornot=1;
        if(optarg!=NULL){
          printf ("option -c with value `%s'\n", optarg);
          initialcardnum=atoi(optarg);
          }
          
          
       if(optarg==NULL){
           printf("no argument");
       }
          break;

        case 'd':
        startornot=1;
        if(optarg!=NULL){
          printf ("option -d with value `%s'\n", optarg);
          decknum=atoi(optarg);
          }

          break;
        case 'r':
        startornot=1;
            if (optarg!=NULL)
            {
                printf("option -r with value %s\n",optarg);
                roundnum=atoi(optarg);
                printf("the round num set: %d\n",roundnum);

            }
            else{
              printf("no argument..\n");
            }
            
            break;

        case 'l':
        
            if(optarg!=NULL){
          printf ("option -f with value `%s'\n", optarg);
          if(strlen(optarg)>30){
              printf("you put a filename too long...");
          }

          unsigned long int i=0;
          for(i=0;i<strlen(optarg);i++){
              logfile[i]=optarg[i];
          }
          logfile[strlen(optarg)]='\0';
          printf(" the logfile is %s ",logfile);
          }

          printf("%s\n",logfile);

          break;
        case 'n':
        startornot=1;
        
          if(optarg!=NULL){
              printf("option -n with value %s",optarg);
              playernum=atoi(optarg);
          }
               
            break;
        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }

  /* Instead of reporting ‘--verbose’
     and ‘--brief’ as they are encountered,
     we report the final status resulting from them. */
    logfile[0]='o';
    logfile[1]='n';
    logfile[2]='e';
    logfile[3]='c';
    logfile[4]='a';
    logfile[5]='r';
    logfile[6]='d';
    logfile[7]='.';
    logfile[8]='l';
    logfile[9]='o';
    logfile[10]='g';
    logfile[11]='\0';
    //printf("the logfile has been initially set as %s", logfile);
  FILE *fp=fopen(logfile,"w+");
  if(fp==NULL){
      printf("fail to open the log file");
  }
  else if(fp!=NULL){
      //printf("the log file has been successfull opened");
  }


if(startornot==1&&AIhuman==1){
    demo(playernum,roundnum,initialcardnum,decknum);
}
else if(AIhuman==0&&startornot==1){
    manmachineMode(playernum,roundnum,initialcardnum,decknum,fp);
}

  /* Print any remaining command line arguments (not options). */
  printf("logfile closed.");
  fclose(fp);
  exit (0);
}


