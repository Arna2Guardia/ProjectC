#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/*
Pour l'exercice vous aurez besoin de generer des entiers aléatoire : rand() renvoit un entier aléatoire.
il s'utilise : rand() % NOMBREMAX + 1 
Pour un entier aléatoire entre 0 et 1 il faut donc faire rand() %2
voir dans la methode main.
*/

// Ecrire la fonction generer(), elle prend en paramètre la grille et renvoie le nombre d'éléments non nuls


int generer(int* tab[9][9]){
    int cpt = 0;
    for(int i = 0; i < 9;i++){
        for(int j = 0; j < 9;j++){
            tab[i][j] = ((i + j*3 +j /3) %9 +1) ;
            if(tab[i][j] != 0){
                cpt++;
            }
        }
    }
    return cpt;
}

void display(int* tab[9][9]){
    for(int i = 0; i < 9;i++){
        for(int j = 0; j < 9;j++){
            printf(" %d ", tab[i][j]);
            if(j%3== 2){
                printf(" | ");
            }
        }
    printf("\n");
    if(i%3==2){
        printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
        }
    }
}
void vider(int* tab[9][9], int nbZeros){
    while(nbZeros > 0){
        int col = rand() % 9;
        int row = rand() % 9;
        if(tab[row][col] != 0){
            tab[row][col] = 0;
        }
        nbZeros--;
    }
}

// Ce lien vous sera utile : https://www.geeksforgeeks.org/pass-2d-array-parameter-c/


/*Écrire une fonction saisir() qui demande à l’utilisateur de saisir au clavier les indices i et j et la valeur v à placer à l’emplacement (i,j).
La fonction doit vérifier la validité des indices et de la valeur.
Si la case n’est pas occupée, la valeur doit être placée dans la grille. remplissage est alors incrémentée*/

void saisir(int* tab[9][9]){
    int row;
    int col;
    int val;
    printf("\nSaisissez une ligne entre 1 et 9\n");
    scanf("%d",&row);
    printf("\nSaisissez une colonne entre 1 et 9\n");
    scanf("%d",&col);
    printf("\nSaisissez une valeur entre 1 et 9\n");
    scanf("%d",&val);
    if(row < 1 || row >9 || col < 1 || col > 9 || val < 1 || val > 9){
        printf("\n Une des valeurs saisies est invalide, veuillez recommencer\n");
        saisir(tab);
    }
    if(tab[row-1][col-1] !=0){
        printf("\nVous ne pouvez pas jouer ici, veuillez recommencer\n");
        saisir(tab);
    } else {
        tab[row-1][col-1] = val;
    }
}


typedef enum{
    HORIZ = 0, VERT = 1
}Sens;

/*
Écrire la fonction verifierLigneColonne() qui prend en paramètre un numéro et un sens (HORIZ ou VERT)
qui vérifie que la ligne ou la colonne (suivant les cas) numéro est bien remplie.
On pourra utiliser un tableau intermédiaire pour vérifier cela. La fonction retournera 1 si tout s’est bien passé, 0 sinon.
 Les constantes HORIZ de valeur 0 et VERT de valeur 1 sont à définir.
*/
int verifierLigneColonne(int* tab[9][9], int num, Sens sens){
    if(sens == 0){
        for(int i = 0; i < 9; i++){
            if(tab[num][i] == 0){
                return 0;
            }
            int* temp = tab[num][i];
            for(int j = i+1; j < 9; j++){
                if(temp == tab[num][j]){
                    return 0;
                }
            }
        }
    } else {
        for(int j = 0; j < 9; j++){
            if(tab[j][num] == 0){
                return 0;
            }
            int *temp = tab[j][num];
            for(int i = j+1; i < 9; i++){
                if(temp == tab[i][num]){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int verifierRegion(int* tab[9][9], int k, int l){
    for(int i = k*3; i < (k*3)+3; i++){
        for(int j = l*3; j < (l*3)+3; j++){
            int* temp = tab[i][j];
            for(int p = i; p < (k*3)+3; p++){
                for(int q = j+1; q < (l*3)+3; q++){
                    if(temp == tab[p][q]){
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
 
//Écrire la fonction verifierGrille() qui renvoie 1 si la grille est correctement remplie et 0 sinon

int verifierGrille(int* tab[9][9]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(!verifierLigneColonne(tab, i, 0)){
                return 0;
            }
            if(!verifierLigneColonne(tab,j, 1)){
                return 0;
            }
        }
    }
    for(int k = 0; k < 3; k++){
        for(int l = 0; l < 3; l++){
            if(!verifierRegion(tab, k,l)){
                return 0;
            }
        }
    }
    return 1;
}

//Écrire le programme principal, en supposant que la seule condition d’arrêt est la réussite du sudoku (ce test ne devra être fait que si nécessaire)

int main(){
    printf("AAAAAAAAAAAAAAAAAHVVVVVVVVVV2`\n");
    int *sudoku[9][9];
    int verif = 1;
    generer(sudoku);
    while(verif == 1){
        printf("on entre dans le while\n");
        int grid = verifierGrille(sudoku);
        printf("resultat de verif grille: %d \n", grid);
        if(grid == 0){
            printf("La grille est mauvaise, on la recrée\n");
            generer(sudoku);
        } else{
            verif = 0;
            printf("on sort du le while\n");
        }
    }
    int nbZero = 20; 
    int coups = nbZero;
    int win = -1; 
    vider(sudoku,nbZero);
    while(coups > 0){
        display(sudoku);
        saisir(sudoku);
        int grid = verifierGrille(sudoku);
        if(grid != 0){
            win = 0;
            break;
        }
        coups--;
        system("cls");
    }
    display(sudoku);
    if(win == 0){
        printf("\nBravo vous avez gagné !\n");
    }else{
        printf("\nVous avez perdu..\n");
    }
    system("pause");
    return 0;
}

// int main(){
//     // Ne pas toucher le code entre les commentaires
//     srand( time( NULL ) );


//     int i, j, k;
//     int solution[9][9];
//     printf("SOLUTION");  
//     printf("\n");  
//     printf("---------------------------------");  
//     printf("\n");  
//     for(j=0;j<9; ++j) 
//     {
//     for(i=0; i<9; ++i)
//         solution[j][i] = (i + j*3 +j /3) %9 +1 ; 
//     }
    
//     for(i=0;i<9; ++i) 
//     {
//     for(j=0; j<9; ++j)
//         printf("%d ", solution[i][j]);
//     printf("\n");  
//     }
//     printf("---------------------------------");  
//     printf("\n");  
//     //toucher le code entre les commentaires 
    
//     printf("%d",rand() % 2);
    
  



//     //Ne pas toucher au code ci dessous
//     system("pause");
//     return 0;
// }

