#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define MAX_CHAR 1000
#define NORTH 0
#define SOUTH 180
#define WEST 90
#define EAST 270
#define MAILLE 20
#define REPOS 10


typedef struct {
    SDL_Surface *ecran;
    SDL_Surface *sol;
    SDL_Surface *robot;
    SDL_Surface *mur;
    SDL_Surface *porte;
    SDL_Surface *visite;
    SDL_Event event;
} Graph;

typedef struct {
    int x;
    int y;
    int direction;
    int affTrace;
} Robot;

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    char **grid;
    int **visited;
    int width;
    int height;
    Point start;
    Point end;
} Map;

// Fonctions pour le Robot
void initRobot(Robot *, Map);
int nextIsWall(Map, int, int, int);
void moveRobot(Robot *, Map *);
int EndReach(Map, int, int);
void turnRobotLeft(Robot *);
void turnRobotRight(Robot *);
void GoToFirstWall(Robot *, Map);
int solvemaze(Robot, Map, Graph, char, int *);
void rotatestart(Robot *, Map);

// Fonctions pour la Carte
FILE *openfile(char *);
Map getmap(char *);
void printpath(Map, Robot, int);
void printmenu(char *, Robot *);
void afficherTraces(Robot *, int);
void freeall(Map);

// Fonctions pour l'interface graphique
void graphmode(Graph, Robot, Map, int *);
void init(Graph *, Map);
SDL_Surface *loadImg(char *);
void DrawMap(Graph, Map, Robot);
void printImg(SDL_Surface *, Graph, int, int);
