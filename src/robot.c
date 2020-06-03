#include "../include/header.h"

/**
 * Initialiser le robot
 *
 * @param   robot : Robot utilisé
 *          map   : Carte utilisée
 * @return (void)
 */
void initRobot(Robot *robot, Map map){
    (*robot).x = map.start.x;
    (*robot).y = map.start.y;
    (*robot).direction = NORTH;
    (*robot).affTrace = 0;
}

/**
 * Savoir si la sortie est sur les côtés du robot
 *
 * @param   map      : Carte utilisée
            x        : Position en abscisse
            y        : Position en ordonnée
 * @return  endreach :  Booléen si la sortie est proche ou non
 */
int EndReach(Map map, int x, int y){
    return (map.grid[x+1][y] == 'S' || map.grid[x-1][y] == 'S' || map.grid[x][y+1] == 'S' || map.grid[x][y-1] == 'S');
}

/**
 * Savoir s'il y a un mur devant le robot
 *
 * @param   map : Carte utilisée
            x   : Position en abscisse
            y   : Position en ordonnée
            dir : Direction du robot
 * @return  int : Booléen s'il y a un mur devant le robot
 */
int nextIsWall(Map map, int x, int y, int dir){
    switch(dir){
        case NORTH:
            x--;
            break;
        case SOUTH:
            x++;
            break;
        case WEST:
            y--;
            break;
        case EAST:
            y++;
            break;
    }
    
    return (map.grid[x][y] == 'x' || map.visited[x][y] == '.');
}

/**
 * Tourner le robot à gauche
 *
 * @param   robot : Robot utilisé
 * @return  (void)
 */
void turnRobotLeft(Robot *robot){
    (*robot).direction =  ((*robot).direction + WEST) % 360;
}

/**
 * Tourner le robot à droite
 *
 * @param   robot : Robot utilisé
 * @return  (void)
 */
void turnRobotRight(Robot *robot){
    (*robot).direction =  ((*robot).direction + EAST) % 360;
}

/**
 * Déplacer le robot
 *
 * @param   robot : Robot utilisé
 *          map   : Map utilisée
 * @return  (void)
 */
void moveRobot(Robot *robot, Map *map){
    // Mark
    (*map).visited[(*robot).x][(*robot).y] = '.';
    if(!nextIsWall(*map, (*robot).x, (*robot).y, (*robot).direction)){
        switch((*robot).direction){
            case NORTH:
                (*robot).x--;
                break;
            case SOUTH:
                (*robot).x++;
                break;
            case WEST:
                (*robot).y--;
                break;
            case EAST:
                (*robot).y++;
                break;
        }
    }
}

/**
 * Allez tout droit jusqu'au prochain mur
 *
 * @param   robot : Robot utilisé
 *          map   : Map utilisée
 * @return  (void)
 */
void GoToFirstWall(Robot *robot, Map map){
    while(!nextIsWall(map, (*robot).x, (*robot).y, (*robot).direction)){
        moveRobot(robot, &map);
    }
    return;
}

/**
 * Tourner le robot tant qu'il a un robot devant lui
 *
 * @param   robot : Robot utilisé
 *          map   : Map utilisée
 * @return  (void)
 */
void rotatestart(Robot *robot, Map map){
    while(nextIsWall(map, (*robot).x, (*robot).y, (*robot).direction)){
        turnRobotLeft(robot);
    }
}

/**
 * Trouver la sortie de l'appartement
 *
 * @param   robot : Robot utilisé
 *          map   : Map utilisée
 *          graph : Interface utilisée
 *          mode  : Mode textuel ou Graphique
 *          steps : Nombre d'étapes
 * @return  int   : Booléen s'il existe un passage
 */
int solvemaze(Robot robot, Map map, Graph graph, char mode, int *steps){

    int way;
    (*steps)++;

    // Affichage selon le mode
    if(mode == 't'){
        printpath(map,robot, *steps);
    }else{
        DrawMap(graph, map, robot);
        while(SDL_PollEvent(&graph.event)){
            switch(graph.event.type){
                case SDL_QUIT:
                    exit(0);
                    break;
            }
        }
    }

    // Check si la fin est sur les côtés du robot
    if(EndReach(map, robot.x, robot.y)){
        printf("\n\n\t\t\tSORTIE TROUVEE EN %d ETAPES\n\n", *steps);
        return 1;
    }

    // Check si Mur devant
    if(nextIsWall(map, robot.x, robot.y, robot.direction)){
        return 0;
    }

    // Explorer vers la gauche
    turnRobotLeft(&robot);
    moveRobot(&robot, &map);
    way = solvemaze(robot, map, graph, mode, steps);
    if(way){ return 1;}

    // Explorer tout droit
    turnRobotRight(&robot);
    moveRobot(&robot, &map);
    way = solvemaze(robot, map, graph, mode, steps);
    if(way){ return 1;}

    // Explorer vers la droite
    turnRobotRight(&robot);
    moveRobot(&robot, &map);
	way = solvemaze(robot, map, graph, mode, steps);
	if(way){ return 1;}

    // Explorer vers le bas
    turnRobotRight(&robot);
    moveRobot(&robot, &map);
    way = solvemaze(robot, map, graph, mode, steps);
    if(way){ return 1;}

	// Sinon c'est une impasse
    return 0;
}
