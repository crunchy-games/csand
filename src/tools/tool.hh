#pragma once
#include "../csand.hh"

#define TOOL_PENCIL 0
#define TOOL_ERASER 1
#define TOOL_SPRAY  2

int tool_CurrentTool = TOOL_PENCIL;

void tool_UsePencil(int x, int y, int cell[GRID_WIDTH][GRID_HEIGHT]) {
  if (x > GRID_WIDTH) {
    return;
  } else if (y > GRID_HEIGHT) {
    return;
  }
  cell[x][y] = elem_CurrentElem;
}

void tool_UseErase(int x, int y, int cell[GRID_WIDTH][GRID_HEIGHT]) {
  if (x > GRID_WIDTH) {
    return;
  } else if (y > GRID_HEIGHT) {
    return;
  }
  cell[x][y] = ELEM_NONE;
}

void tool_UseSpray(int x, int y, int cell[GRID_WIDTH][GRID_HEIGHT]) {
  if ((x + 5) > GRID_WIDTH) {
    return;
  } else if ((y + 5) > GRID_HEIGHT) {
    return;
  }
  int x_ran = GetRandomValue(-5, 5);
  int y_ran = GetRandomValue(-5, 5);
  cell[x + x_ran][y + y_ran] = elem_CurrentElem;
}

void tool_UseTool(int x, int y, int cell[GRID_WIDTH][GRID_HEIGHT]) {
  switch(tool_CurrentTool) {
    case(TOOL_PENCIL):
      tool_UsePencil(x, y, cell);
      break;
    case(TOOL_ERASER):
      tool_UseErase(x, y, cell);
      break;
    case(TOOL_SPRAY):
      tool_UseSpray(x, y, cell);
  }
}
