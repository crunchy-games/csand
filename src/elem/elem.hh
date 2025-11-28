#pragma once
#include "../csand.hh"

#define ELEM_NONE  0   // The id for blank space, `nothing`
#define ELEM_SAND  1   // The id for, you guessed it, `sand`
#define ELEM_WALL  2   // The id for `wall`
#define ELEM_WATER 3   // The id for `water`, has similar properties to `sand`
#define ELEM_ACID  4   // The id for `acid`, an element that goes through other elements

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
  if ((y + 1) == GRID_HEIGHT) {
    cell[x][y] = ELEM_NONE;
    return;
  }
  if ((x + 1) == GRID_WIDTH) {
    cell[x][y] = ELEM_NONE;
    return;
  }
  if (x > GRID_WIDTH) {
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
  if ((y + 1) == GRID_HEIGHT) {
    cell[x][y] = ELEM_NONE;
    return;
  }
  if (x == GRID_WIDTH) {
    cell[x][y] = ELEM_NONE;
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
    if ((x + mod) > GRID_WIDTH) {
      return;
    }
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

  if ((y + 1) == GRID_HEIGHT) {
    cell[x][y] = ELEM_NONE;
    return;
  }
  if (x == GRID_WIDTH) {
    cell[x][y] = ELEM_NONE;
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
    if ((x + mod) > GRID_WIDTH) {
      return;
    }
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