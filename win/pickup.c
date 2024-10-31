#include "simple_logger.h"

#include "pickup.h"
#include "entity.h"

void pickup_think(Entity* self);
void pickup_update(Entity* self);
void pickup_free(Entity* self);

Entity* pickup_new()
{
	Entity* self;

	self = entity_new();
	if (!self)
	{
		slog("failed to spawn a pickup");
	}

	self->hp = 100;
	self->model = gf3d_model_load("models/food.model");
	self->frame = 0.0;
	self->speed = 15.0;
	gfc_vector3d_set(self->position, -5.0, -5.0, -5.0);
	gfc_vector3d_set(self->rotation, 0.0, 0.0, 0.0);
	gfc_vector3d_set(self->scale, 1.0, 1.0, 1.0);
	self->think = pickup_think;
	self->update = pickup_update;
	self->free = pickup_free;
	
	return self;
}

void pickup_think(Entity* self)
{
	if (!self)return;
}

void pickup_update(Entity* self)
{
	if (!self)return;
}

void pickup_free(Entity* self)
{
	if (!self) return;
}