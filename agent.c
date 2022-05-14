/// 
/// File: agent.c
/// Description: agent.c is a support file that implements functions and data
/// related to each individual agent within a bracetopia simulation
///
/// @author Adam Pang (akp4339@rit.edu)
/// @date 02/23/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // //

#define _DEFAULT_SOURCE_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/**
 * get_neighbors will accept a pointer to an empty array of neighbors and populate
 * the given array with the neighbors of the given position from row and column.
 * 
 * @param grid: Pointer to the current bracetopia simulation's grid of agents
 * @param neighbors: Pointer to the array of neighbors of given row and col
 * @param row: Integer representing the row of the 2d grid
 * @param col: Integer representing the column of the 2d grid
 * @param side_length: Integer representing the width/height of the grid
 */
void get_neighbors(char *grid, char *neighbors, int row, int col, int side_length) {
    // Get main 8 directions for math
    int directions[8][2] = { {-1, -1}, {-1, 0}, {-1, 1},     // Coords for neighbors on the left
                                {0, -1}, {0, 1},             // Coords for neighbors above and below
                                {1, -1}, {1, 0}, {1, 1}      // Coords for neighbors on the right
                           };
    
    // Loop through all 8 cardinal directions
    for (int i = 0; i < 8; i++) {
        int neighbor_row = row + directions[i][0]; // Add current row and all 8 X-coordinate points
        int neighbor_col = col + directions[i][1]; // Add current col and all 8 Y-coordinate points

        // Check for valid neighbor
        if (neighbor_row >= 0 && neighbor_row < side_length) {
            if (neighbor_col >= 0 && neighbor_col < side_length) {
                // If neighbor coordinates are valid, add neighbor character
                neighbors[i] = grid[(neighbor_row * side_length) + neighbor_col];
            }
            else {
                neighbors[i] = '.';
            }
        }
        else {
            neighbors[i] = '.';
        }
    }
}

/**
 * get_happiness calculates the happiness of a given agent and places the value into
 * the location that the happiness pointer parameter points to
 * 
 * @param grid: Pointer to the current bracetopia simulation's grid of agents
 * @param neighbors: Pointer to the array of neighbors of given row and col
 * @param row: Integer representing the row of the 2d grid
 * @param col: Integer representing the column of the 2d grid
 * @param side_length: Integer representing the width/height of the grid
 * @param happiness: Double pointer to happiness of agent at row, col
 */
void get_happiness(char *grid, char *neighbors, int row, int col, int side_length, double *happiness) {
    // Compute location of current agent within the 1d array
    int current_agent = (row * side_length) + col;
    // Initialize variables for calculating happiness
    int neighbor_count = 8;
    int similar_pref = 0;

    // Cycle through all neighbors of current agent
    if (grid[current_agent] != '.') {
        for (int neighbor = 0; neighbor < 8; neighbor++) {
            // Fix neighbor count
            if (neighbors[neighbor] == '.') {
                neighbor_count--;
            }
            // Count nearby similar preference neighbors
            if (neighbors[neighbor] == grid[current_agent]) {
                similar_pref++;
            }
        }
    }    

    // Check for divide by 0 error
    if (neighbor_count != 0) {
        *happiness = (double) similar_pref / neighbor_count;
    }
    else {
        *happiness = 0;
    }
}

/**
 * calculate_team_happiness calculates the team happiness of a particular grid within a
 * bracetopia simulation. The calculated value is passed back into the team_happiness
 * pointer.
 * 
 * @param grid: Pointer to the current bracetopia simulation's grid of agents
 * @param side_length: Integer representing the width/height of the grid
 * @param team_happiness: Average happiness of the entire board's agents
 */
void calculate_team_happiness(char *grid, int side_length, double *team_happiness) {
    // Initialize other relevant data to calculate happiness of grid
    char neighbors[8];
    double local_happiness = 0;
    double *happiness_ptr = &local_happiness;
    // Keep track of total happiness for team happiness calculations
    double total_happiness = 0.0;
    int total_agents = 0;

    for (int row = 0; row < side_length; row++) {
        for (int col = 0; col < side_length; col++) {
            // Compute location of current agent within the 1d array
            int current_agent = (row * side_length) + col;

            // Check for valid agent
            if (grid[current_agent] == 'n' || grid[current_agent] == 'e') {
                // Calculate individual local happinesses
                get_neighbors(grid, neighbors, row, col, side_length);
                get_happiness(grid, neighbors, row, col, side_length, happiness_ptr);

                // Add local happiness to counters to calculate team happiness
                total_happiness += *happiness_ptr;
                total_agents++;
            }
        }
    }

    // Alter pointer at team_happiness to store team happiness for display
    *team_happiness = total_happiness / total_agents;
}