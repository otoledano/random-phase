#pragma once

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

//~ void voronoi_partition(Simulation_Parameters *sp,Coord *coord,Sampling_Variables *sv,Files *file,Voronoi *voronoi);

void voronoi_partition(Sampling_Variables *sv,Simulation_Parameters *sp,Coord *coord,Rel_Coord *rel_coord,Files *file,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord));
void voronoi_output(Simulation_Parameters *sp,Sampling_Variables *sv,Files *file,Coord *coord);
