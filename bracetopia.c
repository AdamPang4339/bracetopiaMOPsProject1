/// 
/// File: bracetopia.c
/// Description: bracetopia.c is the main driving file that simulates the fight 
/// between two opposing sides of supporters for newline or endline 
/// brace formatting.
///
/// @author Adam Pang (akp4339@rit.edu)
/// @date 02/22/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // //

#define _DEFAULT_SOURCE
#include <ncurses.h>       // Required for curses functions
#include <unistd.h>        // Required for usleep
#include <stdio.h>         // For macros and standard input/output
#include <stdlib.h>        // For other macros and standard library functions
#include <time.h>          // For randomized time
#include <getopt.h>        // Required to process for "-flag" command 
                           // line arguments
#include "grid.h"          // For initializing grid for simulation
#include "agent.h"         // For agent information 

/**
 * Helper method usage_help() displays the proper usage command example for
 * calling the bracetopia simulation.
 * 
 * @param void: Accepts no parameters
 * @return void: Returns nothing
 */
void usage_help() {
    fprintf( stderr, "usage:\nbracetopia [-h] [-t N] [-c N] [-d dim] [-s %%str] [-v %%vac] [-e %%end]\n" );
}

/**
 * Helper method display_commands() displays the complete list of possible
 * options to provide when calling bracetopia simulations. Mainly used for
 * displaying the help option.
 * 
 * @param void: Accepts no parameters
 * @return void: Returns nothing
 */
void display_commands() {
    printf("Option      Default   Example   Description\n");
    printf("'-h'        NA        -h        print this usage message.\n");
    printf("'-t N'      900000    -t 5000   microseconds cycle delay.\n");
    printf("'-c N'      NA        -c4       count cycle maximum value.\n");
    printf("'-d dim'    15        -d 7      width and height dimension.\n");
    printf("'-s %%str'   50        -s 30     strength of preference.\n");
    printf("'-v %%vac'   20        -v30      percent vacancies.\n");
    printf("'-e %%endl'  60        -e75      percent Endline braces. Others want Newline.\n");
}

/**
 * Main function to be called when a bracetopia simulation is run.
 *
 * @param argc: Number of arguments provided in command line (Including file name)
 * @param argv: Array of individual arguments separated by spaces (Including file name)
 * @return int: Returns error code; 0 if EXIT_SUCCESS, 1 if EXIT_FAILURE, or 2
 */
int main(int argc, char * argv[]) {
    // Initialize + default variables
    int side_length = 15;
    int vacancy = 20;
    int endlines = 60;
    int count = -1;
    int strength = 50;
    int time = 900000;
    int temp;

    // Initialize other variables for output
    int cycle_counter = 0;
    int move_counter = 0;
    int *move_counter_ptr = &move_counter;
    double team_happiness = 0.00;
    double *team_happiness_ptr = &team_happiness;
    int opt;

    // Parse command line arguments for relevant grid data
    while ((opt = getopt(argc, argv, "ht:c:d:s:v:e:")) != -1) {
        switch (opt) {
        case 'h':
            usage_help();
            display_commands();
            return (EXIT_SUCCESS);
            break;
        case 't':
            temp = (int) strtol(optarg, NULL, 10);
            if (temp > 0) {
                time = temp;
            }
            break;
        case 'c':
            count = (int) strtol(optarg, NULL, 10);
            if (count < 0) {
                fprintf(stderr, "count (%i) must be a non-negative integer\n", count);
                usage_help();
                return (1 + EXIT_FAILURE);                
            }
            break;
        case 'd':
            side_length = (int) strtol(optarg, NULL, 10);
            if (side_length < 5 || side_length > 39) {
                fprintf(stderr, "dimension (%i) must be a value in [5...39]\n", side_length);
                usage_help();
                return (1 + EXIT_FAILURE);                
            }
            break;
        case 's':
            strength = (int) strtol(optarg, NULL, 10);
            if (strength < 1 || strength > 99) {
                fprintf(stderr, "preference strength (%i) must be a value in [1...99]\n", strength);
                usage_help();
                return (1 + EXIT_FAILURE);                
            }
            break;
        case 'v':
            vacancy = (int) strtol(optarg, NULL, 10);
            if (vacancy < 1 || vacancy > 99) {
                fprintf(stderr, "vacancy (%i) must be a value in [1...99]\n", vacancy);
                usage_help();
                return (1 + EXIT_FAILURE);                
            }
            break;
        case 'e':
            endlines = (int) strtol(optarg, NULL, 10);
            if (endlines < 1 || endlines > 99) {
                fprintf(stderr, "endline proportion (%i) must be a value in [1...99]\n", endlines);
                usage_help();
                return (1 + EXIT_FAILURE);                
            }
            break;
        default:
            usage_help();
            return (EXIT_FAILURE);
        }
    }

    // Initialize grid data
    char grid[side_length * side_length];
    initialize_grid(grid, side_length, vacancy, endlines);

    // Identify count option or curse option
    if (count != -1) {
        for (int i = -1; i < count; i++) {
            // Calculate information for next grid
            calculate_team_happiness(grid, side_length, team_happiness_ptr);

            // Display current board
            output_print_grid(grid, side_length);

            // Display cycle information
            printf("\ncycle: %i\n", (i + 1));
            printf("moves this cycle: %d\n", *move_counter_ptr);
            printf("teams' \"happiness\": %f\n", *team_happiness_ptr);
            printf("dim: %d, %%strength of preference:  %d%%, %%vacancy:  %d%%, %%end:  %d%%", side_length, strength, vacancy, endlines);

            // Update grid and team happiness by moving agents
            move_grid(grid, side_length, strength, move_counter_ptr);
        }

        printf("\n");
    }
    else {
        // Initialize screen from ncurses
        initscr();
        refresh();

        // Cycle endlessly through generations
        while(1) {
            move(0, 0);
            
            // Display current board
            output_ngrid(grid, side_length);

            // Display cycle information
            mvprintw(side_length + 1, 0, "cycle: %d\n", cycle_counter);
            mvprintw(side_length + 2, 0, "moves this cycle: %d\n", *move_counter_ptr);
            mvprintw(side_length + 3, 0, "teams' \"happiness\": %f\n", *team_happiness_ptr);
            mvprintw(side_length + 4, 0, "dim: %d, %%strength of preference:  %d%%, %%vacancy:  %d%%, %%end:  %d%%\n", side_length, strength, vacancy, endlines);
            mvprintw(side_length + 5, 0, "Use Control-C to quit.\n");
            cycle_counter++;
            
            // Update and refresh board per new generation
            move(side_length, 0);
            refresh();

            // Update grid and team happiness by moving agents
            move_grid(grid, side_length, strength, move_counter_ptr);
            calculate_team_happiness(grid, side_length, team_happiness_ptr);

            // Delay cycles with sleep time
            usleep(time);
        }

        endwin();
    }

    return(EXIT_SUCCESS);
}