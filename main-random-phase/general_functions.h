#pragma once

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


void parametros_char(char* palabra,char* s,int characters,FILE* entrada,char* value);
double parametros(char* palabra,char* s,int characters,FILE* entrada);
double parametros_array(char* palabra,char* s,int characters,FILE* entrada,int elements,double *array);
void parametros_matrix(char* palabra,char* s,int characters,FILE* entrada,int elements_x,int elements_y,double *array);
void reading_input(Simulation_Parameters *sp,Files *file,char* s,long long int characters,Sampling_Variables *sv);
void reading_basis(Lattice_Basis *lattice_basis,Files *file,char* s,long long int characters,Simulation_Parameters sp);
void read_positions(FILE* entrada,Simulation_Parameters *sp,Coord *coord);
void initial_positions(Simulation_Parameters *sp,Lattice_Basis *lattice_basis,Coord *coord,Files file);
void initial_basis(Simulation_Parameters *sp,Lattice_Basis *lattice_basis,Coord *coord);


double cos_tab(Simulation_Parameters *sp,double argument);
double sin_tab(Simulation_Parameters *sp,double argument);
double tan_tab(Simulation_Parameters *sp,double argument);

void verlet_list(Simulation_Parameters *sp,Coord *coord);
void verlet_check(Simulation_Parameters *sp,Coord *coord,uint64_t ii);

double energy_verlet(Rel_Coord *rel_coord,Coord *coord,Simulation_Parameters *sp,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord),long long int i);

void dynamic_output(Simulation_Parameters *sp,Sampling_Variables *sv,Files *file,Coord *coord);

double periodic_boundary_conditions(double position,double amplitude);

void histogram(long long int *histogram,double width,double min,long long int bins_num,double value);

double displacement_x(Simulation_Parameters *sp,double xi,double xj);
double displacement_y(Simulation_Parameters *sp,double yi,double yj);
double distance(Simulation_Parameters *sp,double x1,double x2,double y1,double y2);

void weighted_bond_orientation(Simulation_Parameters *sp,Sampling_Variables *sv,double dx,double dy,int i,double weight);


