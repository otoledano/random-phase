#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

#define max_neighbor 40


typedef struct
{
	double voronoi_edge_x[max_neighbor],voronoi_edge_y[max_neighbor];
	long long int neighbor_list[max_neighbor];
} Voronoi;

typedef struct 
{
	char simulation_ensemble[10],oriented_particles[10],potential_tabulated[10],potential_path[10000],potential_function[30],electric_dipole[10];
	char solvation_effect[10],gay_berne[10],potential_analytic[10],potential_interpolat[10],potential_out[10],system_units[30];
	char initial_lattice[10],bravais_lattice[10],initial_file[10],initial_path[1000];
	int num_processors,lattice_elements;
	long long int num_steps,steps_performed,n_part,potential_divis,potential_ang_div,dynamic_output_freq;
	double lattice_a,lattice_b,lattice_alpha,atr_exponent,rep_exponent,k_B;
	double box_x,box_y,T,target_pressure,angular_disp,radial_disp,rdf_precision;
	double cutoff_radius,e_bin_width,e_bin_ang_width;
	long long int nmol,bins_phi,n_sampling,sec_output,steps_measurement,steps_sec_measurement,trial_movements;
	double dipole_moment,potential_sigma,potential_epsilon,potential_width,epsilon_endend,epsilon_sidsid,sigma_par,sigma_perp,mu_ellipse,nu_ellipse,energy_cutoff;
	short int Potential_analytic,Oriented_particles,Potential_tabulated,Potential_interpolat,Potential_out,Initial_file,Initial_lattice,Electric_dipole;
	double excentric,excentric_prim,alpha_gb; // Gay-berne potential
	double *energy_table,*cos_tab,*sin_tab,*tan_tab;
	double therm_ratio,verlet_radius,verlet_radius_2,lim_2,rcut_2;
	
} Simulation_Parameters;

typedef struct
{
	double r,theta,phi;
} Rel_Coord;

typedef struct
{
	double x,y,phi,ver_x,ver_y,bond_orient_re,bond_orient_im;
	long int *verlet;
	int n_verlet,n_neighbor;
	short int condensed;
	Voronoi voronoi;
} Coord;	

typedef struct
{
	
	double x,y,alpha;
} Lattice_Basis;



typedef struct
{
	char rdf_sampling[10],loc_density_sampling[10],voronoi_construction[10],defect_ratio[10],defects_rdf[10],orientat_parameter[10],energy_profile[10];
	short int Rdf_sampling,Loc_density_sampling,rdf_initial,Voronoi_construction,Defect_ratio,Defects_rdf,defects_rdf_initial,Orientat_parameter,Energy_profile;
	long long int samp_particle_prop,sampling_components,particle_properties,*rdf_histogram,rdf_bins_num,num_samplings,num_therm_samplings,*loc_density_hist;
	long long int defect_count,*defect_list,*defect_rdf_histogram,*plus_def_rdf,*minus_def_rdf,*opposite_def_rdf,*energy_part_histogram,*energy_sys_histogram,energy_bins_hist;
	double energy,*particle_prop_list,rdf_max,loc_density_rad,*local_density_list,*orientational_param_re,*orientational_param_im,*orientational_param_mod,*orientational_param_phase;
	double global_orientation_re,global_orientation_im,global_orientation_mod,global_orientation_phase,energy_hist_width;
	double energy_min_hist,energy_max_hist;
	char loc_dens_dynam_name[20],orient_param_dynam_name[20],orient_phase_dynam_name[20];
	char *particle_properties_name[20];
	int local_density_index,coordination_number,orient_param_mod_index,orient_param_phase_index;
	
} Sampling_Variables;	




