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
        // Load WAV audio file
#define MAX_STUDIENTS 9
Vector2 positions_studients[MAX_STUDIENTS]={
    (Vector2){50,170},
    (Vector2){200,170},
    (Vector2){350,170},
    (Vector2){50,270},
    (Vector2){200,270},
    (Vector2){350,270},
    (Vector2){50,390},
    (Vector2){200,390},
    (Vector2){350,390}
};
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
    game->background=(Texture2D) LoadTexture("resources/background.png"); 
    game->level=1; 
    InitAudioDevice();   
    initPlayer(&player);   
    //https://freesound.org/
    musics[MENU]=(Music)LoadMusicStream("sounds/menu.xm");
    musics[GAME_LOOP]=(Music)LoadMusicStream("sounds/ingame.wav");
    Music game_over_music=(Music)LoadMusicStream("sounds/gameover.wav");
    game_over_music.looping=false;
    musics[GAME_OVER]=game_over_music;
    game->music=musics[MENU];
    sounds[PAPER]=(Sound)LoadSound("sounds/paper.wav");
    sounds[COLLISION]=(Sound)LoadSound("sounds/collision.mp3");
    texture_papers[AVION]=LoadTexture("resources/avion.png");
    texture_papers[CISNE]=LoadTexture("resources/cisne.png");
    texture_papers[BARCO]=LoadTexture("resources/barco.png");
    texture_papers[MARIPOSA]=LoadTexture("resources/mariposa.png");
}

void update_game(Game *game){
    UpdateMusicStream(game->music); 
    switch(game->status){
        
        case INITIAL:

            if (IsKeyPressed(KEY_ENTER)){
                game->status=MENU;
                //game->music=musics[MENU];
                //PlayMusicStream(game->music);
            }

            break;
        case MENU:
            PlayMusicStream(game->music);
            if (IsKeyPressed(KEY_ENTER)){
                game->status=GAME_LOOP;
                StopMusicStream(game->music);
                game->music=musics[GAME_LOOP];
            }
            break;
        case GAME_LOOP:
            PlayMusicStream(game->music);
            if (player.lives==0) {
                game->status=GAME_OVER;
                StopMusicStream(game->music);
                game->music=musics[GAME_OVER];
            }
            if(game->level==1) update_level_1(game);
            input = readInput();
            updatePlayer(&player, input);
            ECS_UpdateEntities(&ecs, &player);
            check_collsisions();
            break;
        case GAME_OVER:
            PlayMusicStream(game->music);
            if (IsKeyPressed(KEY_ENTER)){
                game->status=MENU;
                StopMusicStream(game->music);
                game->music=musics[MENU];
                game->level=1;
                ECS_Init(&ecs);
                initPlayer(&player);
            }
            DrawText("Game over", 150, 310, 20, GREEN);
            break;
        case WIN:
            //Mostrar la pantalla de victoria
            break;
    }
}



void draw_game(Game *game){
    switch(game->status){
        case INITIAL:
            DrawText("Murciadevs presents: ", 50, 50, 18, RED);
            DrawText("¿Sobrevivira la profesora\n\n a los alumnos agobiantes?", 50, 150, 20, YELLOW);
            DrawText("Press Enter to start", 50, 310, 20, RED);     
            DrawText("Juego escrito en C", 50, 500, 16, GREEN);       
            break;
        case MENU:
            ClearBackground(BLACK);
            DrawText("Fase 1\n\nClase de python", 150, 310, 20, GREEN);
            break;
        case GAME_LOOP:
            ClearBackground(RAYWHITE);
            DrawTexture(game->background, 0, 0, WHITE);
            drawPlayer(&player, input);
            ECS_DrawEntities(&ecs);
            GUI();
            break;
        case GAME_OVER:
            //Mostrar la pantalla de game over
            break;
        case WIN:
            //Mostrar la pantalla de victoria
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

void GUI(){
    DrawText(TextFormat("Score: %08i", player.score), 10, 10, 24, RED);
    DrawText(TextFormat("Lives: %02i", player.lives), 270, 10, 24, YELLOW);
}

void update_level_1(Game *game){
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
        ECS_SetEntity(&ecs,entity.entity_id,entity);
        //Reproducimos el sonido de crear papel
        PlaySound(sounds[PAPER]);
    }
}

void check_collsisions(void){
    for (int i = 0; i < ecs.count; i++){
        if (checkCollisionRecs( 
            (Rectangle){
                player.position.x, 
                player.position.y, 
                player.texture.width-64, 
                player.texture.height
            }, 
            (Rectangle){
                ecs.entities[i].position.x, 
                ecs.entities[i].position.y, 
                ecs.entities[i].texture.width, 
                ecs.entities[i].texture.height
            }
        )){
            ECS_DestroyEntity(&ecs,ecs.entities[i].entity_id);
            PlaySound(sounds[COLLISION]);
            player.lives--;
            player.position.x=player.init_position.x;
            player.position.y=player.init_position.y;
        }
    }
}
