#pragma once
#include "../csand.hh"
#include "../elem/elem.hh"

#define GRID_WIDTH 620
#define GRID_HEIGHT 360
#define GRID_CELL_PX_SIZE 2

typedef struct grid_Grid {
  int cell[GRID_WIDTH][GRID_HEIGHT]; // The grid itself. Represented using `cell[x][y]` for simplicity.

  void setup() {
    for (int x = 0; x < GRID_WIDTH; x++) {
      for (int y = 0; y < GRID_HEIGHT; y++) {
        cell[x][y] = ELEM_NONE;
      }
    }
  };

  void draw() {
    for (int x = 0; x < GRID_WIDTH; x++) {
      for (int y = 0; y < GRID_HEIGHT; y++) {
        if (cell[x][y] != ELEM_NONE) {
          DrawRectangle(GRID_CELL_PX_SIZE * x, GRID_CELL_PX_SIZE * y, GRID_CELL_PX_SIZE, GRID_CELL_PX_SIZE, get_color(cell[x][y]));
        }
      }
    }
  };

  void check_elem(int x, int y) {
    switch(cell[x][y]) {
      case(ELEM_NONE):
        return;
      case(ELEM_SAND):
        elem_SandPhysics(cell, x, y);
        break;
      case(ELEM_WALL):
        return;
      case(ELEM_WATER):
        elem_WaterPhysics(cell, x, y);
        break;
      case(ELEM_ACID):
        elem_AcidPhysics(cell, x, y);
        break;
    }
  }

  void update() {
    for (int x = 0; x < GRID_WIDTH; x++) {
      for (int y = GRID_HEIGHT; y >= 0; y--) {
        check_elem(x, y);
      }
    }
  }

  Color get_color(int ELEM_TYPE) {
    switch(ELEM_TYPE) {
      case(ELEM_NONE):
        return ELEM_NONE_COLOR;
      case(ELEM_SAND):
        return ELEM_SAND_COLOR;
      case(ELEM_WALL):
        return ELEM_WALL_COLOR;
      case(ELEM_WATER):
        return ELEM_WATER_COLOR;
      case(ELEM_ACID):
        return ELEM_ACID_COLOR;
    }
  };
} grid_Grid;