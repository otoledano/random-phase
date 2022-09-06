#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

#include "input_variables.h"


typedef struct 
{
	char potential_path[10000],output_path[10000],final_positions_name[10000],input_copy_name[10000],potential_out_name[10000];
	FILE *input,*initial_positions,*final_positions,*input_copy,*potential_out,*potential_in;
	
} Files;


void create_output_files(Files *file,Simulation_Parameters *sp);

void copy_input(Files file,char *input_text,long long int characters_input);
