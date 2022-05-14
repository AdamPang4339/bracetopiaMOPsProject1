/// 
/// File: grid.c
/// Description: grid.c is a support file that implements functions related to 
/// creating and initializing the grid for bracetopia simulations. 
///
/// @author Adam Pang (akp4339@rit.edu)
/// @date 02/23/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // //

#define _DEFAULT_SOURCE_      // Required to use random and usleep
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "agent.h"

/**
 * random_int is a function that is called from initialize_grid to help
 * with the Fisher-Yates shuffling algorithm.
 * 
 * @param min: Minimum value of the range for the random integer
 * @param max: Maximum value of the range for the random integer
 * @return int: Integer being returned
 */
int random_int(int min, int max) {
    long int j = rand();
    int num = (j % (max - min)) + min;

    return num;
}

/**
 * initialize_grid is the main function of the grid.c file that helps with
 * initializing a randomized and shuffled grid for bracetopia simulations.
 * 
 * @param grid: Actual grid being edited
 * @param size: Dimension of the width and height of the board
 * @param vacancy: Integer percentage of the amount of vacant spots
 * @param endlines: Integer percentage of the amount of endline agents
 */
void initialize_grid(char *grid, int size, int vacancy, int endlines) {
    const int NUM_ELEMENTS = size * size;
    const char ENDLINE_CHAR = 'e';
    const char NEWLINE_CHAR = 'n';
    const char VACANT = '.';
    int num_vacant = (NUM_ELEMENTS * vacancy) / 100;
    int num_endlines = (endlines * (NUM_ELEMENTS - num_vacant)) / 100;
    
    srand(41);

    // Populate number of items and agents
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        if (num_endlines > 0) {
            grid[i] = ENDLINE_CHAR;
            num_endlines--;
        }
        else if (num_vacant > 0) {
            grid[i] = VACANT;
            num_vacant--;
        }
        else {
            grid[i] = NEWLINE_CHAR;
        }
    }

    // Modern Fisher-Yates Shuffling algorithm
    for (int i = 0; i < NUM_ELEMENTS - 2; i++) {
        // Create int j to hold random position in grid
        int j = random_int(i, NUM_ELEMENTS);
        // Swap values at i and j (random position)
        int temp = grid[i];
        grid[i] = grid[j];
        grid[j] = temp;
    }
}

/**
 * output_print_grid accepts a pointer to a particular grid in a bracetopia
 * simulation and outputs the grid as a 2d array. Used for print mode display
 * 
 * @param grid: Pointer that points to the actual 1d array grid
 * @param side_length: Integer representing the side length of the 2d square grid
 */
void output_print_grid(char *grid, int side_length) {
    // Cycle through all elements in grid
    for (int i = 0; i < side_length * side_length; i++) {
        // If multiple of side_length, output newline for 2d display
        if ((i != side_length * side_length - 1) && (i % side_length == 0)) {
            printf("\n");
        }
        // Output character from grid
        printf("%c ", grid[i]);
    }
}

/**
 * output_ngrid accepts a pointer to a particular grid in a bracetopia
 * simulation and outputs the grid as a 2d array. Used for ncurses 
 * display.
 * 
 * @param grid: Pointer that points to the actual 1d array grid
 * @param side_length: Integer representing the side length of the 2d square grid
 */
void output_ngrid(char *grid, int side_length) {
    // Cycle through all elements in grid
    for (int i = 0; i < side_length * side_length; i++) {
        // If multiple of side_length, output newline for 2d display
        if (i % side_length == 0) {
            printw("\n");
        }
        // Output character from grid
        printw("%c ", grid[i]);
    }
}

/**
 * move_grid utilizes move logic to move the first founded unhappy agents
 * and relocates them to the next vacant spot in the current grid
 * 
 * @param grid: Pointer that points to a character array
 * @param side_length: Integer representing the side length of the 2d square grid
 * @param threshold: Integer minimum required for an agent to not move
 * @param move_counter: Pointer to retrieve number of agents relocated
 */
void move_grid(char *grid, int side_length, int threshold, int *move_counter) {
    // Set up variables for counting
    const int NUM_ELEMENTS = side_length * side_length;
    // Create copy grid to hold information for comparisons
    char copy[NUM_ELEMENTS];
    strcpy(copy, grid);
    // Initialize variables
    int next_vacant = 0;
    double threshold_percent = (double) threshold / 100;
    char neighbors[NUM_ELEMENTS];
    // Reset move_counter for new move grid
    *move_counter = 0;

    // Cycle through all elements in grid
    for (int unhappy_check = 0; unhappy_check < NUM_ELEMENTS; unhappy_check++) {
        // Immediately stop for loop cycle if all vacancy has been filled
        if (next_vacant >= NUM_ELEMENTS) {
            break;
        }

        // Check index with untouched copy of grid for possible agent
        if (copy[unhappy_check] != '.') {
            // Initialize variables and information for each agent being checked
            int row = (unhappy_check / side_length);
            int col = (unhappy_check % side_length);
            double happiness = 0.0;
            double *happiness_ptr = &happiness;

            // Calculate happiness of current agent position
            get_neighbors(copy, neighbors, row, col, side_length);
            get_happiness(copy, neighbors, row, col, side_length, happiness_ptr);

            // Check for vacancy and need to relocate agent and unchanged position
            if ((next_vacant < NUM_ELEMENTS) && (happiness < threshold_percent) && 
                    (copy[unhappy_check] == grid[unhappy_check])) {
                // Find the next immediate vacant position
                while (next_vacant < NUM_ELEMENTS) {
                    if (copy[next_vacant] == '.') {
                        break;
                    }
                    else {
                        next_vacant++;
                        continue;
                    }
                }

                // If next_vacant is truly vacant, perform relocation
                // Fixes issue with next_vacant at final element
                if (copy[next_vacant] == '.') {
                    // Swap agents and vacant
                    grid[unhappy_check] = '.';
                    grid[next_vacant] = copy[unhappy_check];
                    // Increment counters
                    next_vacant++;
                    *move_counter = *move_counter + 1;
                }
            }
        }
    }
}