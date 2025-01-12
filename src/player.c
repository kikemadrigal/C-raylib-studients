#include "player.h"
#include "input.h"
#include "raylib.h"


void initPlayer(Player *player){
    //Inicializa al jugador
    player->position = (Vector2){200,700};
    player->lives = 3;
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
}
Texture2D getTexturePlayer(){
    Texture2D textura=LoadTexture("resources/Loreto-texture.png");
    return textura;
}
void updatePlayer(Player *player, Input input){
    if(player->position.x<0){
        player->position.x=0;
    }else if(player->position.x>GetScreenWidth()-player->texture.width){
        player->position.x=GetScreenWidth()-player->texture.width;
    }
    if (player->position.y<0){
        player->position.y=0;
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