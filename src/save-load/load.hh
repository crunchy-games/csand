#pragma once
#include "../csand.hh"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void load_LoadGame(string name, int grid[GRID_WIDTH][GRID_HEIGHT]) {
  string file_path = "assets/data/saves/" + name;
  ifstream data(file_path);
  string save_name;

  for (int y = 0; y < (GRID_HEIGHT + 1); y++) {
    for (int x = 0; x < GRID_WIDTH; x++) {
      if (!(data >> grid[x][y])) {
        cerr << "Error reading grid data from file: " << file_path << endl;
        return;
      }
    }
  }
}