//
// Created by dalia on 11/24/2024.
//

#ifndef SNAKES_AND_LADDERS_H
#define SNAKES_AND_LADDERS_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include "DEQ.h"

class snakes_and_ladders {

private:

public:
  int board[101];
  int parent[101];
  bool is_visited[101]; // BFS tracking
  int snakes[10][2];      // Array to store snake positions (start, end)
  int ladders[10][2];     // Array to store ladder positions (start, end)
  int snake_count;        // Count of snakes
  int ladder_count;       // Count of ladders

  snakes_and_ladders();
  ~snakes_and_ladders();
  //snakes_and_ladders(int snakes, int ladders);
  void load_from_file(const char* filename);
  int get_snakes();
  int get_ladders();
  bool is_valid_position(int start, int end);  // Validate snake/ladder positions
  int get_target_position(int position);       // Get target position (snake/ladder effect)
  void mark_visited(int position);             // Mark a position as visited
  bool is_already_visited(int position);
  void print_board();
  void reset_board();
  void simulateGame();
  int bfs(int start, int end);
  void printPath(int parent[], int start, int end);
  void reconstructPath(int parent[], int start, int end);
};



#endif //SNAKES_AND_LADDERS_H
