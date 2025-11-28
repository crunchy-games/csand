#include "csand.hh"

void HandleTools(Vector2 MousePos, int cell[GRID_WIDTH][GRID_HEIGHT]) {
  if (!IsCursorOnScreen()) {
    return;
  }

  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    tool_UseTool((int)MousePos.x / GRID_CELL_PX_SIZE, (int)MousePos.y / GRID_CELL_PX_SIZE, cell);
  } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
    tool_UseErase((int)MousePos.x / GRID_CELL_PX_SIZE, (int)MousePos.y / GRID_CELL_PX_SIZE, cell);
  }

  if (IsKeyPressed(KEY_P)) {
    tool_CurrentTool = TOOL_PENCIL;
  } else if (IsKeyPressed(KEY_E)) {
    tool_CurrentTool = TOOL_ERASER;
  } else if (IsKeyPressed(KEY_S)) {
    tool_CurrentTool = TOOL_SPRAY;
  }
}

void HandleMiscInputs() {
  if (IsKeyPressed(KEY_ONE)) {
    elem_CurrentElem = ELEM_SAND;
  } else if (IsKeyPressed(KEY_TWO)) {
    elem_CurrentElem = ELEM_WALL;
  } else if (IsKeyPressed(KEY_THREE)) {
    elem_CurrentElem = ELEM_WATER;
  } else if (IsKeyPressed(KEY_FOUR)) {
    elem_CurrentElem = ELEM_ACID;
  }
}

void HandleCommandInputs(int cell[GRID_WIDTH][GRID_HEIGHT]) {
  if (IsKeyPressed(KEY_R)) {
    for (int x = 0; x < GRID_WIDTH; x++) {
      for (int y = 0; y < GRID_HEIGHT; y++) {
        cell[x][y] = ELEM_NONE;
      }
    }
  }
}

int main() {
  InitWindow(1240, 720, "csand");
  SetTargetFPS(100); // ticks per second
  ToggleFullscreen();

  Image logo = LoadImage("assets/logo.png");
  SetWindowIcon(logo);
  UnloadImage(logo);

  SetExitKey(KEY_NULL);

  grid_Grid *grid = new grid_Grid;
  grid->setup();

  while (WindowShouldClose() == false) {
    ClearBackground(BLACK);
    grid->update();

    BeginDrawing();
      grid->draw();
      std::string message = std::to_string(GetFPS()) + " FPS";
      DrawText(message.c_str(), 5, 5, 8, WHITE);
    EndDrawing();

    // input
    Vector2 MousePos = GetMousePosition();
    HandleTools(MousePos, grid->cell);
    HandleCommandInputs(grid->cell);
    HandleMiscInputs();
  }

  delete grid; 

  CloseWindow();
  return 0;
}