/*Miglioramento algoritmo mescolatura e distribuzione*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*prototipi di funzione*/
void mescolatura(int deck[][13]);
void distribuzione(int deck[][13], int mseme[], int mnum[], int cpun[], int cpus[], int *carta, int *mazzo); 
int val_mano(int seme[], int num[], char *s[], char *n[]);
void ord_mano(int numero[], int seme[], int copia_num[], int valore[]);
void rivaluta_cpu(int deck[][13], int cpun[], int cpus[], int *carta, int punt, char *n[], char *s[]);
void rivaluta_gio(int deck[][13], int gnum[], int gseme[], int *carta, char *n[], char *s[]);
void stampa_mazzo(int deck[][13], char *n[], char *s[]);
void stampa_mano(char *n[], char *s[], int gion[], int gios[], int cpun[], int cpus[], int *partita);

main()
{
      int riga, colonna, carta, punt_gio, punt_cpu, cart = 1, deck = 52, scelta_menu, cont;
      int mazzo[4][13] = {0};
      char *seme[4] = {"Cuori", "Picchie", "Fiori", "Quadri"}; 
      char *numero[14] = {"Asso", "Due", "Tre", "Quattro", "Cinque", "Sei", "Sette", "Otto", "Nove", "Dieci", "Jack", "Regina", "Re", "Asso"};
      int manos[5] = {0}, manon[5] = {0};
      int cpu_num[5] = {0}, cpu_sem[5] = {0};
      
      /*numero partita*/
      for(cont = 1; cont <= 20; cont++)
      {
               /*randomizza la funzione rand*/
               srand(time(NULL));
               
               /*azzaramento mazzo*/
               for(riga = 0; riga < 4; riga++)
               {
                        for(colonna = 0; colonna < 13; colonna++)
                        {
                                    mazzo[riga][colonna] = 0;
                        }
               }
      
               /*mescola il mazzo*/
               mescolatura(mazzo);
      
               /*distribuisci la mano ai giocatori*/
               distribuzione(mazzo, manos, manon, cpu_num, cpu_sem, &cart, &deck);        
      
               /*stampa le mani dei giocatori*/
               stampa_mano(numero, seme, manon, manos, cpu_num, cpu_sem, &cont);
      
               printf("\n\n\n- - - - - - - - - - - - - - - -\t\t\t- - - - - - - - - - - - - - - -\n\n");
               printf("\t");
      
               /*punto del giocatore*/
               punt_gio = val_mano(manos, manon, seme, numero);
               printf("\t\t\t\t");
      
               /*punto del computer*/
               punt_cpu = val_mano(cpu_sem, cpu_num, seme, numero);
               printf("\n\n- - - - - - - - - - - - - - - -\t\t\t- - - - - - - - - - - - - - - -\n\n");
      
               rivaluta_gio(mazzo, manon, manos, &cart, numero, seme);
      
               rivaluta_cpu(mazzo, cpu_num, cpu_sem, &cart, punt_cpu, numero, seme);
               
               system("cls");
               
               /*stampa le mani dei giocatori*/
               stampa_mano(numero, seme, manon, manos, cpu_num, cpu_sem, &cont);
      
               printf("\n\n\n- - - - - - - - - - - - - - - -\t\t\t- - - - - - - - - - - - - - - -\n\n");
               printf("\t");
      
               /*punto del giocatore*/
               punt_gio = val_mano(manos, manon, seme, numero);
               printf("\t\t\t\t");
      
               /*punto del computer*/
               punt_cpu = val_mano(cpu_sem, cpu_num, seme, numero);
               printf("\n\n- - - - - - - - - - - - - - - -\t\t\t- - - - - - - - - - - - - - - -\n\n");
      
            
      }
}

/*simula la mescolatura del mazzo di 52 carte*/
void mescolatura(int deck[][13])
{
     int riga, colonna, carta = 1, temp, r, c;
     
     /*ordina matrice mazzo*/
     for(riga = 0; riga < 4; riga++)
     {
              for(colonna = 0; colonna < 13; colonna++)
              {
                          deck[riga][colonna] = carta;
                          carta++;
              }
     }
     
     /*ordina matrice mazzo*/
     for(riga = 0; riga < 4; riga++)
     {
              for(colonna = 0; colonna < 13; colonna++)
              {
                          /*scambia la carta deck[riga][colonna] con un altra casuale*/
                          r = rand() % 4;
                          c = rand() % 13;
                          
                          temp = deck[riga][colonna];
                          deck[riga][colonna] = deck[r][c];
                          deck[r][c] = temp;
                          
              }
     }
}

/*distribuisce le 5 carte in mano ai giocatori*/
void distribuzione(int deck[][13], int mseme[], int mnum[], int cpun[], int cpus[], int *carta, int *mazzo)
{
     int riga, colonna, mgio = 0, mcpu = 0;
     static int mano = 5;    /*la carta max da raggiungere*/
     
     if(*carta == 1)
     {
               mano = 5;
     }
     
     /*distribuisce la mano al giocatore*/
     do
     {
               for(riga = 0; riga < 4; riga++)
               {
                        for(colonna = 0; colonna < 13; colonna++)
                        {
                                    if(deck[riga][colonna] == *carta)
                                    {
                                                           mseme[mgio] = riga;
                                                           mnum[mgio] = colonna;
                                                           mgio++;
                                                           *mazzo -= 1;
                                                           colonna = 13;
                                                           riga = 4;
                                    }
                        }
               }
               
               *carta += 1;
               
     }while(*carta <= mano);
       
     mano += 5;
     
     /*distribuisce la mano alla cpu*/
     for(;*carta <= mano; *carta += 1)
     {
                for(riga = 0; riga < 4; riga++)
                {
                         for(colonna = 0; colonna < 13; colonna++)
                         {
                                    if(deck[riga][colonna] == *carta)
                                    { 
                                                           cpus[mcpu] = riga;
                                                           cpun[mcpu] = colonna;
                                                           mcpu++;
                                                           *mazzo -= 1;
                                    }
                         }
                }
     }
     
     mano += 5;
                                     
}

/*determina il punteggio in mano del giocatore*/
int val_mano(int seme[], int num[], char *s[], char *n[])
{
    int carta, conf, pass, temp;
    int freq_num[13] = {0};     /*indica il numero delle uscite dei numeri*/
    int freq_seme[5] = {0};     /*indica il numero delle uscite dei semi*/
    int val[14] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};     /*valore numerico delle carte*/
    int cop_num[5] = {0};       /*copia il vettore numero e lo ordina dal piu piccolo al piu grande*/
    
    /*determina quante volte sono uscite ogni singola carta*/
    for(carta = 0; carta < 5; carta++)
    {
              freq_num[num[carta]]++;
              freq_seme[seme[carta]]++;
    }
    
    /*determinazione del punteggio*/
    for(carta = 0; carta <= 4; carta++)
    {
              /*determina coppia o doppia coppia*/
              if(freq_num[num[carta]] == 2)
              {
                                 /*controlla se ce il colore*/
                                 if(freq_seme[seme[0]] == freq_seme[seme[1]] && freq_seme[seme[0]] == freq_seme[seme[2]] &&  freq_seme[seme[0]] == freq_seme[seme[3]] && freq_seme[seme[0]] == freq_seme[seme[4]])
                                 {
                                                       printf("Colore di %s", s[seme[0]]);
                                                       return 7;
                                 }
                                 
                                 /*controlla se ci sono altre coppie o un altra carta o full*/
                                 for(conf = carta + 1; conf <= 4; conf++)
                                 {
                                          /*se la carta corrente fa parte della coppia gia evidenziata ignora*/
                                          if(num[conf] == num[carta])
                                          {
                                                            continue;
                                          }
                                          
                                          /*se ce un tris assegna full*/
                                          else if(freq_num[num[conf]] == 3)
                                          {
                                               /*assegna full*/
                                               printf("Full di %s e %s", n[num[carta]], n[num[conf]]);
                                               return 6;
                                          }
                                          
                                          /*se ce un altra coppia chiudi e assegna doppia coppia*/
                                          else if(freq_num[num[conf]] == 2)
                                          {
                                                                 /*assegna doppia coppia*/
                                                                 printf("Doppia coppia di %s e %s", n[num[carta]], n[num[conf]]);
                                                                 return 3;
                                          }
                                 }   
                                 
                                 /*se non e uscita doppia coppia assegna coppia*/
                                 /*assegna coppia*/
                                 printf("Coppia di %s", n[num[carta]]);
                                 return 2;
              }   
              
              /*determina tris*/
              else if(freq_num[num[carta]] == 3)
              {
                   /*controlla se ce il colore*/
                   if(freq_seme[seme[0]] == freq_seme[seme[1]] && freq_seme[seme[0]] == freq_seme[seme[2]] &&  freq_seme[seme[0]] == freq_seme[seme[3]] && freq_seme[seme[0]] == freq_seme[seme[4]])
                   {
                                         printf("Colore di %s", s[seme[0]]);
                                         return 7;
                   }
                   
                   /*controlla se ci sono altre coppie*/
                   for(conf = carta + 1; conf <= 4; conf++)
                   {
                            /*se la carta corrente fa parte della coppia gia evidenziata ignora*/
                            if(num[conf] == num[carta])
                            {
                                         continue;
                            }
                            
                            /*se ce un altra coppia assegna full*/
                            else if(freq_num[num[conf]] == 2)
                            {
                                 /*assegna full*/
                                 printf("Full di %s e %s", n[num[carta]], n[num[conf]]);
                                 return 6;
                            }
                   }
                   
                   /*assegna tris*/
                   printf("Tris di %s", n[num[carta]]);
                   return 4;
              }
              
              /*scale*/
              else if(freq_num[num[0]] == 1 && freq_num[num[1]] == 1 && freq_num[num[2]] == 1 && freq_num[num[3]] == 1 && freq_num[num[4]] == 1)
              {
                     /*ordina la mano dalla piu piccola alla piu grande*/
                     ord_mano(num, seme, cop_num, val);
                   
                    /*Determinare se le carte siano in serie*/
                    /*se sono in serie assegna scala*/
                   if(num[1] == num[0] + 1 && num[2] == num[0] + 2 && num[3] == num[0] + 3 && num[4] == num[0] + 4)
                   {
                                 /*scala a colore o scala reale*/
                                 if(freq_seme[seme[0]] == 5 || freq_seme[seme[1]] == 5 || freq_seme[seme[2]] == 5 || freq_seme[seme[3]] == 5 || freq_seme[seme[4]] == 5)
                                 {
                                                       
                                         /*scala reale*/
                                         if(num[1] + num[2] + num[3] + num[4] + num[0] == 55)
                                         {
                                                         /*assegna scala reale*/
                                                         printf("Scala reale");
                                                         return 10;
                                         }
                                         
                                         /*scala colore*/
                                         else
                                         {
                                             /*assegna scala acolore*/
                                             printf("Scala a colore");
                                             return 9;
                                         }
                                 }
                                               
                                 /*scala*/
                                 else
                                 {
                                          /*assegna scala*/
                                           printf("Scala a %s", n[num[4]]);
                                           return 5;
                                 }
                   }
                   
                   /*altrimenti verifica se ce il colore*/
                   else if(freq_seme[seme[0]] == freq_seme[seme[1]] && freq_seme[seme[0]] == freq_seme[seme[2]] &&  freq_seme[seme[0]] == freq_seme[seme[3]] && freq_seme[seme[0]] == freq_seme[seme[4]])
                   {
                                         printf("Colore di %s", s[seme[0]]);
                                         return 7;
                   }
                   
                   /*altrimenti carta alta*/
                   else
                   {
                       printf("Carta alta a %s", n[num[4]]);
                       return 1;
                   }
              }   
              
              /*poker*/
              else if(freq_num[num[carta]] == 4)
              {
                   printf("Poker");
                   return 8;
              }
    } 
}

/*ordina la mano del giocatore dalla piu piccola alla piu grande*/
void ord_mano(int numero[], int sem[], int copia_num[], int valore[])
{
                  int conf, pass, tempn, temps;
      
                  /*ordinare le 5 carte dalla piu piccola alla piu grande e verificare
                     se siano in serie*/
                   for(pass = 1; pass < 5; pass++)
                   {
                            for(conf = 0; conf < 5 - pass; conf++)
                            {
                                     /*ordinamento a bolle*/
                                     if(numero[conf] > numero[conf + 1])
                                     {
                                                      tempn = numero[conf];
                                                      temps = sem[conf];
                                                      numero[conf] = numero[conf + 1];
                                                      numero[conf + 1] = tempn;
                                                      sem[conf] = sem[conf + 1];
                                                      sem[conf + 1] = temps;
                                     }
                            }
                   }
                   
                   /*assegna valore massimo all'asso cioe 14*/
                   if(numero[0] == 0)
                   {
                                 numero[0] = 13;
                                 
                                 /*se ce scala bassa vale 1*/
                                 if(copia_num[1] + copia_num[2] + copia_num[3] + copia_num[4] == 10)
                                 {
                                                 /*l'asso vale 1*/
                                                 numero[0] = 0;
                                 }
                   }
                   
                   /*riordina il vettore mano per far passare l'asso come carta piu alta*/
                   for(pass = 1; pass < 5; pass++)
                   {
                            for(conf = 0; conf < 5 - pass; conf++)
                            {
                                     /*ordinamento a bolle*/
                                     if(numero[conf] > numero[conf + 1])
                                     {
                                                      tempn = numero[conf];
                                                      temps = sem[conf];
                                                      numero[conf] = numero[conf + 1];
                                                      numero[conf + 1] = tempn;
                                                      sem[conf] = sem[conf + 1];
                                                      sem[conf + 1] = temps;
                                     }
                            }
                   }
}
    
/*stampa il mazzo nell'ordine creato nella funzione mescolatura*/
void stampa_mazzo(int deck[][13], char *n[], char *s[])
{
     int riga, colonna, carta;
     printf("\n\n\n\t\t\t\tMazzo mescolato:\n\n\n\n");
     for(carta = 1; carta <= 52; carta++)
     {
               for(riga = 0; riga < 4; riga++)
               {
                        for(colonna = 0; colonna < 13; colonna++)
                        {
                                    if(deck[riga][colonna] == carta)
                                    {
                                                           printf("%2d %7s di %7s     ", carta, n[colonna], s[riga]);
                                                           if(carta % 3 == 0)
                                                           {
                                                                    printf("\n\n\n");
                                                           }
                                    }
                        }
               }
     }
} 

/*rivaluta la mano della cpu e determina quali e quante carte sostituire*/
void rivaluta_cpu(int deck[][13], int cpun[], int cpus[], int *carta, int punt, char *n[], char *s[]) 
{
     int c, riga, colonna;
     int freq_num[13] = {0};     /*indica il numero delle uscite dei numeri*/
     int freq_seme[5] = {0};     /*indica il numero delle uscite dei semi*/
     
     /*determina ogni singola carta quante volte sia uscita*/
     for(c = 0; c < 5; c++)
     {
               freq_num[cpun[c]]++;
               freq_seme[cpus[c]]++;
     }
     
     /*se il pc ha una carta alta, sostituisce 4 carte tranne la carta altra*/
     if(punt == 1)
     {
             printf("Il pc sostituisce 4 carte\n");
             printf("Sostituzioni:\n");
             for(c = 0; c < 4; c++)
             {
                   for(riga = 0; riga < 4; riga++)
                   {
                            for(colonna = 0; colonna < 13; colonna++)
                            {
                                        if(deck[riga][colonna] == *carta)
                                        {
                                                               /*assegna alla mano la carte pescata*/
                                                               printf("Carta %d %s di %s ---------> ", c + 1, n[cpun[c]], s[cpus[c]]);
                                                               cpus[c] = riga;
                                                               cpun[c] = colonna;
                                                               printf("%s di %s\n", n[cpun[c]], s[cpus[c]]);
                                        }
                            }
                   }
                   *carta += 1;
             }
     }   
     
     /*se il pc ha una coppia, sostituisci le tre carte che non fanno parte della coppia*/
     else if(punt == 2)
     {
          printf("Il pc sostituisce 3 carte\n");
          printf("Sostituzioni:\n");
          for(c = 0; c <= 4; c++)
          {
                /*verifica se la carta c non fa parte della coppia*/
                if(freq_num[cpun[c]] == 2)
                {
                                     continue;
                } 
                
                /*altrimenti sostituisci la carta corrente con la carta pescata*/
                else
                {
                    for(riga = 0; riga < 4; riga++)
                   {
                            for(colonna = 0; colonna < 13; colonna++)
                            {
                                        if(deck[riga][colonna] == *carta)
                                        {
                                                               /*assegna alla mano la carte pescata*/
                                                               printf("Carta %d %s di %s ---------> ", c + 1, n[cpun[c]], s[cpus[c]]);
                                                               cpus[c] = riga;
                                                               cpun[c] = colonna;
                                                               printf("%s di %s\n", n[cpun[c]], s[cpus[c]]);
                                        }
                            }
                   }
                } 
                *carta += 1;
          }    
     }   
     
     /*se il pc a una doppia coppia, sostituisce la carta non in coppia*/
     else if(punt == 3)
     {
          printf("Il pc sostituisce 1 carta\n");
          printf("Sostituzioni:\n");
          for(c = 0; c <= 4; c++)
          {
                /*verifica se la carta c non fa parte della coppia*/
                if(freq_num[cpun[c]] == 2)
                {
                                     continue;
                } 
                
                /*altrimenti sostituisci la carta corrente con la carta pescata*/
                else
                {
                    for(riga = 0; riga < 4; riga++)
                   {
                            for(colonna = 0; colonna < 13; colonna++)
                            {
                                        if(deck[riga][colonna] == *carta)
                                        {
                                                               /*assegna alla mano la carte pescata*/
                                                               printf("Carta %d %s di %s ---------> ", c + 1, n[cpun[c]], s[cpus[c]]);
                                                               cpus[c] = riga;
                                                               cpun[c] = colonna;
                                                               printf("%s di %s\n", n[cpun[c]], s[cpus[c]]);
                                        }
                            }
                   }
                } 
                *carta += 1;
          }    
     }   
     
     /*se il pc ha un tris, sostituisci le due carte che non c'entrano col tris*/
     else if(punt == 4)
     {
          printf("Il pc sostituisce 2 carte\n");
          printf("Sostituzioni:\n");
          for(c = 0; c <= 4; c++)
          {
                /*verifica se la carta c non fa parte della coppia*/
                if(freq_num[cpun[c]] == 3)
                {
                                     continue;
                } 
                
                /*altrimenti sostituisci la carta corrente con la carta pescata*/
                else
                {
                    for(riga = 0; riga < 4; riga++)
                   {
                            for(colonna = 0; colonna < 13; colonna++)
                            {
                                        if(deck[riga][colonna] == *carta)
                                        {
                                                               /*assegna alla mano la carte pescata*/
                                                               printf("Carta %d %s di %s ---------> ", c + 1, n[cpun[c]], s[cpus[c]]);
                                                               cpus[c] = riga;
                                                               cpun[c] = colonna;
                                                               printf("%s di %s\n", n[cpun[c]], s[cpus[c]]);
                                        }
                            }
                   }
                } 
                *carta += 1;
          }    
     }
}

/*rivaluta la mano del giocatore*/
void rivaluta_gio(int deck[][13], int gnum[], int gseme[], int *carta, char *n[], char *s[])
{
     int cont, scelta, c, riga, colonna;
     printf("\n\n\n\nseleziona quante carte vuoi sostituire: ");
     scanf("%d", &scelta);
     for(cont = 1; cont <= scelta; cont++)
     {
              printf("Seleziona la %d carta: ", cont);
              scanf("%d", &c);
              
              printf("Sostituzione: %s di %s ------------> ", n[gnum[c - 1]], s[gseme[c - 1]]);
              for(riga = 0; riga < 4; riga++)
              {
                            for(colonna = 0; colonna < 13; colonna++)
                            {
                                        if(deck[riga][colonna] == *carta)
                                        {
                                                               gnum[c - 1] = colonna;
                                                               gseme[c - 1] = riga;
                                                               printf("%s di %s\n\n", n[gnum[c - 1]], s[gseme[c - 1]]);
                                        }
                            }
              }
              *carta += 1;
     }
}

/*stampa la mano dei giocatori*/
void stampa_mano(char *n[], char *s[], int gion[], int gios[], int cpun[], int cpus[], int *partita)
{
     int carta;
     printf("\n\n\n\t  *******************\t\t\t    *******************\n\n");
     printf("\t    Mano giocatotre\t      Partita:%d\t\t  Mano CPU\n\n", *partita);
     printf("\t  *******************\t\t\t    *******************\n\n\n\n");
     for(carta = 1; carta <= 5; carta++)
     {
               printf("\t%d  %7s di %7s\t\t\t   %d  %7s di %7s\n\n", carta, n[gion[carta - 1]], s[gios[carta - 1]], carta, n[cpun[carta - 1]], s[cpus[carta - 1]]);
     }
} 
