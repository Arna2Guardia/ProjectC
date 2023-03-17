#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// 1 - creer une fonction qui prend la variable solution, et la variable tableauJoueur (par exemple) : un tableau rempli de 0, cette fonction doit copier certaines valeurs (grace au rand() % N) 
// de solution dans tableauJoueur afin d'initialiser une grille jouable ( car solution est bel est bien la solution, donc pas jouable par définition. ).
// un parametre doit permettre de verifier la condition de victoire en un seul coup (proposer votre façon de faire :) ) 


void display(int tab[8][8]){
    for(int i = 0; i < 8;i++){
        printf(" | ");
        for(int j = 0; j < 8;j++){
            printf(" %d ", tab[i][j]);
            
        }
        printf(" | \n");
    }
}

void generator(int tab[8][8],int tabJoueur[8][8],int coups){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j< 8; j++){
            tabJoueur[i][j] = tab[i][j];
        }
    }
    while(coups > 0 ){
        int row = rand() % 8;
        int col = rand() % 8;
        if(tabJoueur[row][col] != 9){
            tabJoueur[row][col] = 9;
        }
        coups--;
    }
}


// 2- une fonction saisir qui demande au joueur de saisir 3 informations: i, j , et v qui permettront de placer la valeur v aux coordonnées (i,j)

void saisir(int tab[8][8]){
    int row;
    int col;
    int val;
    printf("\nSaisissez une ligne entre 1 et 8\n");
    scanf("%d",&row);
    printf("\nSaisissez une colonne entre 1 et 8\n");
    scanf("%d",&col);
    printf("\nSaisissez une valeur entre 0 et 1\n");
    scanf("%d",&val);
    if(row < 1 || row >9 || col < 1 || col > 9 || val < 0 || val > 1){
        printf("\n Une des valeurs saisies est invalide, veuillez recommencer\n");
        saisir(tab);
    }
    if(tab[row-1][col-1] !=9){
        printf("\nVous ne pouvez pas jouer ici, veuillez recommencer\n");
        saisir(tab);
    } else {
        tab[row-1][col-1] = val;
    }
}


// 3- apres chaque coordonnées il faut verifier les regles du sudoku sur le tableauJoueur donc : 

int verifierLigneColonne(int tab[8][8],int pos, int sens){

    if(sens == 0){
        int cpt1 = 0;
        int cpt0 = 0;
        //printf("\n On verifie en vertical");
        int cptVoisin = -1; 

        for(int i  = 0; i < 8; i++){
            if(tab[i][pos] == 1){
                cpt1++;
                if(tab[i-1][pos] && tab[i-1][pos] == 1){
                    cptVoisin++;
                    //printf("\ncpt voisin =%d\n", cptVoisin);
                    if(cptVoisin > 1){
                        return 0;
                    }
                } else if(tab[i-1][pos] && tab[i-1][pos] == 0){
                    //printf("\ncpt voisin =%d\n", cptVoisin);
                    cptVoisin = 0;
                }
            }
            if(tab[i][pos] == 0){
                cpt0++;
            }
            if(tab[i-1][pos] && tab[i-1][pos] == 0){
                //printf("\ncpt voisin =%d\n", cptVoisin);
                    cptVoisin++;
                    if(cptVoisin > 1){
                        return 0;
                    }
            } else if(tab[i-1][pos] && tab[i-1][pos] == 1){
                cptVoisin = 0;
            }

        }
        if(cpt0 == cpt1){
            return 1;
        }
    }
    if(sens == 1){
        //printf("\n On verifie en horizontal");
        int cptVoisin = 0; 
        int cpt1 = 0;
        int cpt0 = 0;
        for(int i  = 0; i < 8; i++){
            if(tab[pos][i] == 1){
                cpt1++;
                if(tab[pos][i-1] && tab[pos][i-1] == 1){
                    cptVoisin++;
                    if(cptVoisin > 1){
                        return 0;
                    }
                } else if(tab[pos][i-1] && tab[pos][i-1] == 0){
                    cptVoisin = 0;
                }
            }
            if(tab[pos][i] == 0){
                cpt0++;
            }
            if(tab[pos][i-1] && tab[pos][i-1] == 0){
                    cptVoisin++;
                    if(cptVoisin > 1){
                        return 0;
                    }
            } else if(tab[pos][i-1] && tab[pos][i-1] == 1){
                cptVoisin = 0;
            }
        }
        if(cpt0 == cpt1){
            return 1;
        }
    }

    return 0;  
}


    // - la fonction verifierLigneColonne ( qui verifie les lignes et les colonnes  sur lesquelles sont la nouvelle valeur)
int verifDoublon(int tab[8][8],int pos, int sens){
    int cpt = 0;
    if(sens == 1){
        //printf("\n On verifie en horizontal");

        int verif[8] ={-1,-1,-1,-1, -1,-1,-1,-1};
        for(int i = 0; i < 8; i++){
            verif[i] = tab[pos][i];
        }
        for(int i = 0; i < 8; i++){
            if(i != pos){
                //printf("\n i :",verif[i]);
                int cpt2 = 0;
                //printf("\n cpt = %d",cpt);
                //printf("\n cpt2 = %d",cpt2);
                for(int j = 0; j < 8; j++){
                    //printf("\n j :",j);
                    if(verif[j] != tab[i][j]){
                        cpt2++;
                        //printf("\nOn fait +1 a cpt2: %d\n",cpt2);
                        break;
                    }
                }
                if(cpt2 > 0){
                    //printf("\n On fait +1 a cpt");
                    cpt++;
                    if(cpt == 7){
                        break;
                    }
                }
            }
        }
        if(cpt == 7){
            //printf("\n cpt = %d",cpt);
            return 1;
        }
    }
    if(sens == 0){
        //printf("\n On verifie en vertical");

        int verif[8] ={-1,-1,-1,-1, -1,-1,-1,-1};
        for(int i = 0; i < 8; i++){
            verif[i] = tab[i][pos];
        }
        for(int i = 0; i < 8; i++){
            if(i != pos){
                //printf("\n cpt = %d",cpt);
                int cpt2 = 0;
                for(int j = 0; j < 8; j++){
                    if(verif[j] != tab[j][i]){
                        cpt2++;
                        break;
                    }
                }
                if(cpt2 > 0){
                    //printf("\n On fait +1 a cpt");
                    cpt++;
                    if(cpt == 7){
                        break;
                    }
                }
            }
        }
        if(cpt == 7){
            //printf("\n cpt = %d",cpt);
            return 1;
        }
    }
    return 0;
}

    // - la fonction verifierGrille (qui fait ceci pour toute la grille et permet de definir la condition de victoire)

int verifierGrille(int tab[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            //printf("Verif col: %d     Verif Ligne: %d    Verif doublonCol:   %d   Verif doublonLigne:    %d",verifierLigneColonne(tab, i, 0), verifierLigneColonne(tab,j, 1),verifDoublon(tab,i,0),verifDoublon(tab,j,1));
            if(!verifierLigneColonne(tab, i, 0) || !verifierLigneColonne(tab,j, 1) || !verifDoublon(tab,i,0) || !verifDoublon(tab,j,1)){
                return 0;
            }
        }
    }
    return 1;
}

// 4 - Ecrire le code principal qui permet de jouer au joueur :  le programme prend fin quand on gagne 

int main(){
    // Ne pas toucher le code entre les commentaires
    srand( time( NULL ) );


    int i, j, k;
    printf("SOLUTION");  
    printf("\n");  
    printf("---------------------------------");  
    printf("\n");  

    int solution[8][8] = {
        {1,1,0,1, 0,1,0,0},
        {0,0,1,0, 1,0,1,1},
        {0,1,0,0, 1,1,0,1},
        {1,0,1,1, 0,0,1,0},
    
        {1,0,1,0, 0,1,1,0},
        {0,1,0,1, 1,0,0,1},
        {1,1,0,0, 1,0,1,0},
        {0,0,1,1, 0,1,0,1}
    };
    // int solution[8][8] = {
    //     {1,1,0,1, 0,1,0,0},
    //     {0,0,1,0, 1,0,1,1},
    //     {1,1,0,0, 1,1,0,1},
    //     {0,0,1,1, 0,0,1,0},
    
    //     {0,0,1,0, 0,1,1,0},
    //     {1,1,0,1, 1,0,0,1},
    //     {1,1,0,0, 1,0,1,0},
    //     {0,0,1,1, 0,1,0,1}
    // };


    for(i=0;i<8; ++i) 
    {
    for(j=0; j<8; ++j)
        printf("%d ", solution[i][j]);
    printf("\n");  
    }
    printf("---------------------------------");  
    printf("\n");  
    //toucher le code entre les commentaires 
    int tabJoueur[8][8] = {
        {9,9,9,9, 9,9,9,9},
        {9,9,9,9, 9,9,9,9},
        {9,9,9,9, 9,9,9,9},
        {9,9,9,9, 9,9,9,9},
    
        {9,9,9,9, 9,9,9,9},
        {9,9,9,9, 9,9,9,9},
        {9,9,9,9, 9,9,9,9},
        {9,9,9,9, 9,9,9,9}
    };
    int coups = 10;
    int win = -1;
    generator(solution,tabJoueur,coups);
    while(coups > 0){
        display(tabJoueur);
        saisir(tabJoueur);
        int grid = verifierGrille(tabJoueur);
        if(grid != 0){
            win = 0;
            break;
        }
        //printf("\n La grille est bonne ou pas: %d",verifierGrille(solution));
        coups--;
    }
    display(tabJoueur);
    if(win == 0){
        printf("\nBravo vous avez gagné !\n");
    }else{
        printf("\nVous avez perdu..\n");
    }



    //Ne pas toucher au code ci dessous
    system("pause");
    return 0;
}
