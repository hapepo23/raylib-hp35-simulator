#include <raylib.h>
#include <string.h>

#include "hp35.h"

/* HP-35 Simulator, Version 2025-02-19 */

/* ----------------------------------------------------------------*/

// Definitions

// Convert a macro to a string (stringification)
#define STR(x) #x
#define XSTR(x) STR(x)

// Definitions

#define SCREEN_WIDTH 342
#define SCREEN_HEIGHT 618
#define APP_TITLE "HP-35 Simulator (Raylib)"
#define APP_ICON "icon.png"
#define APP_BACKGROUND_COLOR BLACK
#define TARGET_FPS 30

#define FONT_COUNT 1
#define FONT_PATHS \
  { "seg7.ttf" }
#define FONT_SIZES \
  { 18 }
#define FONT_SPACINGS \
  { 0.f }
#define FONT_ADD_CP_RANGES_COUNT 0
#define FONT_ADD_CP_RANGES \
  {}
#define TEXT_LINE_SPACING 0
#define INPUT_CURSOR '_'

#define MAX_WIDGETS 38

/* ----------------------------------------------------------------*/

#include "myraygui.h"

/* ----------------------------------------------------------------*/

int main(void);
static void click(int id);
static void print(int id);

/* ----------------------------------------------------------------*/

// Widget Definitions

static WidgetData widgets[MAX_WIDGETS] = {
    {
        // 0 OFF
        .type = CLICKAREA,
        .position = {53, 133},
        .size = {89, 22},
        .click_event_fn = click,
    },
    {
        // 1 x^y
        .type = CLICKAREA,
        .position = {51, 175},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 2 log
        .type = CLICKAREA,
        .position = {102, 175},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 3 ln
        .type = CLICKAREA,
        .position = {153, 175},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 4 e^x
        .type = CLICKAREA,
        .position = {204, 175},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 5 clr
        .type = CLICKAREA,
        .position = {255, 175},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 6 sqrt
        .type = CLICKAREA,
        .position = {51, 225},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 7 arc
        .type = CLICKAREA,
        .position = {102, 225},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 8 sin
        .type = CLICKAREA,
        .position = {153, 225},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 9 cos
        .type = CLICKAREA,
        .position = {204, 225},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 10 tan
        .type = CLICKAREA,
        .position = {255, 225},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 11 1/x
        .type = CLICKAREA,
        .position = {51, 275},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 12 x<>y
        .type = CLICKAREA,
        .position = {102, 275},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 13 Rv
        .type = CLICKAREA,
        .position = {153, 275},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 14 sto
        .type = CLICKAREA,
        .position = {204, 275},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 15 rcl
        .type = CLICKAREA,
        .position = {255, 275},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 16 enter
        .type = CLICKAREA,
        .position = {51, 325},
        .size = {84, 31},
        .click_event_fn = click,
    },
    {
        // 17 chs
        .type = CLICKAREA,
        .position = {153, 325},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 18 eex
        .type = CLICKAREA,
        .position = {204, 325},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 19 clx
        .type = CLICKAREA,
        .position = {255, 325},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 20 -
        .type = CLICKAREA,
        .position = {51, 375},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 21 7
        .type = CLICKAREA,
        .position = {102, 375},
        .size = {45, 31},
        .click_event_fn = click,
    },
    {
        // 22 8
        .type = CLICKAREA,
        .position = {172, 375},
        .size = {45, 31},
        .click_event_fn = click,
    },
    {
        // 23 9
        .type = CLICKAREA,
        .position = {243, 375},
        .size = {45, 31},
        .click_event_fn = click,
    },
    {
        // 24 +
        .type = CLICKAREA,
        .position = {51, 425},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 25 4
        .type = CLICKAREA,
        .position = {102, 425},
        .size = {45, 31},
        .click_event_fn = click,
    },
    {
        // 26 5
        .type = CLICKAREA,
        .position = {172, 425},
        .size = {45, 31},
        .click_event_fn = click,
    },
    {
        // 27 6
        .type = CLICKAREA,
        .position = {243, 425},
        .size = {45, 31},
        .click_event_fn = click,
    },
    {
        // 28 x
        .type = CLICKAREA,
        .position = {51, 475},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 29 1
        .type = CLICKAREA,
        .position = {102, 475},
        .size = {45, 31},
        .click_event_fn = click,
    },
    {
        // 30 2
        .type = CLICKAREA,
        .position = {172, 475},
        .size = {45, 31},
        .click_event_fn = click,
    },
    {
        // 31 3
        .type = CLICKAREA,
        .position = {243, 475},
        .size = {45, 31},
        .click_event_fn = click,
    },
    {
        // 32 /
        .type = CLICKAREA,
        .position = {51, 525},
        .size = {34, 31},
        .click_event_fn = click,
    },
    {
        // 33 0
        .type = CLICKAREA,
        .position = {102, 525},
        .size = {45, 31},
        .click_event_fn = click,
    },
    {
        // 34 .
        .type = CLICKAREA,
        .position = {172, 525},
        .size = {45, 31},
        .click_event_fn = click,
    },
    {
        // 35 pi
        .type = CLICKAREA,
        .position = {243, 525},
        .size = {45, 31},
        .click_event_fn = click,
    },
    {
        // 36
        .type = IMAGE,
        .filename = "bg.jpg",
        .position = {0, 0},
    },
    {
        // 37
        .type = LABEL,
        .text = "-1 .234567890-20",
        .backgroundcolor = BLACK,
        .position = {64, 64},
        .textcolor = (Color){255, 112, 112, 255},
        .fontindex = 0,
        .print_event_fn = print,
    },
};

/* ----------------------------------------------------------------*/

// Application Data

/* ----------------------------------------------------------------*/

// Main

int main(void) {
  hp35_init();
  Startup();
  SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
  while (!WindowShouldClose() && !exitstate) {
    Update();
    BeginDrawing();
    Render();
    EndDrawing();
  }
  Shutdown();
  return 0;
}

/* ----------------------------------------------------------------*/

// Callback functions

static void click(int id) {
  switch (id) {
    case 0:
      exitstate = true;
      break;
    case 1:
      hp35_pow();
      break;
    case 2:
      hp35_log10();
      break;
    case 3:
      hp35_log();
      break;
    case 4:
      hp35_exp();
      break;
    case 5:
      hp35_clr();
      break;
    case 6:
      hp35_sqrt();
      break;
    case 7:
      hp35_arc();
      break;
    case 8:
      hp35_sin();
      break;
    case 9:
      hp35_cos();
      break;
    case 10:
      hp35_tan();
      break;
    case 11:
      hp35_reciprocal();
      break;
    case 12:
      hp35_exchange();
      break;
    case 13:
      hp35_rolldown();
      break;
    case 14:
      hp35_store();
      break;
    case 15:
      hp35_recall();
      break;
    case 16:
      hp35_enter();
      break;
    case 17:
      hp35_chs();
      break;
    case 18:
      hp35_eex();
      break;
    case 19:
      hp35_clx();
      break;
    case 20:
      hp35_sub();
      break;
    case 21:
      hp35_num7();
      break;
    case 22:
      hp35_num8();
      break;
    case 23:
      hp35_num9();
      break;
    case 24:
      hp35_add();
      break;
    case 25:
      hp35_num4();
      break;
    case 26:
      hp35_num5();
      break;
    case 27:
      hp35_num6();
      break;
    case 28:
      hp35_mul();
      break;
    case 29:
      hp35_num1();
      break;
    case 30:
      hp35_num2();
      break;
    case 31:
      hp35_num3();
      break;
    case 32:
      hp35_div();
      break;
    case 33:
      hp35_num0();
      break;
    case 34:
      hp35_decimal_point();
      break;
    case 35:
      hp35_pi();
      break;
    default:
      break;
  }
}

static void print(int id) {
  switch (id) {
    case 37:
      strcpy(widgets[id].text, hp35_display());
      break;
    default:
      break;
  }
}

/* ----------------------------------------------------------------*/

// Utilities

/* ----------------------------------------------------------------*/

#define MYRAYGUI_IMPLEMENTATION
#include "myraygui.h"

/* ----------------------------------------------------------------*/
