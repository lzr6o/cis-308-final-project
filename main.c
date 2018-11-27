#include <gb/gb.h>
#include "alpha.c"
#include "helloWorld.c"
#include "blankScreen.c"
#include "sprites.c"

void init();
void checkInput();
void updateSwitches();

// The player array will hold the player's position as X ([0]) and Y ([1])
UINT8 player[2];

void main() {

	init();
	
	while(1) {
		
		checkInput();				// Check for user input (and act on it)
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting memory
	}
	
}

void init() {
	
	DISPLAY_ON;						// Turn on the display
	set_bkg_data(0, 47, alpha);		// Load 47 tiles into background memory
	
	// Use the 'helloWorld' array to write background tiles starting at 0,6 (tile positions)
	//  and write for 10 tiles in width and 2 tiles in height
	set_bkg_tiles(0,6,10,2,helloWorld);
	
	// Load the the 'sprites' tiles into sprite memory
	set_sprite_data(0, 1, sprites);
	
	// Set the first movable sprite (0) to be the first tile in the sprite memory (0)
	set_sprite_tile(0,0);
	
	player[0] = 80;
	player[1] = 72;

}

void updateSwitches() {
	
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
	
}

void checkInput() {

    if (joypad() & J_B) {
		
		// Use the 'blankScreen' array to write background tiles starting at 0,0 (tile positions)
		//  and for 20 tiles in width and 18 tiles in height
		set_bkg_tiles(0,0,20,18,blankScreen);
    }
	
	// UP
	if (joypad() & J_UP) {
			
		player[1]--;
		
	}

	// DOWN
	if (joypad() & J_DOWN) {
			
		player[1]++;
		
	}

	// LEFT
	if (joypad() & J_LEFT) {
		
		player[0]--;
		
	}	
	
	// RIGHT
	if (joypad() & J_RIGHT) {
		
		player[0]++;
		
	}
	
	// Move the sprite in the first movable sprite list (0)
	//  the the position of X (player[0]) and y (player[1])
	move_sprite(0, player[0], player[1]);

}