///
/// File: grid.h
/// Description: grid.h is the interface for functions and data related to each agent 
/// in a bracetopia simulation
///
/// @author Adam Pang (akp4339) 
/// @date 02/23/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef AGENT_H
#define AGENT_H

/**
 * get_neighbors accepts a character pointer referring to a grid and populates
 * the given neighbors character pointer with the 8 neighbors directly next to 
 * the current agent in row, col
 * 
 * @param grid: Array of characters through pointer
 * @param neighbors: Array of characters through pointer
 * @param row: Integer representing the col of current agent
 * @param col: Integer representing the row of current agent
 * @param side_length: Integer representing the side length of the square grid
 */
void get_neighbors(char *grid, char *neighbors, int row, int col, int side_length);

/**
 * get_happiness changes the value of the happiness double pointer provided
 * with the calculated value of the agent's happiness at row, col. Requires 
 * neighbors array character pointer to be populated with get_neighbors() to 
 * properly work.
 * 
 * @param grid: Array of characters through pointer
 * @param neighbors: Array of characters through pointer
 * @param row: Integer representing the col of current agent
 * @param col: Integer representing the row of current agent
 * @param side_length: Integer representing the side length of the square grid
 * @param happiness: Double pointer pointing to the location of the happiness value
 */
void get_happiness(char *grid, char *neighbors, int row, int col, int side_length, double *happiness);

/**
 * calculate_team_happiness calculates the team happiness of a particular grid within a
 * bracetopia simulation. The calculated value is passed back into the team_happiness
 * pointer.
 * 
 * @param grid: Pointer to the current bracetopia simulation's grid of agents
 * @param side_length: Integer representing the width/height of the grid
 * @param team_happiness: Average happiness of the entire board's agents
 */
void calculate_team_happiness(char *grid, int side_length, double *team_happiness);

#endif // AGENT_H