#include "player.h"
#include "input.h"
#include "raylib.h"


void initPlayer(Player *player){
    //Inicializa al jugador
    player->position = (Vector2){GetScreenWidth()/2,GetScreenHeight()-150};
    player->init_position = (Vector2){GetScreenWidth()/2,GetScreenHeight()-64};
    player->lives = 10;
    player->score = 0;
    player->texture = (Texture2D) LoadTexture("resources/Loreto-texture-128-64.png");       
    player->rectangle_frame=(Rectangle) {
        0,
        0,
        64,
        player->texture.height
    };
    player->frame_counter = 0;
    player->frame_speed = 8;
    //player->hit=(Sound)LoadSound("sounds/hit.mp3");
}

void updatePlayer(Player *player, Input input){
    if(player->position.x<0){
        player->position.x=0;
    }else if(player->position.x>GetScreenWidth()-player->texture.width/2){
        player->position.x=GetScreenWidth()-player->texture.width/2;
    }
    if (player->position.y<580){
        player->position.y=580;
    }else if(player->position.y>GetScreenHeight()-player->texture.height){
        player->position.y=GetScreenHeight()-player->texture.height;
    }
    switch(input){
        case UP:
            player->position.y -= 5;
            break;
        case DOWN:
            player->position.y += 5;
            break;
        case LEFT:
            player->position.x -= 5;
            break;
        case RIGHT:
            player->position.x += 5;
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
    if(input!=-1){
        player->frame_counter++;  
    }
    
    if (player->frame_counter >= (60/player->frame_speed))
    {
        player->frame_counter = 0;
        player->rectangle_frame.x -= 64;
    }
    
    DrawTextureRec(player->texture, player->rectangle_frame, player->position, WHITE); 
}

void unloadPlayer(Player *player){
    //Libera la memoria del jugador
    UnloadTexture(player->texture);
}

