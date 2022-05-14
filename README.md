# bracetopiaMOPsProject1
A simulation project that displays a fight between two opposing "brace coding style" teams, newline and endlines. Uses the ncurses environment in C to display.

## Project Files
- **Bracetopia:** Main driving file that simulates the fight between two opposing sides of supporters for newline or endline brace formatting.
- Agent: Implements functions and data related to each individual agent within a bracetopia simulation. 
- Grid: Implements functions related to creating and initializing the grid for bracetopia simulations. 
- Use_GetOpt: File to parse command line arguments and accept arguments with specific command line flags.

## Command Line Usage
`Usage: bracetopia [-h] [-t N] [-c N] [-d dim] [-s %%str] [-v %%vac] [-e %%end]`
```
Option        Default     Example     Description
'-h'          NA          -h          print this usage message.
'-t N'        900000      -t 5000     microseconds cycle delay.
'-c N'        NA          -c4         count cycle maximum value.
'-d dim'      15          -d 7        width and height dimension.
'-s %%str'    50          -s 30       strength of preference.
'-v %%vac'    20          -v30        percent vacancies.
'-e %%endl'   60          -e75        percent Endline braces. Others want Newline.
```
