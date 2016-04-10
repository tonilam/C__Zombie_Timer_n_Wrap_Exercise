#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "cab202_graphics.h"
#include "cab202_timers.h"
#include "Week5Ex1.h"

void setup_score( Game * game ) {
	game->score = 0;
	game->over = false;
	game->timer = create_timer(60);
}

bool update_score( Game * game ) {
	if (timer_expired(game->timer)) {
		++game->score;
		if (game->score >= 29) {
			game->over = true;
		}
		return true;
	}
    return false;
}

void display_score( Game * game ) {
	int printloc[] = {26,13};
	char status[80];
	char headingEnd[] = "Game over! Final score:";
	char headingLive[] = "Score:";
	char headingTime[] = "Clock time:";
	if (game->over) {
		sprintf(status, "%s %d", headingEnd, game->score);
		draw_string(printloc[0], printloc[1], status);
	} else {
		sprintf(status, "%s %d", headingLive, game->score);
		draw_string(printloc[0], printloc[1], status);
	}
		sprintf(status, "%s %f", headingTime, get_current_time());
		draw_string(printloc[0], printloc[1] + 1, status);
}

// --------- Do not submit the following functions --------- // 
void simple_timer( void ) {
	Game game;
	setup_score( &game );
	while ( !game.over ) {
		if ( update_score( &game ) ) {
			clear_screen();
			display_score( &game );
			show_screen();
		}
		timer_pause( 20 );
	}
	timer_pause( 1500 );
}
int main( void ) {
	setup_screen();
	simple_timer();
	cleanup_screen();
	return 0;
}