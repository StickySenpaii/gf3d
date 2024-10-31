#include "simple_logger.h"
#include "entity.h"

typedef struct
{
	Entity		*entity_list;		//List of all active entities
	Uint32		 entity_max;		//max number of entities
}EntityManager;

void entity_system_close();

static EntityManager _entity_manager = { 0 };

void entity_system_initialize(Uint32 max)
{
	if (_entity_manager.entity_list)
	{
		slog("Cannot have more than one entity manager");
		return;
	}
	if (!max)
	{
		slog("0 Entities");
		return;
	}
	_entity_manager.entity_list = gfc_allocate_array(sizeof(Entity), max);
	if (!_entity_manager.entity_list)
	{
		slog("Failed to allocate entity list");
		return;
	}
	_entity_manager.entity_max = max;
	atexit(entity_system_close);
}

void entity_system_close()
{							//Clears all ignoring nothing
	entity_clear_all(NULL);
	if(_entity_manager.entity_list)free(_entity_manager.entity_list);
	memset(&_entity_manager,0,sizeof(EntityManager));
}

void entity_clear_all(Entity *ignore)
{
	int i;
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (&_entity_manager.entity_list[i] == ignore)continue;
		if (!_entity_manager.entity_list[i]._inuse)continue;
		//gf3d_model_free(_entity_manager.entity_list[i].model);
		//if (_entity_manager.entity_list[i].free)_entity_manager.entity_list[i].free(_entity_manager.entity_list[i].data);
		entity_free(&_entity_manager.entity_list[i]);
	}
}

Entity *entity_new() 
{
	int i;
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (_entity_manager.entity_list[i]._inuse)continue;
		memset(&_entity_manager.entity_list[i], 0, sizeof(Entity));
		_entity_manager.entity_list[i]._inuse = 1;
		return &_entity_manager.entity_list[i];
	}
	slog("no more entitys");
	return NULL;
}

void entity_free(Entity *self)
{
	if (!self) return;
	gf3d_model_free(self->model);
	if (self->free)self->free(self->data);
}

void entity_think(Entity *self)
{
	if (!self)return;
	if (self->think)self->think(self);
}


void entity_system_think()
{
	int i;
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (!_entity_manager.entity_list[i]._inuse)continue;
		entity_think(&_entity_manager.entity_list[i]);
	}
}

void entity_update(Entity* self)
{
	if (!self)return;
	if (self->update)self->update(self);
}


void entity_system_update()
{
	int i;
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (!_entity_manager.entity_list[i]._inuse)continue;
		entity_update(&_entity_manager.entity_list[i]);
	}
}

void entity_draw(Entity* self)
{
	GFC_Matrix4 entityMatrix;
	if (!self || !self->model) return;

	// Initialize the entityMatrix to the identity matrix
	gfc_matrix4_identity(entityMatrix);

	// Translate the entityMatrix using the entity's position
	gfc_matrix4_translate(entityMatrix, entityMatrix, self->position);

	// Draw the model with the transformed matrix
	gf3d_model_draw(
		self->model,
		entityMatrix,
		GFC_COLOR_WHITE,
		0);
}

void entity_system_draw()
{
	int i;
	if (!_entity_manager.entity_list) {
		slog("Entity list is not initialized.");
		return;
	}
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (!_entity_manager.entity_list[i]._inuse)continue;
		entity_draw(&_entity_manager.entity_list[i]);
	}
}
