#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

#include "simulation.h"

using namespace std;

int main(int argc, char* argv[]){

    try{
        if (argc < 4) throw 1; // error: not enough arguments
        if (atoi(argv[3]) < 0) throw 2; // negative number for rounds

        string file_1, file_2;
        file_1.append(argv[1]);
        file_2.append(argv[2]);

        world_t world;
        initWorld(world, file_1, file_2);
        //printWorld(world);

        // to decide whether verbose mode
        bool is_verb = 0;
        if(argc > 4){
            string a = argv[4];
            is_verb = (a == "v" || a == "verbose");
        }

        cout << "Initial state" << endl;
        printGrid(world.grid);

        // if verbose, print grid each time a creature's turn is simulated
        // if concise, print grid each time a whole turn is simulated
        for (int i = 1; i <= atoi(argv[3]); i++){

            cout << "Round " << i << endl;

            for (unsigned int j = 0; j < world.numCreatures; j++){
                simulateCreature(world.creatures[j], world.grid, is_verb);
                if (is_verb) {printGrid(world.grid);}
            }

            if (!is_verb){printGrid(world.grid);};

        }

    return 0;
    }

    catch(int error){
        if (error == 1)
            cout << "Error: Missing arguments!" << endl;
        if (error == 2)
            cout << "Error: Number of simulation rounds is negative!" << endl;
        if (error == 4){
            cout << "Error: Too many species!" << endl;
            cout << "Maximal number of species is" << MAXSPECIES << "." << endl;}
        if (error == 7){
            cout << "Error: Too many creatures!" << endl;
            cout << "Maximal number of creatures is " << MAXCREATURES << "." << endl;}
        if (error == 10)
            cout << "Error: The grid height is illegal!" << endl;
        if (error == 11)
            cout << "Error: The grid width is illegal!" << endl;
        }
    catch(er_t error){
        if (error.error_int == 3)
            cout << "Error: Cannot open file " << error.error_string << "!" << endl;
        if (error.error_int == 5){
            cout << "Error: Too many instructions for species " << error.error_string << "!" << endl;
            cout << "Maximal number of instructions is " << MAXPROGRAM << "." << endl;}
        if (error.error_int == 6)
            cout << "Instruction " << error.error_string << " is not recognized!" << endl;
        if (error.error_int == 8)
            cout << "Error: Species " << error.error_string << " not found!" << endl;
        if (error.error_int == 9)
            cout << "Error: Directions " << error.error_string << " is not recognized!" << endl;
    }
    catch(err_tt error){
        cout << "Error: Creature " << crea_call(error.crea) << " is out of bound!" << endl;
        cout << "The grid size is " << error.r << "-by-" << error.c << "." << endl;
    }
    catch(bi_creature error){
        cout << "Error: Creature " << crea_call(error.crea_1) << " overlaps with creature " << 
             crea_call(error.crea_2) << "!" << endl;
    }

    return 0;

}