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
#include "movements.h"
#include "initialize.h"
#include "sampling.h"
#include "voronoi.h"

#define trigonometric_bins 100000		// Divisions for the tabulated trigonometric variables	
#define maxver 500						// Maximum number of particles stored in the Verlet list of each particle
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
	Sampling_Variables sv;
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
	
	reading_input(&sp,&file,input_text,characters_input,&sv);		// Read the input file and fix the simulation variables values
	
	omp_set_num_threads(sp.num_processors);						// Set the number of threads for the parallelization environment
	
	lattice_basis=calloc(sp.lattice_elements,sizeof(Lattice_Basis));		// Allocating memory for the unit cell basis information
	if(strcmp("true",sp.initial_lattice)==0)
	{
		reading_basis(lattice_basis,&file,input_text,characters_input,sp);		// Reading the unit cell basis
	}
	
	
	
	create_output_files(&file,&sp,&sv);				// Create the output folder and files					
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
	
	coord=calloc(sp.n_part,sizeof(Coord));					// Allocate memory for the particle's coordinates
	for(i=0;i<sp.n_part;i++)
	{
		coord[i].verlet=calloc(maxver,sizeof(long int));
	}	
	initial_positions(&sp,lattice_basis,coord,file);		// Set the initial coordinates
		
	//******************************************************************************************************************************	
		
		
	// Define the potential interaction
	
	
	double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord)=NULL; // Set the potential energy function as stated by the input
	potential_energy(&sp,&energy,&rel_coord,&file);
	
	
	//~ printf("%lf\t%lf\n",(double)5.7/(double)100,(*energy)(&sp,(double)5.7/(double)100));	// Example for calling (*energy)
	
	// Initialize the sampling variables depending on the simulation variables
	
	
	void (*movements)(Sampling_Variables *sv,Simulation_Parameters *sp,Coord *coord,Rel_Coord *rel_coord,Files *file,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord))=NULL; // Set the movement class as stated by the input
	movement_select(&sp,&movements);
	
	initialize(&sp,&sv,&rel_coord,coord,energy,&file);

	void (**sampling)(Sampling_Variables *sv,Simulation_Parameters *sp,Coord *coord,Rel_Coord *rel_coord,Files *file,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord))=NULL;
	sampling=calloc(sv.sampling_components,sizeof(void*));
	sampling_selection(&sv,&sp,&sampling);
	
	
	//	*******************************************			 Start the simulation	**********************************************************************
	sp.steps_performed=0;
	do
	{

		(*movements)(&sv,&sp,coord,&rel_coord,&file,energy);
		
		fflush(stdout);
		sv.num_samplings++;
		if(sp.steps_performed>=sp.num_steps*sp.therm_ratio)
		{
			sv.num_therm_samplings++;
		}
		sv.samp_particle_prop=0;	
		for(i=0;i<sv.sampling_components;i++)
		{
			(*sampling[i])(&sv,&sp,coord,&rel_coord,&file,energy);					// Put sampling as a array of pointers to functions, with the different sampling functions
		}
		
		if(sv.num_samplings%sp.dynamic_output_freq==0)
		{
			dynamic_output(&sp,&sv,&file,coord);
			if(sv.Voronoi_construction==1)
			{
				voronoi_output(&sp,&sv,&file,coord);
			}
		}		
		
	// Sampling and continue the simulation
	
	
	}
	while(sp.steps_performed<sp.num_steps);
	
	// Final outputs
	output_sampling(&sv,&file,&sp);
	final_positions(coord,sp,file);
	
	return 0;
}

