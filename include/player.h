#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
/**
 * @brief get the direction up from wht the camera is looking in
 * @return a zero vector on error, or the unit vector looking forward
 */
Entity *player_new();

void player_think(Entity* self);
void player_update(Entity* self);
void player_free(Entity* self);


#endif