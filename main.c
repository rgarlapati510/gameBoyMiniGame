#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"

#define REG_DISPCTL (*((unsigned short*)0x04000000))
#define BG2 (1<<10)
#define MODE3 (3)

/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"

/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.
enum gba_state {
  START,
  INTRO,
  PLAY,
  WIN,
  LOSE,
  STATE;
};

int pos(int row1, int col1, int row2, int col2) {
  return (row1 < row2 + 15 && row1 + 15 > row2 && col1 < col2 + 15 && col1 + 15 > col2);
}

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //


  REG_DISPCTL = BG2 | MODE3;
  //^ set the video mode


  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;


  // Load initial application state
  enum gba_state state = START;
  Rabbit bugsBunny;
  Carrot c;
  Hole h;

  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw
    waitForVBlank();

    switch (state) {
      case START:
        bugsBunny.row = 10;
        bugsBunny.col = 10;
        c.row = 70;
        c.col = 90;
        h.row = 30;
        h.col = 60;
        drawFullScreenImageDMA(bunnyRabbit);
        //create image named bunnyRabbit (title screen)
        // state = ?
        state = INTRO;
      case INTRO:
        drawString(20, 10, "HELP BUGS BUNNY FIND HIS FOOD", BLACK);
        drawString(40, 10, "PRESS START TO BEGIN", BLACK);
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          state = PLAY;
        }
        break;
        // state = ?

      case PLAY:
        drawFullScreenImageDMA(field);
        //create image named field (for game play)
        drawImageDMA(bugsBunny.row, bugsBunny.col, BUNNY_WIDTH, BUNNY_HEIGHT, rabbit);
        drawImageDMA(c.row, c.col, CARROT_WIDTH, CARROT_HEIGHT, carrot);
        drawImageDMA(h.row, h.col, HOLE_WIDTH, HOLE_HEIGHT, hole);
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          state = START;
        }
        if (KEY_DOWN(BUTTON_LEFT, currentButtons) && bugsBunny.col > 0) {
          bugsBunny.col -= 1;
        }
        if (KEY_DOWN(BUTTON_RIGHT, currentButtons) && bugsBunny.col < WIDTH - 15) {
          bugsBunny.col += 1;
        }
        if (KEY_DOWN(BUTTON_UP, currentButtons) && bugsBunny.row > 0) {
          bugsBunny.row -= 1;
        }
        if (KEY_DOWN(BUTTON_DOWN, currentButtons) && bugsBunny.row < HEIGHT - 15) {
          bugsBunny.row += 1;
        }
        if (pos(bugsBunny.row, bugsBunny.col, h.row, h.col) != 0) {
          state = LOSE;
        }
        if (pos(bugsBunny.rowm, bugsBunny.col, c.row, c.col) != 0) {
          state = WIN;
        }
        break;
        // state = ?

      case WIN:
        drawFullScreenImageDMA(fatBunny);
        //create new image of a fat full bunny
        drawString(40, 50, "YAY, BUGS BUNNY IS FED!", BLACK);
        drawString(60, 50, "YOU WIN!", BLACK);
        drawString(110, 30, "CLICK SELECT TO PLAY AGAIN!", BLACK);
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          state = START;
        }

        // state = ?
        break;
      case LOSE:
        drawFullScreenImageDMA(sadBunny);
        //create new image of a sad bunny
        drawString(40, 50, "OH, NO! BUGS BUNNY FELL INTO A HOLE!", BLACK);
        drawString(60, 50, "YOU LOSE :( !", BLACK);
        drawString(110, 30, "CLICK SELECT TO PLAY AGAIN!", BLACK);
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          state = START;
        }

        // state = ?
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  UNUSED(previousButtons); // You can remove this once previousButtons is used

  return 0;
}
