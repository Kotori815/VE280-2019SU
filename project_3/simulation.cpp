#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include "simulation.h"

using namespace std;

bool initWorld(world_t &world, const string &speciesFile, const string &creaturesFile){

    string input; // string to get lines from files
    string helperstring;

    istringstream ss; // the input stringstream for lines

    ifstream species_file;
    species_file.open(speciesFile);
    if (!species_file) {
        er_t error = {3,speciesFile};
        throw error;
    }

    string path;
    getline(species_file, input);
    path.append(input + "/");
    // path is that of the species instruction files

    unsigned int temp1 = 0; // counter for species number

    // ===============init species===============

    while (getline(species_file, input)){

        ifstream op_file;
        op_file.open(path + input);
		op_file.close();
        if (!op_file) {
            er_t error = {3,path + input};
            throw error;
        } // error: file not found, throw the file name

        world.species[temp1].name = input;

        unsigned int temp2 = 0; // counter for instruction number/ program size

        while (getline(op_file, input)){

            if (input == "") break; // if reaching end of file then quit loop

            ss.str(input);
            ss >> helperstring;
            bool is_found = 0; // indicating whether operation is found in opName

            // read the first word of each line as operation name
            // if op isn't one of if****, the read the int following
            for (int i = 0; i < 9; i++){
                if (helperstring == opName[i]){
                    world.species[temp1].program[temp2].op = opcode_t(i);
                    if (i >= 4) {
                        ss >> world.species[temp1].program[temp2].address;
                    }
                    is_found = 1;
                }
            }                

            if (!is_found) {er_t error = {6, helperstring}; op_file.close(); throw error;}
            //error: op not found, through the invalid op name

            ss.clear();

            temp2 ++;
            if (temp2 > MAXPROGRAM){er_t error = {5, world.species[temp1].name}; op_file.close(); throw error;}
            // error: too many instructions, throw as soon as temp2 surpass limit
        }


        world.species[temp1].programSize = temp2;
        temp1 ++;
        if (temp1 > MAXSPECIES) {op_file.close(); throw 4;} // error: too many species
        op_file.close();


    }

    world.numSpecies = temp1;
    species_file.close();


    ifstream world_file;
    world_file.open(creaturesFile);
    if (!world_file) {er_t error = {3,creaturesFile}; throw error;}

    world_file >> world.grid.height;
    if (world.grid.height > MAXHEIGHT) {world_file.close(); throw 10;}
    world_file >> world.grid.width;
    if (world.grid.width > MAXWIDTH) {world_file.close(); throw 11;}

    // ===============inti creatures===============

    temp1 = 0;// int temp1 is counter for creature number 
    while (getline(world_file, input)){
        if (input == "") continue; 

        bool is_found = 0; // indicate whther species is found

        ss.str(input);
        ss >> helperstring;
        for (unsigned int i = 0; i < world.numSpecies; i++){
            if (helperstring == world.species[i].name){
                world.creatures[temp1].species = &world.species[i];
                is_found = 1;
            }
        }
        if(!is_found) {er_t error = {8, helperstring}; world_file.close(); throw error;}
        // error: unknown species, throw the invalid species name

        ss >> helperstring;
        is_found = 0; // indicate direction found or not in directName
        for (int i = 0; i <= 3; i++){
            if (helperstring == directName[i]){
                world.creatures[temp1].direction = direction_t(i);
                is_found = 1;
            }
        }
        if(!is_found) {er_t error = {9, helperstring}; world_file.close(); throw error;}
        // error: illigal direction, throw the invalid direction name

        ss >> world.creatures[temp1].location.r >> world.creatures[temp1].location.c;

        if ((unsigned int)world.creatures[temp1].location.r >= world.grid.height || 
                (unsigned int)world.creatures[temp1].location.c >= world.grid.width) {
            err_tt error = {(int)world.grid.height, (int)world.grid.width, world.creatures[temp1]};
			world_file.close(); throw error;}
        // error: creature outside world/grid, throw the grid-size and the wrong creature
        
        temp1++;
        if (temp1 > MAXCREATURES) throw 7;
        // error: too much creatures
        
        for (unsigned int i = 0; i < temp1-1; i++){
            if(world.creatures[i].location.r == world.creatures[temp1-1].location.r &&
                    world.creatures[i].location.c == world.creatures[temp1-1].location.c){
                bi_creature error = {world.creatures[temp1-1], world.creatures[i]};
				world_file.close(); throw error;}
        }// error: overlapped creatures, throw both creatures, smaller index at first

        ss.clear();
    }

    world.numCreatures = temp1;
    world_file.close();

    // initialize the grid.square pointers to creature, as null pointers
    for (unsigned int i = 0; i < world.grid.height; i++){
        for (unsigned int j = 0; j< world.grid.width; j++){
            world.grid.squares[i][j] = NULL;
        }
    }

    // if find creature at (r,c), make square[r][c] pointing at it
    for (unsigned int i = 0; i < world.numCreatures; i++){
        world.grid.squares[world.creatures[i].location.r][world.creatures[i].location.c] = &world.creatures[i];
        world.creatures[i].programID = 0;
    }

    return 1;

}

void printWorld(const world_t &world){

    //print species
    cout << "there are " << world.numSpecies << " species" << endl;
    cout << endl;
    for (unsigned int i = 0; i < world.numSpecies; i++){
        cout << "species " << i << " " << world.species[i].name << ", has " << world.species[i].programSize << " programs" << endl;
            for (unsigned int j =0; j < world.species[i].programSize; j++){
                cout << "program " << j << ": " << opName[world.species[i].program[j].op] 
                << ", pointing to " << world.species[i].program[j].address << endl;
            }
            cout << endl;
    }


    //print creature
    cout << "there are " << world.numCreatures << " creatures" << endl;
    cout << endl;
    for (unsigned int i = 0; i < world.numCreatures; i++){
        cout << "craeture " << i << " " << world.creatures[i].species->name << 
             ", heading " << directName[world.creatures[i].direction] << 
             ", at point (r,c) " << world.creatures[i].location.r << 
             world.creatures[i].location.c << endl;
    
        cout << endl;
    }
    
    
    //print grid
    int wid = world.grid.width;
    int ht = world.grid.height;
    cout << "the grid is " << ht <<"x"<< wid << endl;

}

void printGrid(const grid_t &grid){

    int wid = grid.width;
    int ht = grid.height;

    for (int i = 0; i < ht; i++){

        string output =""; // string output is resposible for only one line, cleared after output

        for (int j = 0; j < wid; j++){

            if (grid.squares[i][j] != NULL) {
                output.append(grid.squares[i][j]->species->name.substr(0,2) +
                     "_" + directShortName[grid.squares[i][j]->direction] + " ");
            } else {
                output.append("____ ");
            }
        }

        cout << output << endl;
        output.clear();

    }

}

point_t adjacentPoint(point_t pt, direction_t dir){

    point_t ppt;
    switch (dir)
    {
    case EAST:
        ppt = {pt.r, pt.c + 1};
        break;
    case WEST:
        ppt = {pt.r,  pt.c - 1};
        break;
    case NORTH:
        ppt = {pt.r - 1, pt.c};
        break;
    case SOUTH:
        ppt = {pt.r + 1, pt.c};
        break;
    default:
        ppt = pt;
        cerr << "direction fault!" << endl;
        break;
    }

    return ppt;
}

direction_t leftFrom(direction_t dir){
    return (dir > 0) ? direction_t(dir-1) : direction_t(3);
}

direction_t rightFrom(direction_t dir){
    return (dir < 3) ? direction_t(dir + 1) : direction_t(0);
}

instruction_t getInstruction(const creature_t &creature){
    return creature.species->program[creature.programID];
}

creature_t *getCreature(const grid_t &grid, point_t location){
    return grid.squares[location.r][location.c];
}

string crea_call(const creature_t &creature){
    return "(" + creature.species->name + " " + directName[creature.direction] + " "
         + to_string(creature.location.r) + " " + to_string(creature.location.c) + ")";
}

bool is_inside(point_t &point, grid_t &grid){
    return ((unsigned int)point.r < grid.height && point.r >= 0 &&
         (unsigned int)point.c < grid.width && point.c >= 0) ? 1 : 0;
}

void index_change(creature_t &creature, bool to){
    if (to){
        creature.programID = creature.species->program[creature.programID].address - 1;
    } else {
        creature.programID++;
    }
}

void printOp(const creature_t &creature, const int op_num, bool is_verb){
    
    // For consice output, only for first 4 ops, output is needed
    // For verbose one, all actions needed to be output
    if (!is_verb && op_num < 4){
        cout << "Creature " << crea_call(creature) << " takes action: " 
             << opName[op_num] << endl;
    } else if (is_verb){
        cout << "Instruction " << creature.programID + 1 << ": " << opName[op_num];
        if (op_num >= 4) {cout << " " << creature.species->program[creature.programID].address;}
        cout << endl;
    }
    
}

void pointSwap (grid_t &grid, creature_t &creature, point_t p1){
    if (is_inside(p1, grid) && !grid.squares[p1.r][p1.c]){
        point_t temp = creature.location;
        grid.squares[p1.r][p1.c] = &creature;
        grid.squares[temp.r][temp.c] = NULL;
        creature.location = p1;
    }
}

void simulateCreature(creature_t &creature, grid_t &grid, bool verbose){

    bool if_end = 0; // indicates if the turn of creature is finished
    bool way_of_change = 0; // the way to change index of instruction: 0 for directly +1, 
                        // 1 for go to the address following op.

    if (verbose){cout << "Creature " << crea_call(creature) << " takes action:" << endl;}

    while (!if_end){           

        point_t pt_facing = adjacentPoint(creature.location, creature.direction);
        opcode_t op_num = creature.species->program[creature.programID].op;

        printOp(creature, op_num, verbose);

        switch (op_num){
            case HOP:
                pointSwap(grid, creature, pt_facing); 
                // swap the pointer of the point currently on and the adjacent point, if 
                if_end = 1;
                way_of_change = 0;
                break;
            
            case LEFT:
                creature.direction = leftFrom(creature.direction);
                if_end = 1;
                way_of_change = 0;
                break;

            case RIGHT:
                creature.direction = rightFrom(creature.direction);
                if_end = 1;
                way_of_change = 0;
                break;

            case INFECT:
                // change the species of creature on the pt_facing, and reset the programID
                if(grid.squares[pt_facing.r][pt_facing.c]){
                    grid.squares[pt_facing.r][pt_facing.c]->species = creature.species;
                    grid.squares[pt_facing.r][pt_facing.c]->programID = 0;
                }
                if_end = 1;
                way_of_change = 0;
                break;

            case IFEMPTY:
                // pt_facing should be inside grid and not occupied to output 1
                if (is_inside(pt_facing, grid) && !getCreature(grid, pt_facing)){
                    way_of_change = 1;
                } else {
                    way_of_change = 0;
                } break;
                
            case IFENEMY:
                // if outside grid or not occupied, definitely noEnemy
                // if inside, occupied as well as different species, output 1
                if (!is_inside(pt_facing, grid) || !getCreature(grid, pt_facing)){
                    way_of_change = 0;
                } else if (creature.species != getCreature(grid, pt_facing)->species) {
                    way_of_change = 1;
                } else {
                    way_of_change = 0;
                } break;
                
            case IFSAME:
                // if outside grid or not occupied, definitely notSame
                // if inside and occupied, as well as same species, output 1
                if (!is_inside(pt_facing, grid) || !getCreature(grid, pt_facing)){
                    way_of_change = 0;
                } else if(creature.species == getCreature(grid, pt_facing)->species) {
                    way_of_change = 1;
                } else {
                    way_of_change = 0;
                } break;

            case IFWALL:
                // if pt_facing is outside grid, than Is_Wall
                if (!is_inside(pt_facing, grid)) {
                    way_of_change = 1;
                } else {
                    way_of_change = 0;
                } break;

            case GO:
                // directly reset the programID
                way_of_change = 1;
                break;

            default:
                break;
        }

        index_change(creature, way_of_change); // change the craeture's index of instruction/programID

    }
    
}