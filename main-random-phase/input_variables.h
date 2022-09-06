#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>




typedef struct 
{
	char simulation_ensemble[10],oriented_particles[10],potential_tabulated[10],potential_path[10000],potential_function[30],electric_dipole[10];
	char solvation_effect[10],gay_berne[10],potential_analytic[10],potential_interpolat[10],potential_out[10],system_units[30];
	char initial_lattice[10],bravais_lattice[10],initial_file[10],initial_path[1000];
	int num_processors,lattice_elements;
	long long int num_steps,steps_performed,n_part,potential_divis,potential_ang_div;
	double lattice_a,lattice_b,lattice_alpha,atr_exponent,rep_exponent,k_B;
	double box_x,box_y,T,target_pressure,angular_disp,radial_disp,rdf_precision;
	double cutoff_radius,e_bin_width,e_bin_ang_width;
	long long int nmol,bins_phi,n_sampling,sec_output;
	double dipole_moment,potential_sigma,potential_epsilon,potential_width,epsilon_endend,epsilon_sidsid,sigma_par,sigma_perp,mu_ellipse,nu_ellipse,energy_cutoff;
	short int Potential_analytic,Oriented_particles,Potential_tabulated,Potential_interpolat,Potential_out,Initial_file,Initial_lattice,Electric_dipole;
	double excentric,excentric_prim,alpha_gb; // Gay-berne potential
	double *energy_table;
	double therm_ratio;
} Simulation_Parameters;

typedef struct
{
	double r,theta,phi;
} Rel_Coord;

typedef struct
{
	double x,y,phi;
} Coord;	

typedef struct
{
	double x,y,alpha;
} Lattice_Basis;


