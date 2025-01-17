#include "player.h"
#include "input.h"
#include "raylib.h"
#include <stdio.h>

void initPlayer(Player *player){
    //Inicializa al jugador
    player->x = GetScreenWidth()/2;
    player->y= GetScreenHeight()-150;
    player->x_init = GetScreenWidth()/2;
    player->y_init = GetScreenHeight()-150;
    player->lives = 3;
    player->score = 0;
    player->offset_x = 20;
    player->offset_y = 5;
    player->width = 30;
    player->height = 50;
    player->texture = (Texture2D) LoadTexture("resources/Loreto-texture-128-128.png");       
    player->rectangle_frame=(Rectangle) {
        0,
        0,
        64,
        64
    };
    player->frame_counter = 0;
    player->frame_speed = 8;
    player->anim=0;
    player->collidable = true;
    player->rest_time_colliable = 0;
}

void updatePlayer(Player *player, Input input){
    if(player->x<0)
        player->x=0;
    else if(player->x>GetScreenWidth()-player->texture.width/2)
        player->x=GetScreenWidth()-player->texture.width/2;
    

    if(player->y>GetScreenHeight()-player->height-10)
        player->y=GetScreenHeight()-player->height-10;
    else if (player->y<0)
        player->y=0;

    
    switch(input){
        case UP:
            player->y -= 5;
            break;
        case DOWN:
            player->y += 5;
            break;
        case LEFT:
            player->x -= 5;
            player->anim=0;
            player->frame_counter++;  
            break;
        case RIGHT:
            player->x += 5;
            player->anim=1;
            player->frame_counter++;  
            break;
        case FIRE:
            //Disparar
            break;
        case START:
            //Iniciar el juego
            break;
    }
}
void drawPlayer(Player *player, Input input){   
    int left_time=(int)player->rest_time_colliable+7.0f-GetTime();
    //Si el player ha tenido una collisión hacemos un efecto parpadeo
    if(player->collidable==false){
        if(left_time>0){
            if(left_time%2==0){   
                DrawTextureRec(player->texture, player->rectangle_frame,(Vector2){player->x,player->y}, RED);
            }else{
                DrawTextureRec(player->texture, player->rectangle_frame,(Vector2){player->x,player->y}, WHITE); 
            }
        }else{
            player->collidable=true;
        }
    }
  

    printf("\nframe_counter:%d",player->frame_counter);
    //if (player->frame_counter >= (60/player->frame_speed))
    if (player->frame_counter%4==0)
    {
        player->rectangle_frame.x = 64;
        player->frame_counter = 0;
    } else{
        player->rectangle_frame.x = 0;
        player->frame_counter = 1;
    }
    if(player->anim==0)player->rectangle_frame.y=0;
    if(player->anim==1)player->rectangle_frame.y=64;
    //printf("\nx:%f,y:%f,w:%f,h:%f",player->rectangle_frame.x,player->rectangle_frame.y,player->rectangle_frame.width,player->rectangle_frame.height);
    if(player->collidable)
        DrawTextureRec(player->texture, player->rectangle_frame,(Vector2){player->x,player->y}, WHITE);
    
    DrawRectangleLines(player->x+player->offset_x, player->y+player->offset_y, player->width, player->height, RED);
}

void unloadPlayer(Player *player){
    //Libera la memoria del jugador
    UnloadTexture(player->texture);
}


