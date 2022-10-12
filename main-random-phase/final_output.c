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

void output_sampling(Sampling_Variables *sv,Files *file,Simulation_Parameters *sp)
{
	long long int i;
	if(sv->Rdf_sampling==1)
	{
		double half_width,mean_density,radius;
		long long int norm;
		norm=0;
		half_width=(double)sp->rdf_precision/(double)2;
		
		for(i=0;i<sv->rdf_bins_num;i++)
		{
			norm+=sv->rdf_histogram[i];
		}
		mean_density=(double)(norm)/(double)(M_PI*pow(sv->rdf_max,2));	
		for(i=0;i<sv->rdf_bins_num;i++)
		{
			radius=i*sp->rdf_precision;
			fprintf(file->rdf_out,"%lf\t%lf\n",radius+half_width,(double)(sv->rdf_histogram[i])/(double)(mean_density*M_PI*(pow(radius+sp->rdf_precision,2)-pow(radius,2))));	
		}	
	}
	if(sv->Defects_rdf==1)
	{
		fprintf(file->defect_rdf_out,"Distance\tTotal rdf\tPlus def.\tMinus def.\tOpposite sign\n");
		double half_width,mean_density,radius,mean_density_plus,mean_density_minus,mean_density_opposite;
		long long int norm,norm_plus,norm_minus,norm_opposite;
		norm=0;
		norm_plus=0;
		norm_minus=0;
		norm_opposite=0;
		half_width=(double)sp->rdf_precision/(double)2;
		
		for(i=0;i<sv->rdf_bins_num;i++)
		{
			norm+=sv->defect_rdf_histogram[i];
			norm_plus+=sv->plus_def_rdf[i];
			norm_minus+=sv->minus_def_rdf[i];
			norm_opposite+=sv->opposite_def_rdf[i];
		}
		mean_density=(double)(norm)/(double)(M_PI*pow(sv->rdf_max,2));
		mean_density_plus=(double)(norm_plus)/(double)(M_PI*pow(sv->rdf_max,2));
		mean_density_minus=(double)(norm_minus)/(double)(M_PI*pow(sv->rdf_max,2));
		mean_density_opposite=(double)(norm_opposite)/(double)(M_PI*pow(sv->rdf_max,2));	
		for(i=0;i<sv->rdf_bins_num;i++)
		{
			radius=i*sp->rdf_precision;
			fprintf(file->defect_rdf_out,"%lf\t%lf\t%lf\t%lf\t%lf\n",radius+half_width,(double)(sv->defect_rdf_histogram[i])/(double)(mean_density*M_PI*(pow(radius+sp->rdf_precision,2)-pow(radius,2))),(double)(sv->plus_def_rdf[i])/(double)(mean_density_plus*M_PI*(pow(radius+sp->rdf_precision,2)-pow(radius,2))),(double)(sv->minus_def_rdf[i])/(double)(mean_density_minus*M_PI*(pow(radius+sp->rdf_precision,2)-pow(radius,2))),(double)(sv->opposite_def_rdf[i])/(double)(mean_density_opposite*M_PI*(pow(radius+sp->rdf_precision,2)-pow(radius,2))));	
		}
	
	}	
	if(sv->Loc_density_sampling==1)
	{
		double norm;
		norm=0;
		for(i=0;i<sp->n_part;i++)
		{
			norm+=sv->loc_density_hist[i];
		}
		for(i=0;i<sp->n_part;i++)
		{
			fprintf(file->local_density,"%lf\t%lf\n",(double)(i+1)/(double)(M_PI*pow(sv->loc_density_rad,2)),(double)(sv->loc_density_hist[i])/(double)(norm));
		}
	}
	
	if(sv->Energy_profile==1)
	{
		double norm1;
		norm1=0;
		for(i=0;i<sv->energy_bins_hist;i++)
		{
			norm1+=sv->energy_part_histogram[i];
		}
		
		for(i=0;i<sv->energy_bins_hist;i++)
		{
			fprintf(file->energy_histogram_out,"%lf\t%lf\n",sv->energy_min_hist+i*sv->energy_hist_width,(double)sv->energy_part_histogram[i]/(double)norm1);
	
		}
	}	
}	

