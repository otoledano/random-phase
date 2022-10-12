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


void create_output_files(Files *file,Simulation_Parameters *sp,Sampling_Variables *sv)
{
	mkdir(file->output_path,0744);
	
	sprintf(file->final_positions_name,"%s/final_coordinates.txt",file->output_path);
	file->final_positions=fopen(file->final_positions_name,"w");
	
	sprintf(file->input_copy_name,"%s/input.txt",file->output_path);
	file->input_copy=fopen(file->input_copy_name,"w");
	
	sprintf(file->dynamic_name,"%s/dynamic.txt",file->output_path);
	file->dynamic=fopen(file->dynamic_name,"w");
	
	sprintf(file->energy_name,"%s/energy.txt",file->output_path);
	file->energy_out=fopen(file->energy_name,"w");
	
	if(sp->Potential_out==1)
	{
		sprintf(file->potential_out_name,"%s/potential_out.txt",file->output_path);
		file->potential_out=fopen(file->potential_out_name,"w");
	}
	if(sv->Rdf_sampling==1)
	{
		sprintf(file->rdf_out_name,"%s/rdf.txt",file->output_path);
		file->rdf_out=fopen(file->rdf_out_name,"w");
	}
	
	if(sv->Loc_density_sampling==1)
	{
		sprintf(file->local_density_name,"%s/local_density_distribution.txt",file->output_path);
		file->local_density=fopen(file->local_density_name,"w");
	}
	
	if(sv->Voronoi_construction==1)
	{
		sprintf(file->voronoi_output_name,"%s/voronoi_diagram.txt",file->output_path);
		file->voronoi_diagram=fopen(file->voronoi_output_name,"w");
	}
	
	if(sv->Defect_ratio==1)
	{
		sprintf(file->defect_ratio_name,"%s/defect_ratio.txt",file->output_path);
		file->defect_ratio_out=fopen(file->defect_ratio_name,"w");
	}
	
	if(sv->Defects_rdf==1)
	{
		sprintf(file->defect_rdf_name,"%s/defect_rdf.txt",file->output_path);
		file->defect_rdf_out=fopen(file->defect_rdf_name,"w");
	}
	
	if(sv->Orientat_parameter==1)
	{
		sprintf(file->orientation_parameter_name,"%s/orientational_parameter.txt",file->output_path);
		file->orientation_parameter_out=fopen(file->orientation_parameter_name,"w");
		fprintf(file->orientation_parameter_out,"Step\tOrient. Par. Mod.\tOrient. Par. Pha.\n");
	}
	
	if(sv->Energy_profile==1)
	{
		sprintf(file->energy_histogram_name,"%s/energy_histogram.txt",file->output_path);
		file->energy_histogram_out=fopen(file->energy_histogram_name,"w");
		fprintf(file->energy_histogram_out,"Energy\tPart. Distrib.\tTotal Distrib.\n");
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
