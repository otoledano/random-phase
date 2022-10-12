#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

#include "input_variables.h"


typedef struct 
{
	char potential_path[10000],output_path[10000],final_positions_name[10000],input_copy_name[10000],potential_out_name[10000],dynamic_name[10000],rdf_out_name[10000],energy_name[10000],local_density_name[10000],voronoi_output_name[10000];
	FILE *input,*initial_positions,*final_positions,*input_copy,*potential_out,*potential_in,*dynamic,*rdf_out,*energy_out,*local_density,*voronoi_diagram;
	char defect_ratio_name[10000],defect_rdf_name[10000],orientation_parameter_name[10000],energy_histogram_name[10000];
	FILE *defect_ratio_out,*defect_rdf_out,*orientation_parameter_out,*energy_histogram_out;
} Files;


void create_output_files(Files *file,Simulation_Parameters *sp,Sampling_Variables *sv);

void copy_input(Files file,char *input_text,long long int characters_input);
