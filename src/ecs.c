#include "ecs.h"
#include <stdio.h>
#include "raylib.h"
int next_entity_id;



void ECS_Init(ECS *ecs){
    ecs->count = 0;
    next_entity_id = 0;
}
Entity ECS_CreateEntity(ECS *ecs){
    Entity entity;
    entity.entity_id = next_entity_id;
    next_entity_id++;
    ecs->entities[ecs->count] = entity;
    ecs->count++;
    return entity;
}
void ECS_DestroyEntity(ECS *ecs, int entity_id){
    for (int i = 0; i < ecs->count; i++){
        if (ecs->entities[i].entity_id == entity_id){
            printf("Se destruyó la entidad %d\n",ecs->entities[i].entity_id);    
            for (int j = i; j < ecs->count - 1; j++){
                ecs->entities[j] = ecs->entities[j + 1];
            }
            ecs->count--;
            break;
        }
    }
}
void ECS_UpdateEntities(ECS *ecs, Player *player){
    for (int i = 0; i < ecs->count; i++){
        if(ecs->entities[i].position.y>GetScreenHeight()){
            ECS_DestroyEntity(ecs,ecs->entities[i].entity_id);
            player->score+=10;
        }
        ecs->entities[i].position.y += ecs->entities[i].speed.y;
        if (ecs->entities[i].position.x < ecs->entities[i].initial_position.x-30 || ecs->entities[i].position.x > ecs->entities[i].initial_position.x+30)
            ecs->entities[i].speed.x *= -1;
        ecs->entities[i].position.x += ecs->entities[i].speed.x;
    }
}

void ECS_DrawEntities(ECS *ecs){
    for (int i = 0; i < ecs->count; i++){
        if (ecs->entities[i].visible){
            Entity entity=ecs->entities[i];
            DrawTextureRec(entity.texture, entity.rectangle_frame, entity.position, WHITE); 
        }
    }
}

Entity ECS_GetEntity(ECS *ecs, int entity_id){
    for (int i = 0; i < ecs->count; i++){
        if (ecs->entities[i].entity_id == entity_id){
            return ecs->entities[i];
        }
    }
    Entity entity;
    entity.entity_id = -1;
    return entity;
}
void ECS_SetEntity(ECS *ecs, int entity_id, Entity entity){
    for (int i = 0; i < ecs->count; i++){
        if (ecs->entities[i].entity_id == entity_id){
            ecs->entities[i] = entity;
            break;
        }
    }
}