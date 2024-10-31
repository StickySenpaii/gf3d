#include "simple_logger.h"
#include "gfc_input.h"
#include "player.h"
#include "entity.h"

#include "gf3d_camera.h"
#include "math.h"
#include <string.h>
#include "simple_logger.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"

#include "simple_logger.h"

#include "gfc_text.h"
#include "gfc_list.h"
#include "gfc_color.h"
#include "gfc_shape.h"

#include "gf3d_vgraphics.h"
#include "gf3d_texture.h"
#include "gf2d_sprite.h"
#include "gf2d_font.h"


//void gf3d_player_walk_forward(Entity* self, float speed);
//void gf3d_player_move(Entity* self, GFC_Vector3D translation);


Entity *player_new()
{
	Entity *self;

	self = entity_new();
	if (!self)
	{
		slog("failed to spawn a player");
		return NULL;
	}
	
	//self->name = "Player";
	self->hp = 100;
	self->model = gf3d_model_load("models/dino.model");
	self->frame = 0.0;
	self->speed = -1.0;
	self->position = gfc_vector3d(5, 5, 5);
	slog("Player spawn position set to: (%f, %f, %f)", self->position.x, self->position.y, self->position.z);
	self->think = player_think;
	self->update = player_update;
	self->free = player_free;

	return self;
}

void player_think(Entity* self)
{
	if (!self)return;
}

void player_free(Entity* self)
{
    if (!self)return;
}

void player_update(Entity* self)
{
	if (!self) return;

	float moveSpeed = self->speed;
	GFC_Vector3D translation; // Add this for the movement translation
	const Uint8* keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

	if (keys[SDL_SCANCODE_E])
	{
		slog("E key pressed: Moving player forward.");
		self->hp = self->hp - 50;
		if (self->hp == 0)
		{
			slog("Dead homne");
		}

		// Define the forward translation (for example, moving along the z-axis)
		translation.x = 0;
		translation.y = moveSpeed;
		translation.z = 0;

		// Add the translation vector to the player's position to move forward
		gfc_vector3d_add(self->position, self->position, translation);
	}
}

void display_player_hp(Entity* player)
{
	if (!player) return;  // Check if the player entity exists
	slog("display_player_hp called");  // Debugging line to confirm it's being called

	// Buffer to hold the HP text
	char hp_text[50];
	snprintf(hp_text, sizeof(hp_text), "HP: %d", player->hp);  // Convert HP to a string

	// Render the HP text at position (10, 10) on the screen
	gf2d_font_draw_line_tag(
		hp_text,                // Text to display, e.g., "HP: 100"
		FT_H1,                  // Font tag (use the correct tag for your font style/size)
		GFC_COLOR_RED,          // Color of the text (white)
		gfc_vector2d(10, 10)    // Position on the screen (adjust as needed)
	);
}