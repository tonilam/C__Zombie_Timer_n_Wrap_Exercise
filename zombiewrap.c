#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cab202_graphics.h"
#include "cab202_sprites.h"
#include "cab202_timers.h"
#include "Week5Ex2.h"

void setup_zombie( Game * game ) {
	static char bitmap[] =
		"ZZZZ"
		"  Z "
		" Z  "
		"ZZZZ"
		;
	game->laps = 0;
	game->over = false;
	game->timer = create_timer(60);
	game->zombie = sprite_create(45, 8, 4, 4, bitmap);
	sprite_turn_to(game->zombie, 0.6, 0);
}

bool update_zombie( Game * game ) {
	if (game->over || !timer_expired(game->timer)) {			
		return false;
	} else {
		int old_x = 0;
		int new_x = 0;

		old_x = round(sprite_x(game->zombie));
		sprite_step(game->zombie);
		new_x = round(sprite_x(game->zombie));

		if (new_x >= screen_width()) {
			sprite_move_to(game->zombie, 0, sprite_y(game->zombie));
			++game->laps;
		}


		if (game->laps >= 6) {
			game->over = true;
		}
		return new_x != old_x;
	}
}

void display_zombie( Game * game ) {
	sprite_draw(game->zombie);
}

// --------- Do not submit the following functions --------- // 

void zombie_wrap( void ) {
	int frame = 0;
	Game game;

	setup_zombie( &game );
	clear_screen();
	display_zombie( &game );
	show_screen();

	while ( !game.over ) {
		if ( update_zombie( &game ) ) {
			clear_screen();
			display_zombie( &game );
			draw_int(0, 0, frame);
			draw_int(0, 1, round(sprite_x(game.zombie)));
			++frame;
			show_screen();
			wait_char();
		}

		timer_pause( 25 );
	}

	timer_pause( 1500 );
}

int main( void ) {
	setup_screen();
	zombie_wrap();
	cleanup_screen();
	return 0;
}
