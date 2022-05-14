///
/// File: grid.h
/// Description: grid.h is the interface for functions in a bracetopia simulation that uses
/// a character grid in the form of a 2d array
///
/// @author Adam Pang (akp4339) 
/// @date 02/23/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef GRID_H
#define GRID_H

/**
 * random_int is a static function that is called from initialize_grid to help
 * with the Fisher-Yates shuffling algorithm.
 * 
 * @param min: Minimum value of the range for the random integer
 * @param max: Maximum value of the range for the random integer
 * @return int: Random integer being returned
 */
int random_int(int min, int max);

/**
 * initialize_grid initializes a bracetopia simulation board given a particular 
 * dimension size, vacancy percentage, and percentage of endlines.
 * 
 * @param grid: Array of characters
 * @param size: Integer representing the width/height of the grid
 * @param vacancy: Integer percentage of amount of vacant cells
 * @param endlines: Integer percentage of endline preferring agents
 */
void initialize_grid(char *grid, int size, int vacancy, int endlines);

/**
 * output_print_grid accepts a pointer to a particular character array and outputs 
 * its contents in the form of a 2d array (assuming square). Used for print
 * mode display
 * 
 * @param grid: Pointer that points to a character array
 * @param side_length: Integer of width/height for the 2d display
 */
void output_print_grid(char *grid, int side_length);


/**
 * output_ngrid accepts a pointer to a particular character array and outputs 
 * its contents in the form of a 2d array (assuming square). Used for ncurses
 * display.
 * 
 * @param grid: Pointer that points to a character array
 * @param side_length: Integer of width/height for the 2d display
 */
void output_ngrid(char *grid, int side_length);

/**
 * move_grid utilizes move logic to move the first founded unhappy agents
 * and relocates them to the next vacant spot in the current grid
 * 
 * @param grid: Pointer that points to a character array
 * @param side_length: Integer representing the side length of the 2d square grid
 * @param threshold: Integer minimum required for an agent to not move
 * @param move_counter: Pointer to retrieve number of agents relocated
 */
void move_grid(char *grid, int side_length, int threshold, int *move_counter);

#endif // GRID_H