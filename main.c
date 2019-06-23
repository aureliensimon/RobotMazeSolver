#include "header.h"

int main(int argc, char**argv){

    Map map;
    Robot robot;
    Graph graph;
    int steps = 0;
    int affTrace;

    // Test nombre arguments
    if(argc != 3){
        printf("./a.out [nom fichier] [mode (t/g)]\n");
        return -1;
    }

    // Init la Carte & Robot
    map = getmap(argv[1]);
    initRobot(&robot, map);
    rotatestart(&robot, map);

    // Choix du mode
    if(!strcmp("t", argv[2])){
        // MODE TEXTUEL
        printmenu(argv[1], &robot);
        int way = solvemaze(robot, map, graph, 't', &steps);
        if(!way){
            printf("Pas de Solution :(\n");
        }
    }else if(!strcmp("g", argv[2])){
        // MODE GRAPHIQUE
        graphmode(graph, robot, map, &steps);
    }else{
        // Mauvais choix de mode
        printf("./a.out [nom fichier] [mode (t/g)]\n");
    }

    freeall(map);
    return 0;
}
