#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* je vais essayer de m'aider de ca pour afficher mon laby
___________________________________
| _____ |   | ___ | ___ ___ | |   | |
| |   | |_| |__ | |_| __|____ | | | |
| | | |_________|__ |______ |___|_| |
| |_|   | _______ |______ |   | ____|
| ___ | |____ | |______ | |_| |____ |
|___|_|____ | |   ___ | |________ | |
|   ________| | |__ | |______ | | | |
| | | ________| | __|____ | | | __| |
|_| |__ |   | __|__ | ____| | |_| __|
|   ____| | |____ | |__ |   |__ |__ |
| |_______|_______|___|___|___|_____|

idée
1L : _________
derL : _________
1C :   |__ ___ |
derC : | | | | |
       |___|____
*/

/// Variable modifiable

#define tailleLab 5

/// Structure

struct Case {
    int nord;
    int sud;
    int ouest;
    int est;
//0 = mur , 1 = pas mur
    int nombre;
};
typedef struct Case Case;

void afficheLab(Case **l);

Case **initTab() {
    Case **lab = (Case **) malloc(tailleLab * sizeof(Case *));
    for (int i = 0; i < tailleLab; ++i) {
        lab[i] = (Case *) malloc(tailleLab * sizeof(Case));
    }
    for (int i = 0; i < tailleLab; i++)
        for (int j = 0; j < tailleLab; j++) {
            lab[i][j].nombre = i * tailleLab + j;
            lab[i][j].nord = 0;
            lab[i][j].sud = 0;
            lab[i][j].ouest = 0;
            lab[i][j].est = 0;
        }
    return lab;
}

int checkStop(Case **lab) { // 0 stop l'alea, 1 continue l'alea
    for (int i = 0; i < tailleLab; i++)
        for (int j = 0; j < tailleLab; j++)
            if (lab[0][0].nombre != lab[i][j].nombre)
                return 1;
    return 0;
}


void afficheLab(Case **lab) {
    for (int i = 0; i < tailleLab; i++) {
        printf("_");
    }
    printf("\n");
    for (int i = 0; i < tailleLab; i++) {
        for (int j = 0; j < tailleLab; j++) {
            if (lab[i][j].ouest == 1) {
                printf("|");
            }else{
              printf(" ");
            }
            if (lab[i][j].nord == 1) {
                printf("_");
            }else{
              printf(" ");
            }
            if (i == tailleLab - 1) {
                if (lab[i][j].est == 1) {
                    printf("|");
                }else{
                  printf(" ");
                }
            }
        }
        printf("\n");
    }
    for (int i = 0; i < tailleLab; i++) {
        printf("_");
    }
}

Case **entreeSortie(Case **lab) {
    int ent = rand() % tailleLab;
    lab[ent][0].ouest = 1;

    int sort1 = rand() % tailleLab;
    int sort2 = rand() % tailleLab;
    while (sort1 == sort2) {
        sort2 = rand() % tailleLab;
    }
    lab[sort1][tailleLab - 1].est = 1;
    lab[sort2][tailleLab - 1].est = 1;
    return lab;
}

void updateLab(Case **lab) {
    int var = 0;
    for (int i = 0; i < tailleLab; i++) {
        for (int j = 0; j < tailleLab; j++) {
            if ((lab[i][j].nord == 1) && (lab[i + 1][j].sud == 0)) {
                lab[i + 1][j].sud = 1;
                var = lab[i + 1][j].nombre;
                for (int y = 0; y < tailleLab; y++) {
                    for (int x = 0; x < tailleLab; x++) {
                        if (lab[y][x].nombre == var) {
                            lab[y][x].nombre = lab[i][j].nombre;
                        }
                    }
                }
            }
            if ((lab[i][j].sud == 1) && (lab[i - 1][j].nord == 0)) {
                lab[i - 1][j].nord = 1;
                var = lab[i][j].nombre;
                for (int y = 0; y < tailleLab; y++) {
                    for (int x = 0; x < tailleLab; x++) {
                        if (lab[y][x].nombre == var) {
                            lab[y][x].nombre = lab[i - 1][j].nombre;
                        }
                    }
                }
            }
            if ((lab[i][j].ouest == 1) && (lab[i][j - 1].est == 0)) {
                lab[i][j - 1].est = 1;
                var = lab[i][j].nombre;
                for (int y = 0; y < tailleLab; y++) {
                    for (int x = 0; x < tailleLab; x++) {
                        if (lab[y][x].nombre == var) {
                            lab[y][x].nombre = lab[i][j - 1].nombre;
                        }
                    }
                }
            }
            if ((lab[i][j].est == 1) && (lab[i][j + 1].ouest == 0)) {
                lab[i][j + 1].ouest = 1;
                var = lab[i][j + 1].nombre;
                for (int y = 0; y < tailleLab; y++) {
                    for (int x = 0; x < tailleLab; x++) {
                        if (lab[y][x].nombre == var) {
                            lab[y][x].nombre = lab[i][j].nombre;
                        }
                    }
                }
            }
        }
    }
}


Case **ouvAlea(Case **lab) {
    srand(time(NULL));
    int y = 0;
    int x = 0;
    int cpt = 0;

    printf("zzzzzzzz\n");
    afficheLab(lab);
    int *xUtil = (int *) malloc(tailleLab * sizeof(int));
    int *yUtil = (int *) malloc(tailleLab * sizeof(int));
    for (int i = 0; i < tailleLab; i++)
        xUtil[i] = yUtil[i] = -1;

    printf("zzzzzzzz\n");
    while (checkStop(lab) == 1) {

        int x = rand() % tailleLab;
        int y = rand() % tailleLab;

        for (int i = 0; (i < tailleLab) || (xUtil[i] == -1); i++) {
            while ((x == xUtil[i]) && (y == xUtil[i])) { // check si le x et y ont pas deja été sélectioné
                x = rand() % tailleLab;
                y = rand() % tailleLab;
                i = 0;
            }
        }

        xUtil[cpt] = x;
        yUtil[cpt] = y;
        cpt++;

        int ouverture = rand() % 3; // 0 nord, 1 sud, 2 ouest, 3 est
        if ((y == 0) && (x == 0)) {
            while ((ouverture == 0) || (ouverture == 2)) {
                ouverture = rand() % 3;
            }
        } else if ((y == 0) && (x == tailleLab)) {
            while ((ouverture == 0) || (ouverture == 3)) {
                ouverture = rand() % 3;
            }
        } else if ((y == tailleLab) && (x == 0)) {
            while ((ouverture == 1) || (ouverture == 2)) {
                ouverture = rand() % 3;
            }
        } else if ((y == tailleLab) && (x == tailleLab)) {
            while ((ouverture == 1) || (ouverture == 3)) {
                ouverture = rand() % 3;
            }
        } else if (y == 0) {
            while ((ouverture == 0)) {
                ouverture = rand() % 3;
            }
        } else if (y == tailleLab) {
            while ((ouverture == 1)) {
                ouverture = rand() % 3;
            }
        } else if (x == 0) {
            while ((ouverture == 2)) {
                ouverture = rand() % 3;
            }
        } else if (x == tailleLab) {
            while ((ouverture == 3)) {
                ouverture = rand() % 3;
            }
        }

        //ouverture
        if (ouverture == 0) {
            lab[y][x].nord = 1;
        } else if (ouverture == 1) {
            lab[y][x].sud = 1;
        } else if (ouverture == 2) {
            lab[y][x].ouest = 1;
        } else {
            lab[y][x].est = 1;
        }
        afficheLab(lab);
        updateLab(lab);
    }


    return lab;
}

int main() {
    afficheLab(entreeSortie(ouvAlea(initTab())));
    return 0;
}
