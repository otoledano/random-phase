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
#include "general_functions.h"
#include "voronoi.h"


void sampling_rdf(Sampling_Variables *sv,Simulation_Parameters *sp,Coord *coord,Rel_Coord *rel_coord,Files *file,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord))
{
	long long int i,j;
	double dis;
	
	if(sp->steps_performed>=sp->num_steps*sp->therm_ratio)
	{
		if(sv->rdf_initial==1)
		{
			if(sp->box_x<=sp->box_y)
			{
				sv->rdf_max=sp->box_x/2.0;
			}
			else
			{
				sv->rdf_max=sp->box_y/2.0;
			}
			sv->rdf_bins_num=(long long int)floor((double)(sv->rdf_max)/(double)(sp->rdf_precision));
			sv->rdf_histogram=calloc(sv->rdf_bins_num,sizeof(long long int));
			sv->rdf_initial=0;
		}
		if(sp->box_x<sv->rdf_max*2)
		{
			sv->rdf_max=sp->box_x/2.0;	
		}
		if(sp->box_y<sv->rdf_max*2)
		{
			sv->rdf_max=sp->box_y/2.0;	
		}
		#pragma omp parallel private(j,dis)
		{
		#pragma omp for		
		for(i=0;i<sp->n_part;i++)
		{
			for(j=i+1;j<sp->n_part;j++)
			{
				dis=distance(sp,coord[i].x,coord[j].x,coord[i].y,coord[j].y);
				histogram(sv->rdf_histogram,sp->rdf_precision,0.0,sv->rdf_bins_num,dis);
			}
		}
		}
	}	
}

void sampling_local_density(Sampling_Variables *sv,Simulation_Parameters *sp,Coord *coord,Rel_Coord *rel_coord,Files *file,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord))
{
	long long int j,neighbors,i;
	double dis;
	#pragma omp parallel private(j,dis,neighbors)
	{
	#pragma omp for
	for(i=0;i<sp->n_part;i++)
	{
		neighbors=0;
		for(j=0;j<sp->n_part;j++)
		{	
			dis=distance(sp,coord[i].x,coord[j].x,coord[i].y,coord[j].y);
			if(dis<=sv->loc_density_rad)
			{
				neighbors++;	
			}	
		}
		sv->particle_prop_list[sv->samp_particle_prop*sp->n_part+i]=sv->local_density_list[neighbors];
		#pragma omp critical
		{
			sv->loc_density_hist[neighbors]++;;
		}
	}
	}
	sv->samp_particle_prop++;
}	

void sampling_selection(Sampling_Variables *sv,Simulation_Parameters *sp,void (**sampling[sv->sampling_components])(Sampling_Variables *sv,Simulation_Parameters *sp,Coord *coord,Rel_Coord *rel_coord,Files *file,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord)))
{
	long long int counter=0;
	if(sv->Rdf_sampling==1)
	{
		(*sampling)[counter]=&sampling_rdf;
		counter++;
	}
	if(sv->Loc_density_sampling==1)
	{
		(*sampling)[counter]=&sampling_local_density;
		counter++;
	}
	
	if(sv->Voronoi_construction==1)
	{
		(*sampling)[counter]=&voronoi_partition;	
		counter++;
	}	
}

void secondary_output(Sampling_Variables *sv,Simulation_Parameters *sp,Files *file)
{
	fprintf(file->energy_out,"%lld\t%lf\n",sp->steps_performed,sv->energy/(double)sp->n_part);
	fflush(file->energy_out);

}


void defects_ratio(Simulation_Parameters *sp,Sampling_Variables *sv,Files *file,Coord *coord)
{
	long long int i;
	sv->defect_count=0;
	if(sv->Defect_ratio==1)
	{
		for(i=0;i<sp->n_part;i++)
		{
			if(coord[i].n_neighbor!=sv->coordination_number)
			{
				if(sv->Defects_rdf==1)
				{
					sv->defect_list[sv->defect_count]=i;
				}	
				sv->defect_count++;
			}	
		}	
	}
	fprintf(file->defect_ratio_out,"%lld\t%lf\n",sp->steps_performed,(double)sv->defect_count/(double)sp->n_part);	
	fflush(file->defect_ratio_out);
}

void defects_rdf(Simulation_Parameters *sp,Sampling_Variables *sv,Files *file,Coord *coord)
{
	
	fflush(stdout);
	long long int i,j,ii,jj;
	double dis;

	if(sp->steps_performed>=sp->num_steps*sp->therm_ratio)
	{
		if(sv->defects_rdf_initial==1)
		{
			if(sp->box_x<=sp->box_y)
			{
				sv->rdf_max=sp->box_x/2.0;
			}
			else
			{
				sv->rdf_max=sp->box_y/2.0;
			}
			sv->rdf_bins_num=(long long int)floor((double)(sv->rdf_max)/(double)(sp->rdf_precision));
			sv->defect_rdf_histogram=calloc(sv->rdf_bins_num,sizeof(long long int));
			sv->plus_def_rdf=calloc(sv->rdf_bins_num,sizeof(long long int));
			sv->minus_def_rdf=calloc(sv->rdf_bins_num,sizeof(long long int));
			sv->opposite_def_rdf=calloc(sv->rdf_bins_num,sizeof(long long int));
			sv->defects_rdf_initial=0;
		}
		if(sp->box_x<sv->rdf_max*2)
		{
			sv->rdf_max=sp->box_x/2.0;	
		}
		if(sp->box_y<sv->rdf_max*2)
		{
			sv->rdf_max=sp->box_y/2.0;	
		}
	
		#pragma omp parallel private(j,dis,ii,jj)
		{
		#pragma omp for
		for(i=0;i<sv->defect_count;i++)
		{
			ii=sv->defect_list[i];
			for(j=i+1;j<sv->defect_count;j++)
			{
				jj=sv->defect_list[j];
				dis=distance(sp,coord[ii].x,coord[jj].x,coord[ii].y,coord[jj].y);
				histogram(sv->defect_rdf_histogram,sp->rdf_precision,0.0,sv->rdf_bins_num,dis);
				if(coord[ii].n_neighbor-sv->coordination_number<0)		
				{
					if(coord[jj].n_neighbor-sv->coordination_number<0)
					{
						histogram(sv->minus_def_rdf,sp->rdf_precision,0.0,sv->rdf_bins_num,dis);
					}
					else
					{
						histogram(sv->opposite_def_rdf,sp->rdf_precision,0.0,sv->rdf_bins_num,dis);
					}	
				}
				else
				{
					if(coord[jj].n_neighbor-sv->coordination_number<0)
					{
						histogram(sv->opposite_def_rdf,sp->rdf_precision,0.0,sv->rdf_bins_num,dis);
					}
					else
					{
						histogram(sv->plus_def_rdf,sp->rdf_precision,0.0,sv->rdf_bins_num,dis);		
					}
				}		
			}
		}
		}
	}	
}			
