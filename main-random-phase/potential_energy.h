#include <inttypes.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <string.h>


#include "input_variables.h"
#include "files.h"


void potential_energy(Simulation_Parameters *sp,double (**energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord),Rel_Coord *rel_coord,Files *file);
double lennard_jones_interaction(Simulation_Parameters *sp,double distance);
double morse_interaction(Simulation_Parameters *sp,double distance);
double algebraic_repulsion_interaction(Simulation_Parameters *sp,double distance);
double algebraic_repulsion_atraction_interaction(Simulation_Parameters *sp,double distance);
double hard_discs_interaction(Simulation_Parameters *sp,double distance);
double Gay_Berne_interaction(Simulation_Parameters *sp,Rel_Coord *rel_coord);
double Gay_Berne_dipolar_interaction(Simulation_Parameters *sp,Rel_Coord *rel_coord);
double energy_tabulated(Simulation_Parameters *sp,Rel_Coord *rel_coord);
double energy_interpolated(Simulation_Parameters *sp,Rel_Coord *rel_coord);
double energy_oriented_tabulated(Simulation_Parameters *sp,Rel_Coord *rel_coord);
void read_potential_input(Simulation_Parameters *sp,Files *file);
void read_potential_input_oriented(Simulation_Parameters *sp,Files *file);


