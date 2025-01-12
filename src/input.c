#include "raylib.h"
#include "input.h"

void initInput(void){
    //Inicializa el sistema de input
}
Input readInput(void){
    //Lee el input del jugador y lo devuelve
    Input result = -1;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){
        result= UP;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){
        result= DOWN;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
        result= LEFT;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        result= RIGHT;
    }
    return result;
}


