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

void initialize(Simulation_Parameters *sp,Sampling_Variables *sv,Rel_Coord *rel_coord,Coord *coord,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord),Files *file);
