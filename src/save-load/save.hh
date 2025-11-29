#pragma once
#include "../csand.hh"
#include "string"
#include "iostream"
#include "fstream"

using namespace std;

// save a `.save` file with specific parameters
void save_SaveGame(string name, int grid[GRID_WIDTH][GRID_HEIGHT]) {
  string file_name = "assets/data/saves/" + name;
  ofstream file(file_name);

  for (int y = 0; y < GRID_HEIGHT; y++) {
    if (y > 0) {file << "\n";}
    for (int x = 0; x < GRID_WIDTH; x++) {
      file << grid[x][y];
      if (x < (GRID_WIDTH - 1)) {file << " ";}
    }
  }

  file.close();
}