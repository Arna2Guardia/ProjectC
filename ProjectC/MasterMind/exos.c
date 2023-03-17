#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void responseGen(int tab[4]){
    for(int i = 0;i < 4; i++){
        tab[i] = 1 + rand() % 6;
    }
}

void afficher(int tab[4]){
    for(int i = 0; i < 4; i++){
        printf("%d ,",tab[i]);
    }
}

void afficherLettres(int tab[4], char tab2[4]){
    for(int i = 0; i < 4; i++){
        if(tab[i] == 1){
            tab2[i] = 'P';
        }
        if(tab[i] == 2){
            tab2[i] = 'B';
        }
        if(tab[i] == 3){
            tab2[i] = 'M';
        }
        if(tab[i] == 4){
            tab2[i] = 'Y';
        }
        if(tab[i] == 5){
            tab2[i] = 'O';
        }
        if(tab[i] == 6){
            tab2[i] = 'G';
        }
    }
    printf(" | ");
    for(int i = 0; i < 4; i++){
        printf("%c ",tab2[i]);
    }
}

void saisirTab(int tab[4]){
    int val1,val2,val3,val4 = 0;
    int verif = 1;
    while(verif == 1){
        printf("\nChoisissez 4 valeurs entre 1 et 6:\n");
        scanf("%d %d %d %d",&val1,&val2,&val3,&val4);
        if(!(val1 < 1 || val1 > 6 || val2 < 1 || val2 > 6 || val3 < 1 || val3 > 6 || val4 < 1 || val4 > 6)){
            verif = 0;
        }
    }
    int tabVal[4] = {val1,val2,val3,val4};
    for(int i = 0; i < 4; i++){
        tab[i] = tabVal[i];
    }
}

int vrai(int tab[4],int tab2[4]){
    int cpt = 0;
    for(int pos = 0; pos < 4 ; pos++){
        if(tab[pos] == tab2[pos]){
            cpt++;
        }
    }
    return cpt;
}

int vraiMaisPasTrop(int tab[4], int tab2[4]) {
    bool matched[4] = { false };
    for(int pos = 0; pos < 4 ; pos++){
        if(tab[pos] == tab2[pos]){
            matched[pos] = true;
        }
    }
    int cpt = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            if (i != j && tab[i] == tab2[j] && !matched[j]) {
                cpt++;
                matched[j] = true;
                break;
            }
        }
    }
    return cpt;
}


void rangementTator(int tab[4], int nb){
    int verif = 1;
    do {
        int num = rand()%4;
        if(tab[num] == -1){
            tab[num] = nb;
            verif = 0;
        }
    } while(verif);
}

void validator(int tab[4], int tab2[4]){
    char tabChar[4];
    char superTab[4];
    for(int i = 0; i < 4; i++){
        if(tab2[i] == 0){
            superTab[i] = '.';
        }
        if(tab2[i] == 1){
            superTab[i] = 'W';
        }
        if(tab2[i] == 2){
            superTab[i] = 'R';
        }
    }
    printf(" |         | %c  %c |\n", superTab[0],superTab[1]);
    afficherLettres(tab,tabChar);
    printf("| %c  %c |\n", superTab[2],superTab[3]);
}




int main(){
    srand( time( NULL ) );
    int tab[4] = {0,0,0,0};
    responseGen(tab);
    //afficher(tab);
    printf("\n");
    int coups = 10;
    while(coups > 0){
        int tabSaisie[4] = {0};
        saisirTab(tabSaisie);
        int rangement[4] = {-1,-1,-1,-1};
        int reel = vrai(tab,tabSaisie);
        int bof = vraiMaisPasTrop(tab,tabSaisie);
        int faux = 0;
        int remplissage = 4;
        if(reel >= bof){
            faux = 4 - reel - bof;
        } else {
            faux = 4 - bof - reel;
        }
        //printf("\n reel = %d \n bof = %d \n faux = %d",reel,bof,faux);
        if(reel > 0 && remplissage > 0){
            for(int i = 0; i < reel; i++){
                rangementTator(rangement,2);
                remplissage--;
            }
        }
        if(bof > 0 && remplissage > 0){
            for(int i = 0; i < bof; i++){
                rangementTator(rangement,1);
                remplissage--;
            }
        }
        if(faux > 0 && remplissage > 0){
            for(int i = 0; i < faux; i++){
                rangementTator(rangement,0);
            }
        }
        
        printf("\n | - - - - | #  # |\n");
        validator(tabSaisie,rangement);
        if(reel == 4){
            break;
        }
        coups--;
    }
    if(coups > 0){
        printf("\nVous etes le Master Mind !\n\n");
    } else {
        printf("\nVous avez perdu.. dommage\n La reponse etait:\n");
        afficher(tab);
    }
    system("pause");
    return 1;
}