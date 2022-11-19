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


//~ void sampling_selection(Sampling_Variables *sv,Simulation_Parameters *sp,void (**sampling[sv->sampling_components])(Sampling_Variables *sv,Simulation_Parameters *sp,Coord *coord,Rel_Coord *rel_coord,Files *file,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord)));
void sampling_selection(Sampling_Variables *sv,Simulation_Parameters *sp,void (**sampling[sv->sampling_components])(Sampling_Variables *sv,Simulation_Parameters *sp,Coord *coord,Rel_Coord *rel_coord,Files *file,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord)));
void secondary_output(Sampling_Variables *sv,Simulation_Parameters *sp,Files *file);


void sampling_rdf(Sampling_Variables *sv,Simulation_Parameters *sp,Coord *coord,Rel_Coord *rel_coord,Files *file,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord));
void sampling_local_density(Sampling_Variables *sv,Simulation_Parameters *sp,Coord *coord,Rel_Coord *rel_coord,Files *file,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord));



void defects_ratio(Simulation_Parameters *sp,Sampling_Variables *sv,Files *file,Coord *coord);
void defects_rdf(Simulation_Parameters *sp,Sampling_Variables *sv,Files *file,Coord *coord);
