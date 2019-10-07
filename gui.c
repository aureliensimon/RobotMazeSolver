#include "header.h"

/**
 * Demande les options pour le mode graphique
 *
 * @param   graph : Nom de l'interface
            robot : Robot utilisé
            map   : Carte utilisée
            steps : Nombre d'étapes
 * @return (void)
 */
void graphmode(Graph graph, Robot robot, Map map, int *steps){
    init(&graph, map);

    printf("\nAfficher Passage Du Robot ? (y/n) : ");
    char choix;
    scanf("%c", &choix);
    if(choix == 'y'){
        afficherTraces(&robot, 1);
    }
    int way = solvemaze(robot, map, graph, 'g', steps);
    if(!way){
        printf("Pas de Solution :(\n");
        return;
    }
}

/**
 * Initialiser la SDL
 *
 * @param   graph : Nom de l'interface
            map   : Carte utilisée
 * @return (void)
 */
void init(Graph *graph, Map map){
    Graph newgraph;

    // Init SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1){
        fprintf(stderr, "Erreur d'intit de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // ECRAN
    (*graph).ecran = SDL_SetVideoMode(map.width*MAILLE, map.height*MAILLE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    (*graph).robot = loadImg("img/robot.bmp");
    (*graph).sol = loadImg("img/sol.bmp");
    (*graph).mur = loadImg("img/mur.bmp");
    (*graph).porte = loadImg("img/porte.bmp");
    (*graph).visite = loadImg("img/visite.bmp");
    if((*graph).ecran == NULL){
        fprintf(stderr, "Impossible de charger l'écran : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * Charger une image
 *
 * @param   nom   : Nom de l'image à charger
 * @return  img   : l'image chargée
 */
SDL_Surface *loadImg(char *nom){
  SDL_Surface *img = NULL;
  img = SDL_LoadBMP(nom);
  if(!img){
    printf("Erreur chargement de l'image %s\n", nom);
    exit(0);
  }
  return img;
}

/**
 * Afficher une image
 *
 * @param   img   : Nom de l'image à afficher
 *          graph : Nom de l'interface
 *          x     : Position abscisses
 *          y     : Position ordonnée
 * @return (void)
 */
void printImg(SDL_Surface *img, Graph graph, int x, int y){
  SDL_Rect position;
  position.y = y*MAILLE;
  position.x = x*MAILLE;
  SDL_BlitSurface(img, NULL, graph.ecran, &position);
}

/**
 * Afficher toute la carte
 *
 * @param   graph : Nom de l'interface
 *          map   : Carte utilisée
 *          robot : Robot utilisé
 * @return (void)
 */
void DrawMap(Graph graph, Map map, Robot robot){
    int i, j;
    char name[15];
    SDL_Surface *img;

    for(i = 0; i < map.width; i++){
        for(j = 0; j < map.height; j++){
            if(j == robot.x && i == robot.y){
                printImg(graph.robot, graph, i, j);
            }else if(map.visited[j][i] == '.' && robot.affTrace){
                printImg(graph.visite, graph, i, j);
            }else{
                switch(map.grid[j][i]){
                    case 'x':
                        printImg(graph.mur, graph, i, j);
                        break;
                    case 'S':
                        printImg(graph.porte, graph, i, j);
                        break;
                    default:
                        printImg(graph.sol, graph, i, j);
                        break;
                }
            }
        }
    }
    SDL_Flip(graph.ecran);
    SDL_Delay(REPOS);
}
