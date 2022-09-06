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
#include <sys/time.h>

#include "input_variables.h"
#include "files.h"
#include "general_functions.h"
#include "final_output.h"
#include "potential_energy.h"


#define binrdf2 101



int main(int argc, char **argv)
{
	//********************					Declaration of the variables		****************************
	
	
	long long int i,characters_input;
	Files file;
	Simulation_Parameters sp;
	Lattice_Basis *lattice_basis;
	Rel_Coord rel_coord;
	Coord *coord;
	//~ double *position_x,*position_y,*alpha;
	char *input_text;
	int a;
	
	
	//***********************************************************************************************************
	
	
	input_text=calloc(1000000,sizeof(char));		// Allocating memory for the string that will store input file

	file.input=fopen(argv[1],"r");					// Opening the input file, named with the first argument when running the program
	sprintf(file.output_path,"%s",argv[2]);
	
	//***********************		Storing the input file in the string input_text		**********************************
	i=0;						
	do
	{
		i++;
		a=fscanf(file.input,"%c",&input_text[i]);
	}
	while(a!=-1);
	characters_input=i-1;							// Set the total number of characters of the input file
	//**********************************************************************************************************************
	
	reading_input(&sp,&file,input_text,characters_input);		// Read the input file and fix the simulation variables values
	
	//***************** CHANGE TRUE/FALSE to 0's and 1's
	
	lattice_basis=calloc(sp.lattice_elements,sizeof(Lattice_Basis));		// Allocating memory for the unit cell basis information
	if(strcmp("true",sp.initial_lattice)==0)
	{
		reading_basis(lattice_basis,&file,input_text,characters_input,sp);		// Reading the unit cell basis
	}
	
	
	
	create_output_files(&file,&sp);				// Create the output folder and files					
	copy_input(file,input_text,characters_input);
	// Copy the input to the output folder
	
	// Create the universe
	
	//***********************************************	 Create the particles		***************************************************************
	if(strcmp("true",sp.initial_file)==0)
	{
		file.initial_positions=fopen(sp.initial_path,"r");
		fscanf(file.initial_positions,"%lf\t%lf\t%lld\n",&sp.box_x,&sp.box_y,&sp.n_part);
	}
	else
	{
		if(strcmp("true",sp.initial_lattice)==0)
		{
			sp.n_part=sp.lattice_elements*floor((sp.box_x*sp.box_y)/(sp.lattice_a*sp.lattice_b*fabs(sin(sp.lattice_alpha*M_PI/(double)180))))*2;
		}
		else
		{
			sp.n_part=sp.nmol;
		}		
	}	
	
	coord=calloc(sp.n_part,sizeof(Coord));	
	//~ position_x=calloc(sp.n_part,sizeof(double));		// Allocate memory for the particle's coordinates
	//~ position_y=calloc(sp.n_part,sizeof(double));
	//~ alpha=calloc(sp.n_part,sizeof(double));		
	initial_positions(&sp,lattice_basis,coord,file);		// Set the initial coordinates
		
	//******************************************************************************************************************************	
		
		
		
	// Define the potential interaction
	
	
	double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord)=NULL; // Set the potential energy function as stated by the input
	potential_energy(&sp,&energy,&rel_coord,&file);
	
	//~ for(i=1;i<1000;i++)
	//~ {
		//~ printf("%lf\t%lf\n",(double)i/(double)100,(*energy)(&sp,(double)i/(double)100));
	//~ }	
							
	// Initialize the sampling variables depending on the simulation variables
	
	// Start the simulation	
	sp.steps_performed=0;
	do
	{
		//~ MC_move();
		
		
	// Sampling and continue the simulation
	
	
	}
	while(sp.steps_performed<sp.num_steps);
	
	// Final outputs
	
	final_positions(coord,sp,file);
	
	return 0;
}

