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

void read_potential_input(Simulation_Parameters *sp,Files *file)
{
	long long int i;
	double r;
	
	for(i=0;i<sp->potential_divis;i++)
	{
		fscanf(file->potential_in,"%lf\t%lf\n",&r,&sp->energy_table[i]);
	}
}

void read_potential_input_oriented(Simulation_Parameters *sp,Files *file)
{
	long long int i,j,k;
	double r,theta,phi;
	
	for(i=0;i<sp->potential_divis;i++)
	{
		for(j=0;j<sp->potential_ang_div;j++)
		{
			for(k=0;k<sp->potential_ang_div;k++)
			{
				fscanf(file->potential_in,"%lf\t%lf\t%lf\t%lf\n",&r,&theta,&phi,&sp->energy_table[i+j*sp->potential_divis+k*sp->bins_phi]);
			}
		}		
	}	
}

double energy_tabulated(Simulation_Parameters *sp,Rel_Coord *rel_coord)
{
	return sp->energy_table[(long long int)round(rel_coord->r/sp->e_bin_width)];
}

double energy_oriented_tabulated(Simulation_Parameters *sp,Rel_Coord *rel_coord)
{
	long long int r_bin,theta_bin,phi_bin;
	r_bin=(long long int)round(rel_coord->r/sp->e_bin_width);
	theta_bin=(long long int)round(rel_coord->theta/sp->e_bin_ang_width);
	if(theta_bin==sp->potential_ang_div)
	{
		theta_bin=0;
	}	
	phi_bin=(long long int)round(rel_coord->phi/sp->e_bin_ang_width);
	if(phi_bin==sp->potential_ang_div)
	{
		phi_bin=0;
	}
	return sp->energy_table[r_bin+theta_bin*sp->potential_divis+phi_bin*sp->bins_phi];
}


double energy_interpolated(Simulation_Parameters *sp,Rel_Coord *rel_coord)
{
	double e1,e2,c;
	long long int bin_e;
	
	bin_e=(long long int)floor(rel_coord->r/sp->e_bin_width);
	e1=sp->energy_table[bin_e];
	e2=sp->energy_table[bin_e+1];
	c=(rel_coord->r-bin_e*sp->e_bin_width)/sp->e_bin_width;
	
	return c*e1+(1-c)*e2;
}

double energy_trilinear_interpolated(Simulation_Parameters *sp,Rel_Coord *rel_coord)
{
	double E000,E001,E010,E011,E100,E101,E110,E111,c00,c01,c10,c11,c0,c1,dr,dtheta,dphi,energy;
	long long int r_bin0,r_bin1,theta_bin0,theta_bin1,phi_bin0,phi_bin1;
	
	
	r_bin0=(long long int)floor(rel_coord->r/sp->e_bin_width);
	r_bin1=r_bin0+1;	
	theta_bin0=(long long int)round(rel_coord->theta/sp->e_bin_ang_width);
	if(theta_bin0==sp->potential_ang_div)
	{
		theta_bin0=0;
	}
	theta_bin1=theta_bin0+1;
	if(theta_bin1==sp->potential_ang_div)
	{
		theta_bin1=0;
	}	
	phi_bin0=(long long int)round(rel_coord->phi/sp->e_bin_ang_width);
	if(phi_bin0==sp->potential_ang_div)
	{
		phi_bin0=0;
	}
	phi_bin1=phi_bin0+1;
	if(phi_bin1==sp->potential_ang_div)
	{
		phi_bin1=0;
	}	
	
	E000=sp->energy_table[r_bin0+theta_bin0*sp->potential_divis+phi_bin0*sp->bins_phi];
	E010=sp->energy_table[r_bin0+theta_bin1*sp->potential_divis+phi_bin0*sp->bins_phi];
	E100=sp->energy_table[r_bin0+theta_bin0*sp->potential_divis+phi_bin1*sp->bins_phi];
	E110=sp->energy_table[r_bin0+theta_bin1*sp->potential_divis+phi_bin1*sp->bins_phi];
	
	
	if(r_bin1==sp->potential_divis)
	{
		E001=0;
		E011=0;
		E101=0;
		E111=0;
	}
	else
	{
		E001=sp->energy_table[r_bin1+theta_bin0*sp->potential_divis+phi_bin0*sp->bins_phi];
		E011=sp->energy_table[r_bin1+theta_bin1*sp->potential_divis+phi_bin0*sp->bins_phi];
		E101=sp->energy_table[r_bin1+theta_bin0*sp->potential_divis+phi_bin1*sp->bins_phi];
		E111=sp->energy_table[r_bin1+theta_bin1*sp->potential_divis+phi_bin1*sp->bins_phi];
	}
	dr=(sp->e_bin_width*r_bin1-rel_coord->r)/sp->e_bin_width;
	if(theta_bin1!=0)
	{
		dtheta=(sp->e_bin_ang_width*theta_bin1-rel_coord->theta)/sp->e_bin_ang_width;
	}	
	else
	{
		dtheta=(sp->e_bin_ang_width*sp->potential_ang_div-rel_coord->theta)/sp->e_bin_ang_width;
	}	
	if(phi_bin1!=0)
	{
		dphi=(sp->e_bin_ang_width*phi_bin1-rel_coord->phi)/sp->e_bin_ang_width;
	}	
	else
	{
		dphi=(sp->e_bin_ang_width*sp->potential_ang_div-rel_coord->phi)/sp->e_bin_ang_width;
	}	
	
	c00=E000*(1-dr)+E001*dr;
	c01=E100*(1-dr)+E101*dr;
	c10=E010*(1-dr)+E011*dr;
	c11=E110*(1-dr)+E111*dr;
	c0=c00*(1-dtheta)+c10*dtheta;
	c1=c01*(1-dtheta)+c11*dtheta;
	energy=c0*(1-dphi)+c1*dphi;
	
	
	return energy;
}

double lennard_jones_interaction(Simulation_Parameters *sp,Rel_Coord *rel_coord)
{
	double energy,sigma_6;
	sigma_6=pow(sp->potential_sigma/rel_coord->r,6);
	energy=4*sp->potential_epsilon*(pow(sigma_6,2)-sigma_6);
	
	return energy-sp->energy_cutoff;
}

double morse_interaction(Simulation_Parameters *sp,Rel_Coord *rel_coord)
{
	double energy;
	
	energy=sp->potential_epsilon*pow((1-exp(-sp->potential_width*(rel_coord->r-sp->potential_sigma))),2);
	
	return energy-sp->energy_cutoff;
}


double algebraic_repulsion_interaction(Simulation_Parameters *sp,Rel_Coord *rel_coord)
{
	double energy;
	
	energy=sp->potential_epsilon*pow(rel_coord->r,-sp->rep_exponent);
	
	return energy-sp->energy_cutoff;
}

double algebraic_repulsion_atraction_interaction(Simulation_Parameters *sp,Rel_Coord *rel_coord)
{
	double energy;
	
	energy=sp->potential_epsilon*(pow(rel_coord->r,-sp->rep_exponent)-pow(rel_coord->r,-sp->atr_exponent));
	
	return energy-sp->energy_cutoff;
}

double hard_discs_interaction(Simulation_Parameters *sp,Rel_Coord *rel_coord)
{
	double energy;
	
	if(rel_coord->r>=sp->potential_sigma)
	{
		energy=-sp->k_B*sp->T*100;
	}
	else
	{
		energy=sp->k_B*sp->T*100;
	}	
	return energy;
}

double Gay_Berne_interaction(Simulation_Parameters *sp,Rel_Coord *rel_coord)
{
	double energy,epsilon_1,epsilon_2,epsilon_tot,sigma_tot,pot_term,cos_phi,cos_theta,sin_phi,sin_theta;
	
	cos_phi=cos(rel_coord->phi);
	sin_phi=sin(rel_coord->phi);
	cos_theta=cos(rel_coord->theta);
	sin_theta=sin(rel_coord->theta);
	
	epsilon_1=(double)1/(double)sqrt(1-pow(sp->excentric,2)*pow(cos_phi,2));
	epsilon_2=1-(double)(sp->excentric_prim/(double)2)*((double)pow(sp->alpha_gb*cos_theta+(double)(cos_theta*cos_phi+sin_theta*sin_phi)/(double)sp->alpha_gb,2)/(1+sp->excentric_prim*cos_phi)+(double)pow(sp->alpha_gb*cos_theta-(double)(cos_theta*cos_phi-sin_theta*sin_phi)/(double)sp->alpha_gb,2)/(1-sp->excentric_prim*cos_phi));
	epsilon_tot=sp->potential_epsilon*pow(epsilon_1,sp->nu_ellipse)*pow(epsilon_2,sp->mu_ellipse);
	sigma_tot=sp->sigma_perp*pow(1-(double)(sp->excentric/(double)2)*((double)pow(cos_theta+cos_theta*cos_phi+sin_theta*sin_phi,2)/(1+sp->excentric*cos_phi)+(double)pow(cos_theta-cos_theta*cos_phi-sin_theta*sin_phi,2)/(1-sp->excentric*cos_phi)),-0.5);
	pot_term=(double)sp->sigma_perp/(double)(rel_coord->r-sigma_tot+sp->sigma_perp);
	energy=4*epsilon_tot*(pow(pot_term,12)-pow(pot_term,6));
		
	return energy;
}

double Gay_Berne_dipolar_interaction(Simulation_Parameters *sp,Rel_Coord *rel_coord)
{
	double energy,epsilon_1,epsilon_2,epsilon_tot,sigma_tot,pot_term,cos_phi,cos_theta,sin_phi,sin_theta,dip_dip;
	
	cos_phi=cos(rel_coord->phi);
	sin_phi=sin(rel_coord->phi);
	cos_theta=cos(rel_coord->theta);
	sin_theta=sin(rel_coord->theta);
	
	epsilon_1=(double)1/(double)sqrt(1-pow(sp->excentric,2)*pow(cos_phi,2));
	epsilon_2=1-(double)(sp->excentric_prim/(double)2)*((double)pow(sp->alpha_gb*cos_theta+(double)(cos_theta*cos_phi+sin_theta*sin_phi)/(double)sp->alpha_gb,2)/(1+sp->excentric_prim*cos_phi)+(double)pow(sp->alpha_gb*cos_theta-(double)(cos_theta*cos_phi-sin_theta*sin_phi)/(double)sp->alpha_gb,2)/(1-sp->excentric_prim*cos_phi));
	epsilon_tot=sp->potential_epsilon*pow(epsilon_1,sp->nu_ellipse)*pow(epsilon_2,sp->mu_ellipse);
	sigma_tot=sp->sigma_perp*pow(1-(double)(sp->excentric/(double)2)*((double)pow(cos_theta+cos_theta*cos_phi+sin_theta*sin_phi,2)/(1+sp->excentric*cos_phi)+(double)pow(cos_theta-cos_theta*cos_phi-sin_theta*sin_phi,2)/(1-sp->excentric*cos_phi)),-0.5);
	pot_term=(double)sp->sigma_perp/(double)(rel_coord->r-sigma_tot+sp->sigma_perp);
	energy=4*epsilon_tot*(pow(pot_term,12)-pow(pot_term,6));
	dip_dip=((double)pow(sp->dipole_moment,2)/(double)pow(rel_coord->r,3))*(cos_phi-3*cos_theta*(cos_phi*cos_theta+sin_phi*sin_theta));
	energy+=dip_dip;
		
	return energy;
}


void potential_energy(Simulation_Parameters *sp,double (**energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord),Rel_Coord *rel_coord,Files *file)
{
	long long int i,j,k;
	sp->e_bin_width=sp->cutoff_radius/(double)sp->potential_divis;
	if(sp->Potential_tabulated==0)		// For analytic potential energy functions
	{
		if(sp->Oriented_particles==0)		// For particles without orientation
		{
			if(strcmp("LJ",sp->potential_function)==0)			// Lennard-Jones interaction
			{
				sp->energy_cutoff=4*sp->potential_epsilon*(pow(sp->potential_sigma/sp->cutoff_radius,12)-pow(sp->potential_sigma/sp->cutoff_radius,6));
				
				*energy=&lennard_jones_interaction;
			}
			if(strcmp("Morse",sp->potential_function)==0)		// Morse interaction
			{
				sp->energy_cutoff=sp->potential_epsilon*pow((1-exp(-sp->potential_width*(sp->cutoff_radius-sp->potential_sigma))),2);
				
				*energy=&morse_interaction;
			}
			if(strcmp("AR",sp->potential_function)==0)			// Algebraic repulsion
			{
				sp->energy_cutoff=sp->potential_epsilon*pow(sp->cutoff_radius,-sp->rep_exponent);
				
				*energy=&algebraic_repulsion_interaction;
			}
			if(strcmp("ARA",sp->potential_function)==0)			// Algebraic repulsion and atraction
			{
				sp->energy_cutoff=sp->potential_epsilon*(pow(sp->cutoff_radius,-sp->rep_exponent)-pow(sp->cutoff_radius,-sp->atr_exponent));
				
				*energy=&algebraic_repulsion_atraction_interaction;
			}
			if(strcmp("HD",sp->potential_function)==0)			// Hard-Discs
			{
				sp->energy_cutoff=0;
				
				*energy=&hard_discs_interaction;
			}
			
			if(sp->Potential_analytic==0)	// If potential energy is stored in a table for the calculations (RAM memory)
			{
				sp->energy_table=calloc(sp->potential_divis,sizeof(double));
				for(i=1;i<sp->potential_divis;i++)
				{
					rel_coord->r=(double)(i)*sp->e_bin_width;
					sp->energy_table[i]=(*energy)(sp,rel_coord);
					sp->energy_table[0]=1E100;					// High value for the singularity of the repulsive interaction
				}
				*energy=&energy_tabulated;
				if(sp->Potential_interpolat==1)
				{
					*energy=&energy_interpolated;
				}						
			}
			if(sp->Potential_out==1)							// If potential energy is stored in an output file
			{
				for(i=1;i<sp->potential_divis;i++)
				{
					rel_coord->r=(double)(i)*sp->e_bin_width;
					fprintf(file->potential_out,"%lf\t%lf\t",i*sp->e_bin_width,(*energy)(sp,rel_coord));
				}
			}			
		}
		
		else 								// For oriented particles	
		{
			sp->e_bin_ang_width=M_PI*2/(double)sp->potential_ang_div;
			sp->bins_phi=sp->potential_divis*sp->potential_ang_div;
			
			if(strcmp("GB",sp->potential_function)==0)			// Gay-Berne potential interaction
			{
				sp->energy_cutoff=0;
				sp->excentric=(double)(sp->sigma_par*sp->sigma_par-sp->sigma_perp*sp->sigma_perp)/(double)(sp->sigma_par*sp->sigma_par+sp->sigma_perp*sp->sigma_perp);	
				sp->excentric_prim=(pow(sp->epsilon_sidsid,(double)1/(double)sp->mu_ellipse)-pow(sp->epsilon_endend,(double)1/(double)sp->mu_ellipse))/(double)(pow(sp->epsilon_sidsid,(double)1/(double)sp->mu_ellipse)+pow(sp->epsilon_endend,(double)1/(double)sp->mu_ellipse));
				sp->alpha_gb=sqrt((double)1/(double)(1+pow((double)sp->epsilon_endend/(double)sp->epsilon_sidsid,(double)1/(double)sp->mu_ellipse)));
				
				if(sp->Electric_dipole==1)			// Dipolar interaction potential interaction
				{
					*energy=&Gay_Berne_dipolar_interaction;
				}
				else
				{
					*energy=&Gay_Berne_interaction;
				}	
			}
			
			
			if(sp->Potential_analytic==0)	// If potential energy is stored in a table for the calculations (RAM memory)
			{
				sp->energy_table=calloc(sp->potential_divis*sp->e_bin_ang_width*sp->e_bin_ang_width,sizeof(double));
				for(i=0;i<sp->potential_divis;i++)
				{
					rel_coord->r=(double)(i)*sp->e_bin_width;
					for(j=0;j<sp->potential_ang_div;j++)
					{
						rel_coord->theta=(double)(j)*sp->e_bin_ang_width;
						for(k=0;k<sp->potential_ang_div;k++)
						{
							rel_coord->phi=(double)(k)*sp->e_bin_ang_width;
							if(i==0)
							{
								sp->energy_table[i+j*sp->potential_divis+k*sp->bins_phi]=1E100;					// High value for the singularity of the repulsive interaction
							}	
							else
							{
								sp->energy_table[i+j*sp->potential_divis+k*sp->bins_phi]=(*energy)(sp,rel_coord);
							}
						}
					}		
				}
				*energy=&energy_oriented_tabulated;
				if(sp->Potential_interpolat==1)
				{
					*energy=&energy_trilinear_interpolated;
				}						
			}
			if(sp->Potential_out==1)							// If potential energy is stored in an output file
			{
				for(i=0;i<sp->potential_divis;i++)
				{
					rel_coord->r=(double)(i)*sp->e_bin_width;
					for(j=0;j<sp->potential_ang_div;j++)
					{
						rel_coord->theta=(double)(j)*sp->e_bin_ang_width;
						for(k=0;k<sp->potential_ang_div;k++)
						{
							rel_coord->phi=(double)(k)*sp->e_bin_ang_width;
							fprintf(file->potential_out,"%lf\t%lf\t%lf\t%lf\t",rel_coord->r,rel_coord->theta,rel_coord->phi,(*energy)(sp,rel_coord));
						}
					}
				}
			}	
		}
			
			
								
	}
	
	else 													// If potential energy is read from a file
	{
		file->potential_in=fopen(file->potential_path,"r");
		if(sp->Oriented_particles==0)						// Particles without orientation
		{
			sp->energy_table=calloc(sp->potential_divis,sizeof(double));
			read_potential_input(sp,file);
			*energy=&energy_tabulated;
			
			if(sp->Potential_interpolat==1)					// If energy is interpolated between points in the table
			{
				*energy=&energy_interpolated;
			}
			if(sp->Potential_out==1)							// If potential energy is stored in an output file
			{
				for(i=1;i<sp->potential_divis;i++)
				{
					rel_coord->r=(double)(i)*sp->e_bin_width;
					fprintf(file->potential_out,"%lf\t%lf\t",i*sp->e_bin_width,(*energy)(sp,rel_coord));
				}
			}	
		}
		else 												// Particles with orientation
		{
			sp->energy_table=calloc(sp->potential_divis*sp->e_bin_ang_width*sp->e_bin_ang_width,sizeof(double));
			read_potential_input_oriented(sp,file);
			*energy=&energy_oriented_tabulated;
			
			if(sp->Potential_interpolat==1)					// If energy is interpolated between points in the table (trilinear interpolation)
			{
				*energy=&energy_trilinear_interpolated;
			}
			if(sp->Potential_out==1)							// If potential energy is stored in an output file
			{
				for(i=0;i<sp->potential_divis;i++)
				{
					rel_coord->r=(double)(i)*sp->e_bin_width;
					for(j=0;j<sp->potential_ang_div;j++)
					{
						rel_coord->theta=(double)(j)*sp->e_bin_ang_width;
						for(k=0;k<sp->potential_ang_div;k++)
						{
							rel_coord->phi=(double)(k)*sp->e_bin_ang_width;
							fprintf(file->potential_out,"%lf\t%lf\t%lf\t%lf\t",rel_coord->r,rel_coord->theta,rel_coord->phi,(*energy)(sp,rel_coord));
						}
					}
				}
			}
			
		}
	}
	
		
	
}	
