//
// Created by dalia on 11/24/2024.
//
#include "snakes_and_ladders.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "DEQ.h"
using namespace std;

snakes_and_ladders::snakes_and_ladders() {
    reset_board();
    for (int i = 0; i <= 100; i++) {
        is_visited[i] = false; // Initialize all positions as unvisited
    }
    snake_count = 0;
    ladder_count = 0;
}

snakes_and_ladders::~snakes_and_ladders() {}

//snakes_and_ladders::snakes_and_ladders(int snakes, int ladders) {
//    for (int i = 0; i <= 100; i++) {
//        board[i] = -1;
//    }
//    // You can add logic to randomly place snakes and ladders
//}

void snakes_and_ladders::load_from_file(const char* filename) {
    ifstream file(filename);
    cout << filename << endl;
    if (!file) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    int start, end;
    while (file >> start >> end) {
        if (is_valid_position(start, end)) {
            board[start] = end; // Add snake or ladder to the board

            if (start > end) { // It's a snake
                snakes[snake_count][0] = start;
                snakes[snake_count][1] = end;
                snake_count++;
            } else { // It's a ladder
                ladders[ladder_count][0] = start;
                ladders[ladder_count][1] = end;
                ladder_count++;
            }
        } else {
            cerr << "Invalid position in file: " << start << " -> " << end << endl;
        }
    }

    file.close();
}

int snakes_and_ladders::get_snakes() {
    return snake_count; // Return the number of snakes
}

int snakes_and_ladders::get_ladders() {
    return ladder_count;
}

bool snakes_and_ladders::is_valid_position(int start, int end) {
    // Positions must be within the board range
    if (start < 1 || start > 100 || end < 1 || end > 100) {
        return false;
    }
    // Snakes: start > end, Ladders: start < end
    return true;
}

//void snakes_and_ladders::save_to_file(const char* filename) {
//  ofstream file(filename);
//  if (!file) {
//    cerr << "Error opening file: " << filename << endl;
//    return;
//  }
//  for (int i = 0; i < board.size(); i++) {
//    file << board[i];
//    if (i != board.size() - 1) {
//      file << " ";
//    } else {
//    file << "\n";
//    }
//
//  }
//  file.close();
//}

int snakes_and_ladders::get_target_position(int position) {
    if (position >= 1 && position <= 100 && board[position] != -1) {
        return board[position];
    }
    return position; // No snake or ladder
}

void snakes_and_ladders::mark_visited(int position) {
    if (position >= 1 && position <= 100) {
        is_visited[position] = true;
    }
}


bool snakes_and_ladders::is_already_visited(int position) {
    return position >= 1 && position <= 100 && is_visited[position];
}

// Print the board
void snakes_and_ladders::print_board() {
    for (int i = 1; i <= 100; i++) {
        if (board[i] != -1) {
            if (i > board[i]) {
                cout << "Cell " << i << ": Snake to " << board[i] << endl;
            } else {
                cout << "Cell " << i << ": Ladder to " << board[i] << endl;
            }
        }
    }

    cout << "***********************************************************" << endl;

    cout << "Snakes:--------------------------\n";
    for (int i = 0; i < snake_count; i++) {
        cout << "Start: " << snakes[i][0] << ", End: " << snakes[i][1] << endl;
    }

    cout << "Ladders:-------------------------\n";
    for (int i = 0; i < ladder_count; i++) {
        cout << "Start: " << ladders[i][0] << ", End: " << ladders[i][1] << endl;
    }
}

void snakes_and_ladders::reset_board() {
    for (int i = 0; i <= 100; i++) {
        board[i] = -1; // No snakes or ladders by default
    }
}

// void snakes_and_ladders::simulateGame() {
//
//     int position = 1; // Starting position
//     int rolls = 0;    // Counter for dice rolls
//     char choice;
//
//     cout << "Do you want manual dice rolls? (y/n): ";
//     cin >> choice;
//
//     srand(time(0)); // Seed for random number generation
//
//     cout << "Game Start!\n";
//     while (position < 100) {
//         int diceRoll;
//         if (choice == 'y' || choice == 'Y') {
//             cout << "Enter dice roll (1-6): ";
//             cin >> diceRoll;
//             if (diceRoll < 1 || diceRoll > 6) {
//                 cout << "Invalid roll. Try again.\n";
//                 continue;
//             }
//         } else {
//             diceRoll = rand() % 6 + 1; // Random dice roll between 1 and 6
//         }
//
//         rolls++;
//         cout << "Rolled " << diceRoll << ": ";
//
//         // Move the player
//         position += diceRoll;
//
//         if (position > 100) {
//             position -= diceRoll;   // Ensure player doesn't go beyond 100
//             cout << "Overshot! Stay at " << position << endl;
//             continue;
//         }
//
//         cout << "Moved to " << position;
//
//         // Check for snakes or ladders
//         if (board[position] != -1) {
//             if (board[position] > position)
//                 cout << endl << "Hit a ladder! Climbed to " << board[position];
//             else
//                 cout << endl << "Bitten by a snake! Slid to " << board[position];
//             position = board[position];
//         }
//
//         cout << endl;
//     }
//
//     cout << "Game Over! " << "************************************" << endl;
//     cout << "Reached cell 100 in " << rolls << " rolls.";
// }

void snakes_and_ladders::simulateGame() {
    int numPlayers;
    cout << "Enter the number of players (2 or more): ";
    cin >> numPlayers;

    if (numPlayers < 2) {
        cout << "Number of players must be 2 or more." << endl;
        return;
    }

    int* positions = new int[numPlayers]; // Array to track each player's position
    int* rolls = new int[numPlayers];     // Array to track the number of rolls for each player
    for (int i = 0; i < numPlayers; i++) {
        positions[i] = 1; // Initialize all players at starting position
        rolls[i] = 0;
    }

    char choice;
    cout << "Do you want manual dice rolls? (y/n): ";
    cin >> choice;

    srand(time(0)); // Seed for random number generation

    cout << "Game Start! ***********************************************\n";
    bool gameOver = false;
    int currentPlayer = 0; // Index to track the current player

    while (!gameOver) {
        int diceRoll;
        cout << "\nPlayer " << (currentPlayer + 1) << "'s turn." << endl;

        if (choice == 'y' || choice == 'Y') {
            cout << "Enter dice roll for Player " << (currentPlayer + 1) << " (1-6): ";
            cin >> diceRoll;
            if (diceRoll < 1 || diceRoll > 6) {
                cout << "Invalid roll. Try again.\n";
                continue;
            }
        } else {
            diceRoll = rand() % 6 + 1; // Random dice roll between 1 and 6
            cout << "Player " << (currentPlayer + 1) << " rolled " << diceRoll << ": ";
        }

        rolls[currentPlayer]++;
        // Move the player
        positions[currentPlayer] += diceRoll;

        if (positions[currentPlayer] > 100) {
            positions[currentPlayer] -= diceRoll;   // Ensure player doesn't go beyond 100
            cout << "Overshot! Stay at " << positions[currentPlayer] << endl;
        } else {
            cout << "Moved to " << positions[currentPlayer];

            // Check for snakes or ladders
            if (board[positions[currentPlayer]] != -1) {
                if (board[positions[currentPlayer]] > positions[currentPlayer])
                    cout << "\nHit a ladder! Climbed to " << board[positions[currentPlayer]];
                else
                    cout << "\nBitten by a snake! Slid to " << board[positions[currentPlayer]];
                positions[currentPlayer] = board[positions[currentPlayer]];
            }
            cout << endl;

            // Check if the player has won
            if (positions[currentPlayer] == 100) {
                cout << "\nPlayer " << (currentPlayer + 1) << " wins the game!" << endl;
                cout << "Reached cell 100 in " << rolls[currentPlayer] << " rolls." << endl;
                gameOver = true;
                break;
            }

            // **Place the code snippet here to display current positions after each player's turn**
            cout << "\nCurrent Positions:\n";
            for (int i = 0; i < numPlayers; i++) {
                cout << "Player " << (i + 1) << ": " << positions[i] << endl;
            }
        }

        // Move to the next player
        currentPlayer = (currentPlayer + 1) % numPlayers;

        // // **Place the code snippet here to display current positions after each round**
        // if (currentPlayer == 0) {
        //     // After all players have taken their turn
        //     cout << "\nCurrent Positions:\n";
        //     for (int i = 0; i < numPlayers; i++) {
        //         cout << "Player " << (i + 1) << ": " << positions[i] << endl;
        //     }
        // }
    }

    delete[] positions;
    delete[] rolls;
}

// BFS to find the shortest path
int snakes_and_ladders::bfs(int start, int end) {
    DEQ<pair<int, int>> queue; // DEQ to store {current_cell, dice_rolls}
    //bool visited[101] = {false}; // Visited array
    //int parent[101];             // To track the path

    // Initialize parent array
    for (int i = 0; i <= 1000; i++) {
        parent[i] = -1;
    }

    // Push the starting cell into the queue
    queue.Add_Rear({start, 0});
    is_visited[start] = true;

    while (!queue.DEQisEmpty()) {
        // Get the current cell and dice rolls from the front of the queue
        pair<int, int> current = queue.Remove_Front();
        int current_cell = current.first;
        int dice_rolls = current.second;

        // If we reached the end cell
        if (current_cell == end) {
            printPath(parent, start, end); // Print the path
            return dice_rolls;            // Return the number of dice rolls
        }

        // Simulate dice rolls
        for (int roll = 1; roll <= 6; roll++) {
            int next_cell = current_cell + roll;
            if (next_cell > 100) continue; // Skip cells beyond 100

            // Check for snakes or ladders
            if (board[next_cell] != -1) {
                next_cell = board[next_cell];
            }

            // Visit if not already visited
            if (!is_visited[next_cell]) {
                is_visited[next_cell] = true;
                queue.Add_Rear({next_cell, dice_rolls + 1});
                parent[next_cell] = current_cell; // Track the path
            }
        }
    }

    return -1; // If no path is found
}

// Print the reconstructed path
void snakes_and_ladders::printPath(int parent[], int start, int end) {
    DEQ<int> path;
    for (int at = end; at != -1; at = parent[at]) {
        path.Add_Front(at);  // Add elements to the front to reverse the order
    }

    cout << endl << "Path: ";
    while (!path.DEQisEmpty()) {
        int cell = path.Remove_Front();  // Remove elements from the front
        cout << cell << " ";
    }
    cout << endl;
}

void snakes_and_ladders::reconstructPath(int parent[], int start, int end) {
    int *path = new int[1000];
    int k = 0;

    for (int v = end; v != -1; v = parent[v]) {
        path[k++] = v;
    }

    if (k == 0 || path[k - 1] != start) {
        cout << "No solution found." << endl;
        delete[] path;
        return;
    }

    cout << "Path: ";
    for (int i = k - 1; i >= 0; --i) {
        cout << path[i];
        if (i > 0) {
            cout << " -> ";
        }
    }
    cout << endl;
    delete[]path;
}