#ifndef ENTITY_H
#define ENTITY_H

#include "gfc_types.h"
#include "gf3d_model.h"
#include "gfc_text.h"
#include "gf3d_obj_load.h"

typedef struct Entity_S
{
    Uint8          _inuse;                              // In-use flag
    GFC_TextLine   name;                                // Name of entity / Currently unused
    int            hp;                                  // Health
    int            money;                               // https://youtu.be/HMuYfScGpbE?si=8-LeEmPyxDMG4tci
    Model          *model;                              // Pointer to OBJ data
    float          frame;                               // Frame of animation (if applicable)
    float          speed;                               // Gotta go fast
    GFC_Vector3D   position;                            // Entity's position in the world
    GFC_Vector3D   rotation;                            // Entity's rotation in the world
    GFC_Vector3D   scale;                               // Scale
    void           (*think)(struct Entity_S* self);     // Function pointer to make decisions (AI, etc.)
    void           (*update)(struct Entity_S* self);    // Function pointer to update entity state
    void           (*free)(struct Entity_S* self);      // Function pointer to cleanup data
    int            (*draw)(struct Entity_S* self);      // Draws the Entity
    void           *data;                               // Additional data related to the entity
}Entity;

/*
* @brief Entity management system, Cleans up on exit
* @Param Maximum entities
*/
void entity_system_initialize(Uint32 max);

void entity_system_close();

/*
* @brief Clean up between levels
* @param Do not clean up entity 
*/
void entity_clear_all(Entity *ignore);

/*
* @brief Get a blank entity for use
* @return NULL on error
*/
Entity *entity_new();

/*
* @brief returns/cleans data from an entity
* @param the entity to free
*/
void entity_free(Entity *self);

/*
* @brief Run think function for all active entities
*/
void entity_system_think();

/*
* @brief Run update function for all active entities
*/
void entity_system_update();

/*
* @brief Run draw function for all active entities
*/
void entity_system_draw();


#endif // !ENTITY_H
