#include "ecs.h"
#include <stdio.h>
#include <string.h>
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
            //printf("Se destruyó la entidad %d\n",ecs->entities[i].entity_id);    
            for (int j = i; j < ecs->count - 1; j++){
                ecs->entities[j] = ecs->entities[j + 1];
            }
            ecs->count--;
            break;
        }
    }
}
void ECS_UpdateEntities(ECS *ecs, Player *player){
    int limit=30;
    for (int i = 0; i < ecs->count; i++){
        Entity *entity=&ecs->entities[i];
        if(entity->position.y>GetScreenHeight()){
            ECS_DestroyEntity(ecs,entity->entity_id);
            player->score+=10;
        }

        if(strcmp(entity->tag,"paper ")==0){
            entity->position.y+=entity->speed.y;
            if (entity->position.x < entity->initial_position.x-limit || entity->position.x > entity->initial_position.x+limit){
                entity->speed.x *= -1;
            }
        }else if(strcmp(entity->tag,"otro  ")==0){
            limit=100;
            entity->speed.y+=0.1f;
            if (player->x-entity->position.x<0){
                entity->speed.x*=-1;
            }else{
                entity->speed.x=1;
            }
            entity->position.y+=entity->speed.y;
        }


           
        entity->position.x += entity->speed.x;
       
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

/**************************************
 * 
 *              TAGS
 * 
 * ***********************************/

void add_tag(Entity *entity, const char *tag){
    strcpy(entity->tag, tag);    
}
void remove_tag(Entity *entity){
    strcpy(entity->tag, "");
}
bool has_tag(Entity *entity, const char *tag){
    if(strcmp(entity->tag,tag)==0){
        return true;
    }
    return false;
}
void search_tag(ECS *ecs, const char *tag, Entity *entities, int *size){
    int count=0;
    for(int i=0;i<ecs->count;i++){
       if (has_tag(&ecs->entities[i], tag)){
            entities[count]=ecs->entities[i];
            count++;
       }
    }
    *size=count;
}

