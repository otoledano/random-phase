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

void final_positions(Coord *coord,Simulation_Parameters sp,Files file)
{
	long long int i;
	fprintf(file.final_positions,"%lf\t%lf\t%lld\n",sp.box_x,sp.box_y,sp.n_part);
	if(strcmp("true",sp.oriented_particles)==0)
	{
		for(i=0;i<sp.n_part;i++)
		{
			fprintf(file.final_positions,"%lf\t%lf\t%lf\n",coord[i].x,coord[i].y,coord[i].phi);	
		}
	}	
	else
	{
		for(i=0;i<sp.n_part;i++)
		{
			fprintf(file.final_positions,"%lf\t%lf\n",coord[i].x,coord[i].y);
		}
	}		
}	

