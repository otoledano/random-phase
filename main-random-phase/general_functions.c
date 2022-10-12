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

#define periodic_angles 12*M_PI
#define binrdf2 101
#define energymap_grid 50
#define trigonometric_bins 100000
#define maxver 200						// Maximum number of particles stored in the Verlet list of each particle

double displacement_x(Simulation_Parameters *sp,double xi,double xj)
{
	double dx;
	dx=xi-xj;
	dx=dx-sp->box_x*round((double)dx/(double)sp->box_x);
	return dx;
}	

double displacement_y(Simulation_Parameters *sp,double yi,double yj)
{
	double dy;
	dy=yi-yj;
	dy=dy-sp->box_y*round((double)dy/(double)sp->box_y);
	return dy;
}	

void parametros_matrix(char* palabra,char* s,int characters,FILE* entrada,int elements_x,int elements_y,double *array)
{
	long int m,k,i,j;
	
	m=0;
	for(k=0;k<=characters;k++)
	{
		if(s[k]==palabra[m])
		{
			m++;
		}
		else
		{
			m=0;
		}
		if(m==strlen(palabra))
		{
			fseek(entrada,k,SEEK_SET);
			for(i=0;i<elements_y;i++)
			{
				for(j=0;j<elements_x;j++)
				{
					fscanf(entrada,"%lf",&array[i*elements_x+j]);
				}
				fscanf(entrada,"\n");
			}
			break;
			
			
		}
	}
	fseek(entrada,0,SEEK_SET);	
	
}


void parametros_char(char* palabra,char* s,int characters,FILE* entrada,char* value)
{
	long int m,k;
	
	m=0;
	for(k=0;k<=characters;k++)
	{
		if(s[k]==palabra[m])
		{
			m++;
		}
		else
		{
			m=0;
		}
		if(m==strlen(palabra))
		{
			fseek(entrada,k,SEEK_SET);
			
			
			fscanf(entrada, " \'%[^\']\'",value);
			
			
			break;
		}
		
	}
	fseek(entrada,0,SEEK_SET);	
}

double parametros(char* palabra,char* s,int characters,FILE* entrada)
{
	long int m,k;
	double value;
	
	m=0;
	for(k=0;k<=characters;k++)
	{
		if(s[k]==palabra[m])
		{
			m++;
		}
		else
		{
			m=0;
		}
		if(m==strlen(palabra))
		{
			fseek(entrada,k,SEEK_SET);
			
			fscanf(entrada,"%lf",&value);
			break;
			
			
		}
	}
	fseek(entrada,0,SEEK_SET);	
	return value;
}

void parametros_array(char* palabra,char* s,int characters,FILE* entrada,int elements,double *array)
{
	long int m,k,i;
	
	m=0;
	for(k=0;k<=characters;k++)
	{
		if(s[k]==palabra[m])
		{
			m++;
		}
		else
		{
			m=0;
		}
		if(m==strlen(palabra))
		{
			fseek(entrada,k,SEEK_SET);
			for(i=0;i<elements;i++)
			{
				fscanf(entrada,"%lf",&array[i]);
			}
			break;
			
			
		}
	}
	fseek(entrada,0,SEEK_SET);	
}



void reading_input(Simulation_Parameters *sp,Files *file,char* s,long long int characters,Sampling_Variables *sv)
{
	char *Simulation_Ensemble={"Simulation_Ensemble"};
	parametros_char(Simulation_Ensemble,s,characters,file->input,sp->simulation_ensemble);
	if(strcmp("NPT",sp->simulation_ensemble)==0)
	{
		char *Target_Pressure={"Target_Pressure"};
		sp->target_pressure=parametros(Target_Pressure,s,characters,file->input);
	}
	
	
	char *Box_x={"Box_x"};
	sp->box_x=parametros(Box_x,s,characters,file->input);
	char *Box_y={"Box_y"};
	sp->box_y=parametros(Box_y,s,characters,file->input);
	
	
		
		
	char *Temperature_Sys={"Temperature_Sys"};
	sp->T=parametros(Temperature_Sys,s,characters,file->input);
	
	
	char *Oriented_Particles={"Oriented_Particles"};
	parametros_char(Oriented_Particles,s,characters,file->input,sp->oriented_particles);
	if(strcmp("true",sp->oriented_particles)==0)
	{
		sp->Oriented_particles=1;
		char *Electric_Dipole={"Electric_Dipole"};
		parametros_char(Electric_Dipole,s,characters,file->input,sp->electric_dipole);
		if(strcmp("true",sp->electric_dipole)==0)
		{
			sp->Electric_dipole=1;
			char *Dipole_Moment={"Dipole_Moment"};
			sp->dipole_moment=parametros(Dipole_Moment,s,characters,file->input);
		}	
		else
		{
			sp->Electric_dipole=0;
		}
		char *Potential_Ang_Div={"Potential_Ang_Div"};
		sp->potential_ang_div=parametros(Potential_Ang_Div,s,characters,file->input);	
	}
	else
	{
		sp->Oriented_particles=0;
	}		
	
	char *Potential_Tabulated={"Potential_Tabulated"};
	parametros_char(Potential_Tabulated,s,characters,file->input,sp->potential_tabulated);
	if(strcmp("true",sp->potential_tabulated)==0)			// ************** If the potential is read from a file ************
	{
		sp->Potential_tabulated=1;
		char *Potential_PATH={"Potential_PATH"};
		parametros_char(Potential_PATH,s,characters,file->input,sp->potential_path);
	}
	else                                                    // ***********	If the potential is analytic ***********************
	{
		sp->Potential_tabulated=0;
		char *Potential_Function={"Potential_Function"};
		parametros_char(Potential_Function,s,characters,file->input,sp->potential_function);
		char *Potential_Sigma={"Potential_Sigma"};
		sp->potential_sigma=parametros(Potential_Sigma,s,characters,file->input);
		char *Potential_Epsilon={"Potential_Epsilon"};
		sp->potential_epsilon=parametros(Potential_Epsilon,s,characters,file->input);
		
		if(strcmp("AR",sp->potential_function)==0)			// ************** For algebraic repulsive potential ************
		{
			char *Rep_Exponent={"Rep_Exponent"};
			sp->rep_exponent=parametros(Rep_Exponent,s,characters,file->input);	
		}	
		if(strcmp("ARA",sp->potential_function)==0)			// ************** For algebraic repulsive and atractive potential ************
		{
			char *Rep_Exponent={"Rep_Exponent"};
			sp->rep_exponent=parametros(Rep_Exponent,s,characters,file->input);	
			char *Atr_Exponent={"Atr_Exponent"};
			sp->atr_exponent=parametros(Atr_Exponent,s,characters,file->input);
		}	
		if(strcmp("Morse",sp->potential_function)==0)			// ************** For Morse potential ************
		{
			char *Potential_Width={"Potential_Width"};
			sp->potential_width=parametros(Potential_Width,s,characters,file->input);
		}
		if(strcmp("GB",sp->potential_function)==0)			// ************** For Gay-Berne potential ************
		{
			char *Epsilon_EndEnd={"Epsilon_EndEnd"};
			sp->epsilon_endend=parametros(Epsilon_EndEnd,s,characters,file->input);
			char *Epsilon_SidSid={"Epsilon_SidSid"};
			sp->epsilon_sidsid=parametros(Epsilon_SidSid,s,characters,file->input);
			char *Sigma_Par={"Sigma_Par"};
			sp->sigma_par=parametros(Sigma_Par,s,characters,file->input);
			char *Sigma_Perp={"Sigma_Perp"};
			sp->sigma_perp=parametros(Sigma_Perp,s,characters,file->input);
			char *Mu_Ellipse={"Mu_Ellipse"};
			sp->mu_ellipse=parametros(Mu_Ellipse,s,characters,file->input);
			char *Nu_Ellipse={"Nu_Ellipse"};
			sp->nu_ellipse=parametros(Nu_Ellipse,s,characters,file->input);
		}		
			
	}
	
	char *Num_Steps={"Num_Steps"};
	sp->num_steps=(long long int)parametros(Num_Steps,s,characters,file->input);
	sp->num_steps=sp->num_steps;
	
	char *Num_Processors={"Num_Processors"};
	sp->num_processors=(int)parametros(Num_Processors,s,characters,file->input);
	
	char *Potential_Analytic={"Potential_Analytic"};
	parametros_char(Potential_Analytic,s,characters,file->input,sp->potential_analytic);
	if(strcmp("true",sp->potential_analytic)==0)			
	{
		sp->Potential_analytic=1;
	}
	else
	{
		sp->Potential_analytic=0;
	}		
	char *Potential_Interpolat={"Potential_Interpolat"};
	parametros_char(Potential_Interpolat,s,characters,file->input,sp->potential_interpolat);
	if(strcmp("true",sp->potential_interpolat)==0)			
	{
		sp->Potential_interpolat=1;
	}	
	else
	{
		sp->Potential_interpolat=0;
	}	
	char *Potential_Out={"Potential_Out"};
	parametros_char(Potential_Out,s,characters,file->input,sp->potential_out);
	if(strcmp("true",sp->potential_out)==0)			
	{
		sp->Potential_out=1;
	}	
	else
	{
		sp->Potential_out=0;
	}
	
	char *System_Units={"System_Units"};
	parametros_char(System_Units,s,characters,file->input,sp->system_units);
	if(strcmp("Internal",sp->system_units)==0)			
	{
		sp->k_B=1;
	}
	else if (strcmp("Nano",sp->system_units)==0)
	{
		sp->k_B=8.617333262E-5;
	}	
	
	char *Angular_Disp={"Angular_Disp"};
	sp->angular_disp=parametros(Angular_Disp,s,characters,file->input);
	sp->angular_disp=(double)(sp->angular_disp*M_PI)/(double)(180);
	
	char *Radial_Disp={"Radial_Disp"};
	sp->radial_disp=parametros(Radial_Disp,s,characters,file->input);
	char *Rdf_Precision={"Rdf_Precision"};
	sp->rdf_precision=parametros(Rdf_Precision,s,characters,file->input);
	char *Cutoff_Radius={"Cutoff_Radius"};
	sp->cutoff_radius=parametros(Cutoff_Radius,s,characters,file->input);
	char *Verlet_Radius={"Verlet_Radius"};
	sp->verlet_radius=parametros(Verlet_Radius,s,characters,file->input);
	char *Potential_Divis={"Potential_Divis"};
	sp->potential_divis=parametros(Potential_Divis,s,characters,file->input);
	
	
	
	char *Initial_File={"Initial_File"};
	parametros_char(Initial_File,s,characters,file->input,sp->initial_file);
	if(strcmp("true",sp->initial_file)==0)
	{
		sp->Initial_file=1;
		char *Initial_Path={"Initial_Path"};
		parametros_char(Initial_Path,s,characters,file->input,sp->initial_path);
	}
	else
	{
		sp->Initial_file=0;
		char *Initial_Lattice={"Initial_Lattice"};
		parametros_char(Initial_Lattice,s,characters,file->input,sp->initial_lattice);
		if(strcmp("true",sp->initial_lattice)==0)
		{
			sp->Initial_lattice=1;
			char *Lattice_a={"Lattice_a"};
			sp->lattice_a=parametros(Lattice_a,s,characters,file->input);
			char *Lattice_b={"Lattice_b"};
			sp->lattice_b=parametros(Lattice_b,s,characters,file->input);
			char *Lattice_alpha={"Lattice_alpha"};
			sp->lattice_alpha=parametros(Lattice_alpha,s,characters,file->input);
									
			char *Lattice_Elements={"Lattice_Elements"};
			sp->lattice_elements=parametros(Lattice_Elements,s,characters,file->input);
					
		}
		else
		{
			sp->Initial_lattice=0;
		}	
	}	
	
	if(strcmp("true",sp->initial_lattice)!=0)
	{
		char *Particles_Num={"Particles_Num"};
		sp->nmol=(long long int)parametros(Particles_Num,s,characters,file->input);
	}
	
	
	char *N_Samplings={"N_Samplings"};
	sp->n_sampling=(long long int)parametros(N_Samplings,s,characters,file->input);
	char *Therm_Ratio={"Therm_Ratio"};
	sp->therm_ratio=parametros(Therm_Ratio,s,characters,file->input);
	char *Sec_Output={"Sec_Output"};
	sp->sec_output=(long long int)parametros(Sec_Output,s,characters,file->input);
	char *Dynamic_Output_Freq={"Dynamic_Output_Freq"};
	sp->dynamic_output_freq=(long long int)parametros(Dynamic_Output_Freq,s,characters,file->input);
	
	
	char *Rdf_Sampling={"Rdf_Sampling"};
	parametros_char(Rdf_Sampling,s,characters,file->input,sv->rdf_sampling);
	if(strcmp("true",sv->rdf_sampling)==0)
	{
		sv->Rdf_sampling=1;
	}	
	char *Loc_Density_Sampling={"Loc_Density_Sampling"};
	parametros_char(Loc_Density_Sampling,s,characters,file->input,sv->loc_density_sampling);
	if(strcmp("true",sv->loc_density_sampling)==0)
	{
		sv->Loc_density_sampling=1;
		char *Loc_Density_Rad={"Loc_Density_Rad"};
		sv->loc_density_rad=parametros(Loc_Density_Rad,s,characters,file->input);
	}
	
	char *Voronoi_Construction={"Voronoi_Construction"};
	parametros_char(Voronoi_Construction,s,characters,file->input,sv->voronoi_construction);
	if(strcmp("true",sv->voronoi_construction)==0)
	{
		sv->Voronoi_construction=1;
	}
	
	char *Defect_Ratio={"Defect_Ratio"};
	parametros_char(Defect_Ratio,s,characters,file->input,sv->defect_ratio);
	if(strcmp("true",sv->defect_ratio)==0)
	{
		sv->Defect_ratio=1;
	}
	
	char *Coordination_Number={"Coordination_Number"};
	sv->coordination_number=(int)parametros(Coordination_Number,s,characters,file->input);
	
	char *Defects_Rdf={"Defects_Rdf"};
	parametros_char(Defects_Rdf,s,characters,file->input,sv->defects_rdf);
	if(strcmp("true",sv->defects_rdf)==0)
	{
		sv->Defects_rdf=1;
	}
	
	char *Orientat_Parameter={"Orientat_Parameter"};
	parametros_char(Orientat_Parameter,s,characters,file->input,sv->orientat_parameter);
	if(strcmp("true",sv->orientat_parameter)==0)
	{
		sv->Orientat_parameter=1;
	}
	
	char *Energy_Profile={"Energy_Profile"};
	parametros_char(Energy_Profile,s,characters,file->input,sv->energy_profile);
	if(strcmp("true",sv->energy_profile)==0)
	{
		sv->Energy_profile=1;
		char *Energy_Min_Hist={"Energy_Min_Hist"};
		sv->energy_min_hist=parametros(Energy_Min_Hist,s,characters,file->input);
		char *Energy_Max_Hist={"Energy_Max_Hist"};
		sv->energy_max_hist=parametros(Energy_Max_Hist,s,characters,file->input);
		char *Energy_Bins_Hist={"Energy_Bins_Hist"};
		sv->energy_bins_hist=(long long int)parametros(Energy_Bins_Hist,s,characters,file->input);
	}
	
	
	
	
	
}


void reading_basis(Lattice_Basis *lattice_basis,Files *file,char* s,long long int characters,Simulation_Parameters sp)
{
	int i;
	double *array;
	
	array=calloc(3*sp.lattice_elements,sizeof(double));
	char *Begin_Lattice_Coordinates	={"%Begin_Lattice_Coordinates"};
	if(strcmp("true",sp.oriented_particles)==0)
	{
		parametros_matrix(Begin_Lattice_Coordinates,s,characters,file->input,3,sp.lattice_elements,array);
		for(i=0;i<sp.lattice_elements;i++)
		{
			lattice_basis[i].x=array[i*3];
			lattice_basis[i].y=array[i*3+1];
			lattice_basis[i].alpha=array[i*3+2];
		}
	}
	else
	{
		parametros_matrix(Begin_Lattice_Coordinates,s,characters,file->input,2,sp.lattice_elements,array);
		for(i=0;i<sp.lattice_elements;i++)
		{
			lattice_basis[i].x=array[i*2];
			lattice_basis[i].y=array[i*2+1];
		}
	}	
	
	free(array);
}

void read_positions(FILE* entrada,Simulation_Parameters *sp,Coord *coord)
{
	long long int i;
	double dummy;
	fscanf(entrada,"%lf\t%lf\t%lf\n",&dummy,&dummy,&dummy);
	for(i=0;i<sp->n_part;i++)		// Fore each particle, read its coordinates
	{
		
		if(strcmp("true",sp->oriented_particles)==0)
		{
			fscanf(entrada,"%lf\t%lf\t%lf\n",&coord[i].x,&coord[i].y,&coord[i].phi);
		}
		else
		{
			fscanf(entrada,"%lf\t%lf\n",&coord[i].x,&coord[i].y);
		}			
	}
	
}

void initial_basis(Simulation_Parameters *sp,Lattice_Basis *lattice_basis,Coord *coord)	// Distributes the particles along the periodic lattice
{
	long long int i,j,k,x_divisions,y_divisions,particle_count;
	double sin_alpha,cos_alpha,x,y,initial_x,x_0;
	
	
	sin_alpha=sin(sp->lattice_alpha*M_PI/(double)180);
	cos_alpha=cos(sp->lattice_alpha*M_PI/(double)180);

	x=0;
	y=0;
	
	particle_count=0;
	
	for(k=0;k<sp->lattice_elements;k++)
	{
		
		x=lattice_basis[k].x*sp->lattice_a+lattice_basis[k].y*sp->lattice_b*cos_alpha;
		y=lattice_basis[k].y*sp->lattice_b*sin_alpha;
		y_divisions=ceil((sp->box_y-y)/(sp->lattice_b*sin_alpha));
		for(i=0;i<y_divisions;i++)
		{
			x_0=x;
			initial_x=x-floor(x/sp->lattice_a)*sp->lattice_a;
			x_divisions=ceil((sp->box_x-initial_x)/sp->lattice_a);
			for(j=0;j<x_divisions;j++)
			{
				
				coord[particle_count].x=x-floor(x/sp->box_x)*sp->box_x;	
				coord[particle_count].y=y;
				
				x=x+sp->lattice_a;
				coord[particle_count].phi=lattice_basis[k].alpha;
				particle_count++;
			}
			
			x=x_0+sp->lattice_a*cos_alpha;
			y=y+sp->lattice_b*sin_alpha;
		}
	}	
	sp->n_part=particle_count;
}


void initial_positions(Simulation_Parameters *sp,Lattice_Basis *lattice_basis,Coord *coord,double *alpha,Files file)
{
	long long int i;
	if(strcmp("true",sp->initial_file)==0)					// If initial coordinates are read from a file
	{
		
		file.initial_positions=fopen(sp->initial_path,"r");			// Open input file with coordinates
		read_positions(file.initial_positions,sp,coord);		// Read input file with coordinates
	}
	else 													// If initial coordinates are NOT read from a file
	{
		
		if(strcmp("true",sp->initial_lattice)==0)			//	If particles are placed in a lattice
		{
			initial_basis(sp,lattice_basis,coord);
		}
		else 												// If particles are placed randomly
		{
			for(i=0;i<sp->n_part;i++)						// Give a random value for each particle "i"
			{
				coord[i].x=rand()*sp->box_x/(double)RAND_MAX;
				coord[i].y=rand()*sp->box_y/(double)RAND_MAX;
			}
			if(strcmp("true",sp->oriented_particles)==0)	// If particles have orientation give a random orientation for each particle "i"
			{
				coord[i].phi=(double)(rand()*360.0)/(double)RAND_MAX;
			}		
		}	
	}
}

double cos_tab(Simulation_Parameters *sp,double argument)
{
	return sp->cos_tab[(long long int)floor((double)(argument*trigonometric_bins)/(double)(2*M_PI))];
}

double sin_tab(Simulation_Parameters *sp,double argument)
{	
	return sp->sin_tab[(long long int)floor((double)(argument*trigonometric_bins)/(double)(2.0*M_PI))];
}

double tan_tab(Simulation_Parameters *sp,double argument)
{
	return sp->tan_tab[(long long int)floor((double)(argument*trigonometric_bins)/(double)(2.0*M_PI))];
}

void verlet_list(Simulation_Parameters *sp,Coord *coord)
{
	long int i,j;
	double dx,dy,dis2;
	#pragma omp parallel private(j,dx,dy,dis2)
	{
	#pragma omp for
	for(i=0;i<sp->n_part;i++)
	{
		coord[i].n_verlet=0;
		
		//~ for(j=0;j<maxver;j++)
		//~ {
			//~ particle[i].ver.list[j]=0;
		//~ }
		coord[i].ver_x=coord[i].x;
		coord[i].ver_y=coord[i].y;

		for(j=0;j<sp->n_part;j++)
		{
			
			if(j!=i)
			{
				
				dx=displacement_x(sp,coord[i].x,coord[j].x);
				
				if(fabs(dx)<=sp->verlet_radius)
				{
					dy=displacement_y(sp,coord[i].y,coord[j].y);
					if(fabs(dy)<=sp->verlet_radius)
					{
						dis2=pow(dx,2)+pow(dy,2);
						if(dis2<sp->verlet_radius_2)
						{
							coord[i].verlet[coord[i].n_verlet]=j;
							coord[i].n_verlet+=1;
						}
					}
				}
			}
		}
					
	}
	}
	
			
}

void verlet_check(Simulation_Parameters *sp,Coord *coord,uint64_t ii)
{
	double deltax,deltay,delta;
				
	deltax=coord[ii].x-coord[ii].ver_x;
	deltax=deltax-sp->box_x*round((double)deltax/(double)sp->box_x);
	deltay=coord[ii].y-coord[ii].ver_y;
	deltay=deltay-sp->box_y*round((double)deltay/(double)sp->box_y);		
	
	delta=deltax*deltax+deltay*deltay;
	if(delta>sp->lim_2)
	{
		verlet_list(sp,coord);	
	}	
	
}

double energy_verlet(Rel_Coord *rel_coord,Coord *coord,Simulation_Parameters *sp,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord),long long int i)
{
	double En,dx,dy,dis2;
	long int j,jj;
	En=0;
	for(jj=0;jj<coord[i].n_verlet;jj++)
	{
		j=coord[i].verlet[jj];						
		dx=displacement_x(sp,coord[i].x,coord[j].x);
		dy=displacement_y(sp,coord[i].y,coord[j].y);
		dis2=dx*dx+dy*dy;
		if(dis2<sp->rcut_2)
		{
			rel_coord->r=sqrt(dis2);
			En+=(energy)(sp,rel_coord);
		}
	}
	
	return En;
}	


void dynamic_output(Simulation_Parameters *sp,Sampling_Variables *sv,Files *file,Coord *coord)
{
	long long int i,j;
	fprintf(file->dynamic,"#Step %lld\n",sp->steps_performed);
	for(i=0;i<sp->n_part;i++)
	{
		fprintf(file->dynamic,"%lf\t%lf\t",coord[i].x,coord[i].y);		
		for(j=0;j<sv->particle_properties;j++)
		{
			//~ fprintf(file->dynamic,"%lf\t",sv->particle_properties_values[i][j]);
			fprintf(file->dynamic,"%lf\t",sv->particle_prop_list[j*sp->n_part+i]);
		}	
		fprintf(file->dynamic,"\n");
	}
}

double periodic_boundary_conditions(double position,double amplitude)
{
	return position-amplitude*(floor(position/amplitude));
}

void histogram(long long int *histogram,double width,double min,long long int bins_num,double value)
{
	long long int bin;
	bin=(long long int)floor((value-min)/width);
	if(bin<bins_num)
	{
		histogram[bin]++;
	}
}	

double distance(Simulation_Parameters *sp,double x1,double x2,double y1,double y2)
{
	double dx,dy,dis;
	
	dx=x1-x2;
	dy=y1-y2;
	dx=dx-sp->box_x*round(dx/sp->box_x);
	dy=dy-sp->box_y*round(dy/sp->box_y);
	dis=sqrt(pow(dx,2)+pow(dy,2));
	return dis;
}			

void weighted_bond_orientation(Simulation_Parameters *sp,Sampling_Variables *sv,double dx,double dy,int i,double weight)
{
	double angle;
	
	angle=sv->coordination_number*(atan2(dy,dx));
	angle=fmod(angle+periodic_angles,2*M_PI);
	sv->orientational_param_re[i]=sv->orientational_param_re[i]+weight*cos_tab(sp,(double)(angle));
	sv->orientational_param_im[i]=sv->orientational_param_im[i]+weight*sin_tab(sp,(double)(angle));	
}

