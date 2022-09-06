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


void create_output_files(Files *file,Simulation_Parameters *sp)
{
	mkdir(file->output_path,0744);
	
	sprintf(file->final_positions_name,"%s/final_coordinates.txt",file->output_path);
	file->final_positions=fopen(file->final_positions_name,"w");
	
	sprintf(file->input_copy_name,"%s/input.txt",file->output_path);
	file->input_copy=fopen(file->input_copy_name,"w");
	
	if(sp->Potential_out==1)
	{
		sprintf(file->potential_out_name,"%s/potential_out.txt",file->output_path);
		file->potential_out=fopen(file->potential_out_name,"w");
	}
}


void copy_input(Files file,char *input_text,long long int characters_input)
{
	long long int i;
	for(i=1;i<characters_input;i++)
	{
		fprintf(file.input_copy,"%c",input_text[i]);
	}
	fclose(file.input_copy);
}	
