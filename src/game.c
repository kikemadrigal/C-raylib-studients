#include "raylib.h"
#include "game.h"
#include "input.h"
#include "player.h"
#include "ecs.h"
#include "physics.h"
#include <stdio.h>

Player player;
Input input;
ECS ecs;
//float current_time=GetTime();
//float end_time=GetTime()+10.0f;
        // Load WAV audio file
#define MAX_STUDIENTS 9
Texture2D texture_papers[4];
Music musics[4];
Sound sounds[2];

typedef enum Objects{
    AVION,
    CISNE,
    BARCO,
    MARIPOSA
}Objects;
typedef enum Effects{
    PAPER,
    COLLISION,
    PLAYER_DIE,
    ENEMY_DIE
}Effects;


void init_game(Game *game ){
    game->status=INITIAL;
    game->ultima_pulsacion=-1;
    game->background=(Texture2D) LoadTexture("resources/background800x400.png"); 
    game->level=1; 
    game->is_paused=false;
    game->end_time=GetTime()+100.0f;

    InitAudioDevice();   
    //https://freesound.org/
    //para generar la musica xm: https://github.com/milkytracker/MilkyTracker/releases/tag/v1.05.01
    musics[MENU]=(Music)LoadMusicStream("sounds/menu.xm");
    musics[GAME_LOOP]=(Music)LoadMusicStream("sounds/ingame.xm");
    game->music=musics[MENU];
    Music music = LoadMusicStream("sounds/gameover.wav");
    music.looping = false;
    musics[GAME_OVER]=music;
    sounds[PAPER]=(Sound)LoadSound("sounds/paper.wav");
    sounds[COLLISION]=(Sound)LoadSound("sounds/collision.mp3");



}

void update_game(Game *game){
    UpdateMusicStream(game->music); 
    switch(game->status){
        case INITIAL:
            if (IsKeyPressed(KEY_ENTER)){
                game->status=MENU;
            }
            break;
        case MENU:
            PlayMusicStream(game->music);
            if (IsKeyPressed(KEY_ENTER)){
                game->status=GAME_LOOP;
                StopMusicStream(game->music);
                game->music=musics[GAME_LOOP];
                SetMusicVolume(game->music, 0.1f);
                if(game->level==1) init_level_1(game);
                else if (game->level==2) init_level_2(game);
                game->end_time=GetTime()+100.0f;
            }
            break;
        case GAME_LOOP:
            PlayMusicStream(game->music);
            if (player.lives==0) {
                game->status=GAME_OVER;
                player.x=-180;
                StopMusicStream(game->music);
                game->music=musics[GAME_OVER];
            }
            float let_time=game->end_time-GetTime();
            if (let_time<0){
                game->status=WIN;
            }
            if(game->level==1) update_level_1(game);
            input = readInput();
       
            updatePlayer(&player, input);
            ECS_UpdateEntities(&ecs, &player);
            check_collsisions();
            break;
        case GAME_OVER:
            if(GetMusicTimePlayed(game->music)<GetMusicTimeLength(game->music)-0.1){
                PlayMusicStream(game->music);
            }else{
                PauseMusicStream(game->music);
            }           
            if (IsKeyPressed(KEY_ENTER)){
                game->status=MENU;
                StopMusicStream(game->music);
                game->music=musics[MENU];

            }
            break;
        case WIN:
            if (IsKeyPressed(KEY_ENTER)){
                game->status=MENU;
                StopMusicStream(game->music);
                initPlayer(&player);
                ECS_Init(&ecs);
                game->end_time=GetTime()+100.0f;
            }
            break;
    }
}



void draw_game(Game *game){
    switch(game->status){
        case INITIAL:
            DrawText("Murciadevs presents: ", GetScreenWidth()/2-100, 50, 18, RED);
            DrawText("¿Sobrevivira la profesora\n\n a los alumnos agobiantes?", GetScreenWidth()/2-100, 150, 20, YELLOW);
            DrawText("Press Enter", GetScreenWidth()/2-100, 300, 20, RED);      
            break;
        case MENU:
            ClearBackground(BLACK);
            DrawText("Fase 1", GetScreenWidth()/2-100, 50, 20, RED);
            DrawText("Clase de python", GetScreenWidth()/2-100, 150, 18, YELLOW);
            DrawText("Esquiva las figuras de papel \n\nque lazan los alumnos\n\nTienes 100 segundos", GetScreenWidth()/2-100, 200, 16, GREEN);
            DrawText("Press Enter to start", GetScreenWidth()/2-100, 300, 14, BLUE); 
            break;
        case GAME_LOOP:
            ClearBackground(RAYWHITE);
            DrawTexture(game->background, 0, 0, WHITE);
            drawPlayer(&player, input);
            ECS_DrawEntities(&ecs);
            GUI(game);
            break;
        case GAME_OVER:
            ClearBackground(BLACK);
            DrawText("Game over", GetScreenWidth()/2-100, 150, 30, GREEN);
            DrawText("Press Enter to start", GetScreenWidth()/2-100, 300, 14, BLUE); 
            break;
        case WIN:
            DrawText("You win", GetScreenWidth()/2-100, 150, 30, GREEN);
            DrawText("Press Enter to start", GetScreenWidth()/2-100, 300, 14, BLUE); 
            break;
    }      
}

void unload_game(Game *game){
    //Libera la memoria del juego
    UnloadTexture(game->background);
    unloadPlayer(&player);
    UnloadMusicStream(game->music);
    UnloadSound(sounds[PAPER]);
    UnloadSound(sounds[COLLISION]);
    UnloadTexture(texture_papers[AVION]);
    UnloadTexture(texture_papers[CISNE]);
    UnloadTexture(texture_papers[BARCO]);
    UnloadTexture(texture_papers[MARIPOSA]);
    CloseAudioDevice();
}

void GUI(Game *game){
    float left_time=game->end_time-GetTime();
    DrawText(TextFormat("Score: %08i", player.score), 10, 10, 24, RED);
    DrawText(TextFormat("Time: %d", (int )left_time), 340, 10, 24, GREEN);
    DrawText(TextFormat("Lives: %02i", player.lives), 640, 10, 24, YELLOW);
}
void check_collsisions(void){
    for (int i = 0; i < ecs.count; i++){
        if (checkCollisionRects( 
            (Rectangle){
                player.x+player.offset_x, 
                player.y+player.offset_y, 
                player.width, 
                player.height
            }, 
            (Rectangle){
                ecs.entities[i].position.x, 
                ecs.entities[i].position.y, 
                ecs.entities[i].texture.width, 
                ecs.entities[i].texture.height
            }
        )){
            if(player.collidable==false)return;
            ECS_DestroyEntity(&ecs,ecs.entities[i].entity_id);
            PlaySound(sounds[COLLISION]);
            player.lives--;
            player.x=player.x_init;
            player.y=player.y_init;
            player.rest_time_colliable=GetTime();
            //hacemos que el player no pueda colisionar por 2 segundos
            player.collidable=false;
            //hacemos una pausa de 1 segundo
            for (int i = 0; i < 1000000000; i++){}
        }
    }
}




/************************************************************** 
 * 
 *                  LEVELS
 * 
 * ************************************************************/



/**
 * En el nivel 1 se crean los aviones, cisnes, barcos y mariposas aleatoriamente, la profesora los tiene que esquibar
 */

void init_level_1(Game *game){
    texture_papers[AVION]=LoadTexture("resources/avion.png");
    texture_papers[CISNE]=LoadTexture("resources/cisne.png");
    texture_papers[BARCO]=LoadTexture("resources/barco.png");
    texture_papers[MARIPOSA]=LoadTexture("resources/mariposa.png");

    initPlayer(&player);   
    ECS_Init(&ecs);
}


void update_level_1(Game *game){
    Vector2 positions_studients[MAX_STUDIENTS]={
        (Vector2){200,40},
        (Vector2){370,140},
        (Vector2){520,240},
        (Vector2){200,40},
        (Vector2){370,140},
        (Vector2){520,240},
        (Vector2){200,40},
        (Vector2){370,140},
        (Vector2){520,240}
    };

    game->counter++;
    if (game->counter%40==0){
        game->counter=0;
        Entity entity=ECS_CreateEntity(&ecs);
        int object_number=GetRandomValue(0,3);
        if(object_number==AVION)
            entity.texture=texture_papers[AVION];
        else if (object_number==CISNE){
            entity.texture=texture_papers[CISNE];
        }else if (object_number==BARCO){
            entity.texture=texture_papers[BARCO];
        }else if (object_number==MARIPOSA){
            entity.texture=texture_papers[MARIPOSA];
        }
        Vector2 position=positions_studients[GetRandomValue(0,MAX_STUDIENTS)];
        entity.position=position;
        entity.initial_position=position;
        entity.speed=(Vector2){1,0.5f};
        entity.visible=true;
        entity.rectangle_frame=(Rectangle){0,0,entity.texture.width,entity.texture.height};
        entity.frame_counter=0;
        entity.frame_speed=8;
        int random_number=GetRandomValue(0,3);
        if (random_number==0)
            add_tag(&entity,"paper ");
        else
            add_tag(&entity,"otro  ");
        ECS_SetEntity(&ecs,entity.entity_id,entity);
        //Reproducimos el sonido de crear papel
        PlaySound(sounds[PAPER]);
    }
}


void init_level_2(Game *game){
    texture_papers[AVION]=LoadTexture("resources/avion.png");
    texture_papers[CISNE]=LoadTexture("resources/cisne.png");
    texture_papers[BARCO]=LoadTexture("resources/barco.png");
    texture_papers[MARIPOSA]=LoadTexture("resources/mariposa.png");

    initPlayer(&player);   
    ECS_Init(&ecs);
}

