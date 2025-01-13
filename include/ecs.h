#ifndef ECS_H
#define ECS_H

#include "raylib.h"
#include "player.h"
#define MAX_ENTITIES 100
typedef struct {
    Vector2 position;
    Vector2 initial_position;
    Vector2 speed;
    bool visible;
    Texture2D texture;
    Rectangle rectangle_frame;
    int frame_counter;
    int frame_speed;
    int entity_id;
}Entity;


typedef struct {
    Entity entities[MAX_ENTITIES];
    int count;
    int ecs_delta;
}ECS;


void ECS_Init(ECS *ecs);
Entity ECS_CreateEntity(ECS *ecs);
void ECS_DestroyEntity(ECS *ecs, int entity_id);
void ECS_UpdateEntities(ECS *ecs, Player *player);
void ECS_DrawEntities(ECS *ecs);
Entity ECS_GetEntity(ECS *ecs, int entity_id);
void ECS_SetEntity(ECS *ecs, int entity_id, Entity entity);

#endif

