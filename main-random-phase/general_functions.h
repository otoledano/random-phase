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
void reading_input(Simulation_Parameters *sp,Files *file,char* s,long long int characters);
void reading_basis(Lattice_Basis *lattice_basis,Files *file,char* s,long long int characters,Simulation_Parameters sp);
void read_positions(FILE* entrada,Simulation_Parameters *sp,Coord *coord);
void initial_positions(Simulation_Parameters *sp,Lattice_Basis *lattice_basis,Coord *coord,Files file);
void initial_basis(Simulation_Parameters *sp,Lattice_Basis *lattice_basis,Coord *coord);

