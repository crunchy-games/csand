#pragma once
#include "../csand.hh"

#define ELEM_NONE  0   // The id for blank space, `nothing`
#define ELEM_SAND  1   // The id for, you guessed it, `sand`
#define ELEM_WALL  2   // The id for `wall`
#define ELEM_WATER 3   // The id for `water`, has similar properties to `sand`
#define ELEM_ACID  4   // The id for `acid`, an element that goes through other elements
#define ELEM_WOOD  5   // The id for `wood`, an element that is flammable
#define ELEM_FIRE  6   // The id for `fire`, an element that eats at flammable elements

#define ELEM_SAND_COLOR  YELLOW
#define ELEM_NONE_COLOR  BLACK
#define ELEM_WALL_COLOR  GRAY
#define ELEM_WATER_COLOR BLUE
#define ELEM_ACID_COLOR  GREEN

#define ELEM_WATER_DISPERSITY 4
#define ELEM_ACID_DISPERSITY  2

#define GRID_WIDTH 620
#define GRID_HEIGHT 360

int elem_CurrentElem = ELEM_SAND;

/* The function used by dust-like elements, and of course `sand` */
void elem_SandPhysics(int cell[GRID_WIDTH][GRID_HEIGHT], int x, int y) {
  // ensure that the sand doesn't fall off screen
  if ((y + 1) == GRID_HEIGHT) {
    return;
  }
  // main logic
  if (cell[x][y + 1] == ELEM_NONE) {
    cell[x][y + 1] = cell[x][y]; // place element below
    cell[x][y] = ELEM_NONE;      // remove current element
  } else if (cell[x - 1][y + 1] == ELEM_NONE) {
    cell[x - 1][y + 1] = cell[x][y];
    cell[x][y] = ELEM_NONE;
  } else if (cell[x + 1][y + 1] == ELEM_NONE) {
    cell[x + 1][y + 1] = cell[x][y];
    cell[x][y] = 0;
  }
}

void elem_WaterPhysics(int cell[GRID_WIDTH][GRID_HEIGHT], int x, int y) {
  // ensure that the water doesn't fall off screen
  if ((y + 1) == GRID_HEIGHT) {
    return;
  }
  // main logic
  if (cell[x][y + 1] == ELEM_NONE) {
    cell[x][y + 1] = cell[x][y]; // place element below
    cell[x][y] = ELEM_NONE;      // remove current element
  } else if (cell[x - 1][y + 1] == ELEM_NONE) {
    cell[x - 1][y + 1] = cell[x][y];
    cell[x][y] = ELEM_NONE;
  } else if (cell[x + 1][y + 1] == ELEM_NONE) {
    cell[x + 1][y + 1] = cell[x][y];
    cell[x][y] = 0;
  }

  // 'disperse' logic
  if (cell[x - 1][y] == ELEM_NONE && cell[x + 1][y] == ELEM_NONE) {
    int mod = GetRandomValue(-1 * ELEM_WATER_DISPERSITY, ELEM_WATER_DISPERSITY);
    if (cell[x + mod][y] == ELEM_NONE) {
      cell[x + mod][y] = cell[x][y];
      cell[x][y] = ELEM_NONE;
    }
  } else if (cell[x - 1][y] == ELEM_NONE) {
    cell[x - 1][y] = cell[x][y];
    cell[x][y] = ELEM_NONE;
  } else if (cell[x + 1][y] == ELEM_NONE) {
    cell[x + 1][y] = cell[x][y];
    cell[x][y] = ELEM_NONE;
  }
}

void elem_AcidPhysics(int cell[GRID_WIDTH][GRID_HEIGHT], int x, int y) {
  // 'disappear' logic
  float death_roll = (float)GetRandomValue(0, 100) / 100.0f;
  if (death_roll > 0.99) {
    cell[x][y] = ELEM_NONE;
    return;
  }

  // ensure that the water doesn't fall off screen
  if ((y + 1) == GRID_HEIGHT) {
    return;
  }
  // main logic
  if (cell[x][y + 1] != ELEM_ACID) {
    cell[x][y + 1] = cell[x][y]; // place element below
    cell[x][y] = ELEM_NONE;      // remove current element
  } else if (cell[x - 1][y + 1] != ELEM_ACID) {
    cell[x - 1][y + 1] = cell[x][y];
    cell[x][y] = ELEM_NONE;
  } else if (cell[x + 1][y + 1] != ELEM_ACID) {
    cell[x + 1][y + 1] = cell[x][y];
    cell[x][y] = 0;
  }

  // 'disperse' logic
  if (cell[x - 1][y] != ELEM_ACID && cell[x + 1][y] != ELEM_ACID) {
    int mod = GetRandomValue(-1 * ELEM_ACID_DISPERSITY, ELEM_ACID_DISPERSITY);
    if (cell[x + mod][y] != ELEM_ACID) {
      cell[x + mod][y] = cell[x][y];
      cell[x][y] = ELEM_NONE;
    }
  } else if (cell[x - 1][y] != ELEM_ACID) {
    cell[x - 1][y] = cell[x][y];
    cell[x][y] = ELEM_NONE;
  } else if (cell[x + 1][y] != ELEM_ACID) {
    cell[x + 1][y] = cell[x][y];
    cell[x][y] = ELEM_NONE;
  }
}

void elem_FirePhysics(int cell[GRID_WIDTH][GRID_HEIGHT], int x, int y) {
  float death_roll = (float)GetRandomValue(0, 100) / 100.0f;

  // find wood
  int mod_x = GetRandomValue(-10, 10);
  int mod_y = GetRandomValue(-10, 10);
  if ((x + mod_x) >= GRID_WIDTH) {
    return;
  }
  if (cell[x + mod_x][y + mod_y] == ELEM_NONE) {
    cell[x + mod_x][y + mod_y] = ELEM_FIRE;
    cell[x][y] = ELEM_NONE;
  // burn wood
  } else if (cell[x + mod_x][y + mod_y] == ELEM_WOOD) {
    cell[x + mod_x][y + mod_y] = ELEM_FIRE;
  }
  // burn out
  if (death_roll < 0.03) {
    cell[x + mod_x][y + mod_y] = ELEM_NONE;
    return;
  }
}