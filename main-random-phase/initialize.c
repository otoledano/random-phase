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

#define trigonometric_bins 100000


void initialize(Simulation_Parameters *sp,Sampling_Variables *sv,Rel_Coord *rel_coord,Coord *coord,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord),Files *file)
{
	long long int i;
	
	sp->verlet_radius_2=pow(sp->verlet_radius,2);
	sp->lim_2=pow((sp->verlet_radius-sp->cutoff_radius)/(double)2,2);			// Square of the maximum displacement performed by a particle before calculating a new Verlet list
	sp->rcut_2=sp->cutoff_radius*sp->cutoff_radius;
	
	sp->steps_measurement=(long long int)floor((double)sp->num_steps/(double)sp->n_sampling);
	
	sp->steps_sec_measurement=(long long int)floor((double)sp->steps_measurement/(double)sp->sec_output);
	
	sp->cos_tab=calloc(trigonometric_bins,sizeof(double));
	sp->sin_tab=calloc(trigonometric_bins,sizeof(double));
	sp->tan_tab=calloc(trigonometric_bins,sizeof(double));
	
	for(i=0;i<trigonometric_bins;i++)
	{
		sp->cos_tab[i]=cos((double)(i*2.0*M_PI)/(double)(trigonometric_bins));
		sp->sin_tab[i]=sin((double)(i*2.0*M_PI)/(double)(trigonometric_bins));
		sp->tan_tab[i]=tan((double)(i*2.0*M_PI)/(double)(trigonometric_bins));
	}
	
	verlet_list(sp,coord);
	sv->energy=0;
	for(i=0;i<sp->n_part;i++)
	{
		sv->energy+=energy_verlet(rel_coord,coord,sp,energy,i);
	}
	sv->energy=sv->energy/(double)2;
	
	//	**************		Counting the number of sampling variables calculated	***************************************************************
	
	fprintf(file->dynamic,"#X\t\tY\t\t");
	
	sv->sampling_components=0;
	sv->particle_properties=0;
	
	if(sv->Rdf_sampling==1)					// If radial distribution function is calculated
	{
		sv->sampling_components++;
		sv->rdf_initial=1;		
	}
	
	
	
	if(sv->Loc_density_sampling==1)
	{
		sv->loc_density_hist=calloc(sp->n_part,sizeof(long long int));
		sv->local_density_list=calloc(sp->n_part,sizeof(double));
		for(i=0;i<sp->n_part;i++)
		{
			sv->local_density_list[i]=(double)(i+1)/(double)(M_PI*pow(sv->loc_density_rad,2));
		}	
		sprintf(sv->loc_dens_dynam_name,"%s","Local Density");
		sv->particle_properties_name[sv->particle_properties]=sv->loc_dens_dynam_name;
		sv->local_density_index=sv->particle_properties;
		sv->sampling_components++;
		sv->particle_properties++;
	}
	
	if(sv->Voronoi_construction==1)
	{
		sv->sampling_components++;
		
		if(sv->Defects_rdf==1)
		{
			sv->defect_list=calloc(sp->n_part,sizeof(long long int));
			sv->defects_rdf_initial=1;
		}
		
		if(sv->Orientat_parameter==1)
		{
			sv->orientational_param_re=calloc(sp->n_part,sizeof(double));
			sv->orientational_param_im=calloc(sp->n_part,sizeof(double));
			
			
			sprintf(sv->orient_param_dynam_name,"%s","Or. Par. Mod");
			sv->particle_properties_name[sv->particle_properties]=sv->orient_param_dynam_name;
			sv->orient_param_mod_index=sv->particle_properties;
			sv->particle_properties++;
			
			sprintf(sv->orient_phase_dynam_name,"%s","Or. Par. Phase");
			sv->particle_properties_name[sv->particle_properties]=sv->orient_phase_dynam_name;
			sv->orient_param_phase_index=sv->particle_properties;
			
			sv->particle_properties++;
		}
	}
	
	if(sv->Energy_profile==1)
	{
		sv->energy_part_histogram=calloc(sv->energy_bins_hist,sizeof(long long int));
		sv->energy_sys_histogram=calloc(sv->energy_bins_hist,sizeof(long long int));
		sv->energy_hist_width=(double)(sv->energy_max_hist-sv->energy_min_hist)/(double)(sv->energy_bins_hist);
		//~ printf("\n\n%lf\t%lf\t%lf%lld\n\n",sv->energy_hist_width,sv->energy_max_hist,sv->energy_min_hist,sv->energy_bins_hist);
	}
	
	
	sv->particle_prop_list=calloc(sp->n_part*sv->particle_properties,sizeof(double));	
	sv->num_samplings=0;
	sv->num_therm_samplings=0;
	
	for(i=0;i<sv->particle_properties;i++)
	{
		fprintf(file->dynamic,"%s\t",sv->particle_properties_name[i]);
	}
	fprintf(file->dynamic,"\n");
}	
