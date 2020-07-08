#ifndef SIMULATION_H
#define SIMULATION_H

#include "world_type.h"

struct er_t
{
    int error_int;
    string error_string;
};
// a type for errors, consisting a identifying number and a string 
// containing detailed information needed.

struct err_tt{
    int r,c;
    creature_t crea;
};
// a type for errors, specially for the error of creature outside world.

struct bi_creature
{
    creature_t crea_1;
    creature_t crea_2;
};
// a type for errors, specially for overlapping creatures.

void printWorld(const world_t &world);
    // REQUIRES: a initialized world
    //
    // EFFECT: print everything of the world, including all species
    // and their numbers of instruction and detailed instructions, all 
    // creatures and their species, direction and position. 
    // The function is not for determining whether the world is 
    // initialized appropraitely, but a show for all details.

bool initWorld(world_t &world, const string &speciesFile, const string
      &creaturesFile);
    // MODIFIES: world
    //
    // EFFECTS: Initialize "world" given the species summary file
    // "speciesFile" and the world description file
    // "creaturesFile". This initializes all the components of
    // "world". Returns true if initialization is successful.

void simulateCreature(creature_t &creature, grid_t &grid, bool verbose);
    // REQUIRES: creature is inside the grid.
    //
    // MODIFIES: creature, grid, cout.
    //
    // EFFECTS: Simulate one turn of "creature" and update the creature,
    // the infected creature, and the grid if necessary.
    // The creature programID is always updated. The function
    // also prints to the stdout the procedure. If verbose is
    // true, it prints more information.

void printGrid(const grid_t &grid);
    // MODIFIES: cout.
    //
    // EFFECTS: print a grid representation of the creature world.

point_t adjacentPoint(point_t pt, direction_t dir);
    // EFFECTS: Returns a point that results from moving one square
    // in the direction "dir" from the point "pt".

direction_t leftFrom(direction_t dir);
    // EFFECTS: Returns the direction that results from turning
    // left from the given direction "dir".

direction_t rightFrom(direction_t dir);
    // EFFECTS: Returns the direction that results from turning
    // right from the given direction "dir".

instruction_t getInstruction(const creature_t &creature);
    // EFFECTS: Returns the current instruction of "creature".

creature_t *getCreature(const grid_t &grid, point_t location);
    // REQUIRES: location is inside the grid.
    //
    // EFFECTS: Returns a pointer to the creature at "location" in "grid".

string crea_call(const creature_t &creature);
    // EFFECTS: return a string in the form of (<SPECIES> <DIR> <R> <C>).

bool is_inside(point_t &point, grid_t &grid);
    // EFFECTS: return if the point inside the grid.

void index_change(creature_t &creature, bool way);
    // EFFECTS: change the creature's index of instruction if applicable.
    // The boolean way to decide how to change: if true, then change to the 
    // index following the instruction; if false, then change to the next 
    // instruction.

void printOp(const creature_t &creature, const int op_num);
    // EFFECTS: print the instruction of the creature has taken. op_num is the 
    // index for the instruction in the creature's species.

void pointSwap(grid_t &grid, creature_t &creature, point_t p1);
    // EFFECTS: For the operation of hop, where creature hop from point p2 
    // to point p1, that is, to swap the value of p1 and p2 in grid.

#endif