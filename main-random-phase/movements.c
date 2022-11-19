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
#include "sampling.h"

void movement_MC_NVT_local(Sampling_Variables *sv,Simulation_Parameters *sp,Coord *coord,Rel_Coord *rel_coord,Files *file,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord))
{
	long long int i;
	double E,E2,x_old,y_old,delta_E;
	printf("Simulation progress: %lf%%\r",100.0*((double)sp->steps_performed/(double)sp->num_steps));
	do
	{
		sp->trial_movements=0;
		do
		{
			i=(long long int)floor(sp->n_part*rand())/RAND_MAX;
			x_old=coord[i].x;
			y_old=coord[i].y;
			E=energy_verlet(rel_coord,coord,sp,energy,i);
				
			coord[i].x=coord[i].x+sp->radial_disp*cos_tab(sp,(double)(rand()*2.0*M_PI)/(double)RAND_MAX);
			coord[i].y=coord[i].y+sp->radial_disp*sin_tab(sp,(double)(rand()*2.0*M_PI)/(double)RAND_MAX);
			

			
			coord[i].x=periodic_boundary_conditions(coord[i].x,sp->box_x);
			coord[i].y=periodic_boundary_conditions(coord[i].y,sp->box_y);
			
			verlet_check(sp,coord,i);
			
			E2=energy_verlet(rel_coord,coord,sp,energy,i);
			delta_E=E2-E;

			if(((double)rand()/(double)RAND_MAX)<exp(-(delta_E)/(sp->k_B*sp->T)))							// Accepted movements
			{
				sv->energy+=delta_E;
				
				if(sv->Energy_profile==1)
				{	
					if(sp->steps_performed>sp->num_steps*sp->therm_ratio)
					{
						histogram(sv->energy_part_histogram,sv->energy_hist_width,sv->energy_min_hist,sv->energy_bins_hist,E2);
					}
				}
						
			}
			else 							// Rejected movements
			{
				coord[i].x=x_old;
				coord[i].y=y_old;
				
				if(sv->Energy_profile==1)
				{
					if(sp->steps_performed>sp->num_steps*sp->therm_ratio)
					{
						histogram(sv->energy_part_histogram,sv->energy_hist_width,sv->energy_min_hist,sv->energy_bins_hist,E);
					
					}
				}
					
			}	
			sp->trial_movements++;	
		}
		while(sp->trial_movements<sp->n_part);
		sp->steps_performed++;
		
		if((sp->steps_performed%sp->steps_sec_measurement)==0)
		{
			secondary_output(sv,sp,file); //Output with properties that do not require aditional calculations. for MC run --- NVT-energy, NPT-energy and [], muPT- energy [] and particles...
		}	
		
		
	}
	while(sp->steps_performed%sp->steps_measurement!=0);
	sp->trial_movements=0;
}	

void movement_MC_NVT_local_oriented(Sampling_Variables *sv,Simulation_Parameters *sp,Coord *coord,Rel_Coord *rel_coord,Files *file,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord))
{





}	

void movement_select(Simulation_Parameters *sp,void (**movements)(Sampling_Variables *sv,Simulation_Parameters *sp,Coord *coord,Rel_Coord *rel_coord,Files *file,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord)))
{
	if(strcmp("NVT",sp->simulation_ensemble)==0)					// NVT ensemble
	{
		if(sp->Oriented_particles==0)
		{
			*movements=&movement_MC_NVT_local;
		}
		if(sp->Oriented_particles==1)
		{
			*movements=&movement_MC_NVT_local_oriented;
		}	
	}
	
}	
