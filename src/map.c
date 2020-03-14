#include "../include/header.h"

/**
 * Ouvrir un fichier
 *
 * @param   namefile : Nom du fichier à ouvrir
 * @return  file     : Fichier ouvert
 */
FILE *openfile(char *namefile){
    FILE *file = fopen(namefile, "r");
    if(!file){
        printf("Erreur : '%s' n'est pas un nom de fichier valide\n", namefile);
        exit(0);
    }
    return file;
}

/**
 * Créer la carte
 *
 * @param   namefile : Nom du fichier à ouvrir
 * @return  map      : Carte utilisée
 */
Map getmap(char *namefile){
    Map map;
    FILE *file = NULL;
    int width, height, i, j;
    char ligne[MAX_CHAR];
    char *ptr;
    char **grid;
    int **grid_visited;

    file = openfile(namefile);

    // Get width / height
    fscanf(file, "%d:%d", &width, &height);

    fgets(ligne , MAX_CHAR , file); // Avale ligne width:height
    grid = malloc(height * sizeof(char *));
    grid_visited = malloc(height * sizeof(int *));
    for(i = 0; i < height; i++){
        grid[i] = malloc(width * sizeof(char));
        grid_visited[i] = malloc(width * sizeof(int));
        fgets(ligne , MAX_CHAR , file);
        for(j = 0; j < width; j++){
            if(ligne[j] == 'D'){
                map.start.x = i;
                map.start.y = j;
            }else if(ligne[j] == 'S'){
                map.end.x = i;
                map.end.y = j;
            }
            grid[i][j] = ligne[j];
        }
    }

    map.grid = grid;
    map.visited = grid_visited;
    map.width = width;
    map.height = height;

    fclose(file);
    return map;
}

/**
 * Afficher le menu textuel
 *
 * @param   filename : Nom du fichier à ouvrir
 *          robot    : Robot utilisé
 * @return  (void)
 */
void printmenu(char *filename, Robot *robot){
    char choix;

    printf("\e[1;1H\e[2J");
    printf(
    "\n\t  ___   _  _____  _  _  ___  ___  _  _  ___  ___  _  _   ___\n"
    "\t | _ \\ /_\\|_   _|| || || __||_ _|| \\| ||   \\|_ _|| \\| | / __|\n"
    "\t |  _// _ \\ | |  | __ || _|  | | | .` || |) || | | .` || (_ |\n"
    "\t |_| /_/ \\_\\|_|  |_||_||_|  |___||_|\\_||___/|___||_|\\_| \\___|\n"
    "\n________________________________________________________________________________\n"
    );

    printf("\nFichier Sélectionné : %s\n", filename);
    printf("\nAfficher Passage Du Robot ? (y/n) : ");
    scanf("%c", &choix);
    if(choix == 'y'){
        afficherTraces(robot, 1);
    }
}

/**
 * Afficher traces du robot
 *
 * @param   robot : Robot utilisé
 *          aff   : Booléen si afficher ou non les traces
 * @return  (void)
 */
void afficherTraces(Robot *robot, int aff){
    (*robot).affTrace = aff;
}

/**
 * Afficher la carte
 *
 * @param   map   : Carte utilisée
 *          robot : Robot utilisé
 *          steps : Nombre d'étapes
 * @return  (void)
 */
void printpath(Map map, Robot robot, int steps){

    char nomdir[6];
    usleep(20000);
    printf("\e[1;1H\e[2J");
    printf(
    "\n\t  ___   _  _____  _  _  ___  ___  _  _  ___  ___  _  _   ___\n"
    "\t | _ \\ /_\\|_   _|| || || __||_ _|| \\| ||   \\|_ _|| \\| | / __|\n"
    "\t |  _// _ \\ | |  | __ || _|  | | | .` || |) || | | .` || (_ |\n"
    "\t |_| /_/ \\_\\|_|  |_||_||_|  |___||_|\\_||___/|___||_|\\_| \\___|\n"
    "\n________________________________________________________________________________\n"
    );
    for(int i = 0; i < map.height; i++){
        printf("\n\t\t");
        for(int j = 0; j < map.width; j++){
            if(i == robot.x && j == robot.y){
                switch(robot.direction){
                    case NORTH:
                        printf("^");
                        strcpy(nomdir, "\u2191");
                        break;
                    case SOUTH:
                        printf("v");
                        strcpy(nomdir, "\u2193");
                        break;
                    case WEST:
                        printf("<");
                        strcpy(nomdir, "\u2190");
                        break;
                    case EAST:
                        printf(">");
                        strcpy(nomdir, "\u2192");
                        break;
                }
            }else{
                if(robot.affTrace && map.visited[i][j] == '.'){
                    printf("%c", map.visited[i][j]);
                }else{
                    if(map.grid[i][j] != 'D'){
                        printf("%c", map.grid[i][j]);
                    }else{
                        printf(" ");
                    }
                }
            }
        }

    }
    printf("\n\t\t _________________________________________________\n"
    "\t\t|\t\tPANNEAU DE CONTROLE\t\t  |"
    "\n\t\t|_________________________________________________|"
    "\n\t\t|     POSITION DU ROBOT    |                      |"
    "\n\t\t|       x  : %4d          |                      |"
    "\n\t\t|       y  : %4d          |   ETAPE N° : %5d   |"
    "\n\t\t|      dir :    %s          |                      |"
    "\n\t\t|__________________________|______________________|\n\n"
    , robot.y, robot.x, steps, nomdir
    );
}

/**
 * Libérer la mémoire
 *
 * @param   map   : Carte utilisée
 * @return  (void)
 */
void freeall(Map map){
    int i;
    for(i = 0; i < map.height; i++){
        free(map.grid[i]);
        free(map.visited[i]);
    }
    free(map.grid);
    free(map.visited);
}
