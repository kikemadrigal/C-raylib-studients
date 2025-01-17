#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "input.h"
typedef struct {
    //Como las texturas se cargan cuando creamos la entidad en el game.c, no necesitamos cargarlas aquí
    int x,y;
    int x_init, y_init;
    int offset_x;
    int offset_y;
    int width;
    int height;
    short lives;
    long score;
    long hiscore;
    Texture2D texture;
    Rectangle rectangle_frame;
    int frame_counter;
    int frame_speed;
    int anim;
    bool collidable;
    float rest_time_colliable;
    bool visible;
}Player;

void initPlayer(Player *player);
void updatePlayer(Player *player, Input input);
void drawPlayer(Player *player, Input input);
void unloadPlayer(Player *player);
#endif