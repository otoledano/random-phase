
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


#define periodic_angles 12*M_PI
#define pi_2	2*M_PI

void voronoi_partition(Sampling_Variables *sv,Simulation_Parameters *sp,Coord *coord,Rel_Coord *rel_coord,Files *file,double (*energy)(Simulation_Parameters *sp,Rel_Coord *rel_coord))
//~ void voronoi_partition(Parametros_Simulacion *sp,Particle *particle,Sampling_Variables *sam,Files *file,Counters *count,Voronoi *voronoi)
{
	double Dy_2,Dx_2,*s_x,*s_y,*v_x,*v_y,mx,my,med_v_x,med_v_y,x_int,y_int,y1,y3,int_comp,*s_x_new,*s_y_new,*v_x_new,*v_y_new;
	double *area,dx,dy,x_corte_inicio,y_corte_inicio,x_corte_fin,y_corte_fin,x_corte_fin_2,y_corte_fin_2,area_tot;
	long int *s_particle,max_segmentos,i,j,jj,l,k,k_next,n_segmentos,corte_inicio,corte_fin,puntos_nuevos,n_intersecciones;
	long int *s_particle_new;
	short int interseccion,corta;
	
	max_segmentos=100;
	
	s_x=calloc(max_segmentos,sizeof(double));
	s_y=calloc(max_segmentos,sizeof(double));
	v_x=calloc(max_segmentos,sizeof(double));
	v_y=calloc(max_segmentos,sizeof(double));
	s_x_new=calloc(max_segmentos,sizeof(double));
	s_y_new=calloc(max_segmentos,sizeof(double));
	v_x_new=calloc(max_segmentos,sizeof(double));
	v_y_new=calloc(max_segmentos,sizeof(double));
	s_particle=calloc(max_segmentos,sizeof(long int));
	s_particle_new=calloc(max_segmentos,sizeof(long int));
	area=calloc(max_segmentos,sizeof(double));
	Dx_2=(double)sp->box_x/(double)2;
	Dy_2=(double)sp->box_y/(double)2;
	
	if(sv->Orientat_parameter==1)
	{
		sv->global_orientation_re=0;
		sv->global_orientation_im=0;
	}
	for(i=0;i<sp->nmol;i++)			// Para cada una de las partículas (i)
	{								// Creamos el entorno inicial (un cuadrado de lado 3*d centrado en la caja
		coord[i].condensed=1;
		n_segmentos=4;
		s_x[0]=-sp->box_x;			// Puntos de los segmentos del entorno
		s_y[0]=-sp->box_y;
		s_x[1]=-sp->box_x;
		s_y[1]=2*sp->box_y;
		s_x[2]=2*sp->box_x;
		s_y[2]=2*sp->box_y;
		s_x[3]=2*sp->box_x;
		s_y[3]=-sp->box_y;	
		
		v_x[0]=0.0;			//Vectores de los segmentos del entorno
		v_y[0]=1.0;
		v_x[1]=1.0;
		v_y[1]=0.0;
		v_x[2]=0.0;
		v_y[2]=-1.0;
		v_x[3]=-1.0;
		v_y[3]=0.0;	
		
		s_particle[0]=0;
		s_particle[1]=0;
		s_particle[2]=0;
		s_particle[3]=0;
		
		
			
		for(j=0;j<coord[i].n_verlet;j++)		// Para cada uno de los posibles vecinos de la partícula "i"
		{
			corta=0;
			jj=coord[i].verlet[j];
			
			
				//	Aplicar las condiciones de Contorno
				
			if((fabs(coord[i].x-coord[jj].x)<Dx_2)&&(fabs(coord[i].y-coord[jj].y)<Dy_2))
			{
				mx=(double)(coord[i].x+coord[jj].x)/(double)2;		// Hallamos la mediatriz entre "i" y "jj" (vecino de la lista de Verlet)
				med_v_x=coord[jj].y-coord[i].y;
				my=(double)(coord[i].y+coord[jj].y)/(double)2;
				med_v_y=coord[i].x-coord[jj].x;
			}
			else
			{
				if(fabs(coord[i].x-coord[jj].x)>Dx_2)			// Si hay PBC en x
				{
					if(fabs(coord[i].y-coord[jj].y)>Dy_2)		// Y también en Y
					{
						if(coord[i].x>Dx_2)
						{
							if(coord[i].y>Dy_2)
							{
								mx=(double)(coord[i].x+coord[jj].x+sp->box_x)/(double)2;
								med_v_x=coord[jj].y+sp->box_y-coord[i].y;
								my=(double)(coord[i].y+coord[jj].y+sp->box_y)/(double)2;
								med_v_y=coord[i].x-(coord[jj].x+sp->box_x);
							}
							else
							{
								mx=(double)(coord[i].x+coord[jj].x+sp->box_x)/(double)2;
								med_v_x=coord[jj].y-sp->box_y-coord[i].y;
								my=(double)(coord[i].y+coord[jj].y-sp->box_y)/(double)2;
								med_v_y=coord[i].x-(coord[jj].x+sp->box_x);
							}
						}
						else
						{
							if(coord[i].y>Dy_2)
							{
								mx=(double)(coord[i].x+coord[jj].x-sp->box_x)/(double)2;		
								med_v_x=coord[jj].y+sp->box_y-coord[i].y;
								my=(double)(coord[i].y+coord[jj].y+sp->box_y)/(double)2;
								med_v_y=coord[i].x-(coord[jj].x-sp->box_x);
							}
							else
							{
								mx=(double)(coord[i].x+coord[jj].x-sp->box_x)/(double)2;		
								med_v_x=coord[jj].y-sp->box_y-coord[i].y;
								my=(double)(coord[i].y+coord[jj].y-sp->box_y)/(double)2;
								med_v_y=coord[i].x-(coord[jj].x-sp->box_x);
							}
						}
					}
					else 				// Si hay PBC en x pero no en Y.
					{
						if(coord[i].x>Dx_2)
						{
							mx=(double)(coord[i].x+coord[jj].x+sp->box_x)/(double)2;
							med_v_x=coord[jj].y-coord[i].y;
							my=(double)(coord[i].y+coord[jj].y)/(double)2;
							med_v_y=coord[i].x-(coord[jj].x+sp->box_x);
						}
						else
						{
							mx=(double)(coord[i].x+coord[jj].x-sp->box_x)/(double)2;		
							med_v_x=coord[jj].y-coord[i].y;
							my=(double)(coord[i].y+coord[jj].y)/(double)2;
							med_v_y=coord[i].x-(coord[jj].x-sp->box_x);
						}
					}
				}
				else					// Si hay PBC sólo en Y
				{
					if(coord[i].y>Dy_2)
					{
						mx=(double)(coord[i].x+coord[jj].x)/(double)2;	
						med_v_x=coord[jj].y+sp->box_y-coord[i].y;
						my=(double)(coord[i].y+coord[jj].y+sp->box_y)/(double)2;
						med_v_y=coord[i].x-coord[jj].x;
					}
					else
					{
						mx=(double)(coord[i].x+coord[jj].x)/(double)2;
						med_v_x=coord[jj].y-sp->box_y-coord[i].y;
						my=(double)(coord[i].y+coord[jj].y-sp->box_y)/(double)2;
						med_v_y=coord[i].x-coord[jj].x;
					}
				}
			}
					// Fin Periodic Boundary Conditions
			n_intersecciones=0;			
			for(k=0;k<n_segmentos;k++)				// Para cada uno de los segmentos del entorno de "i"
			{
				
				k_next=k+1;
				if(k_next==n_segmentos)
				{
					k_next=0;
				}
				
				if((med_v_x==0)&&(v_x[k]==0))
				{
					interseccion=0;
				}
				else if(v_x[k]==0)
				{
					x_int=s_x[k];
					y_int=((double)med_v_y/(double)med_v_x)*(x_int-mx)+my;
					int_comp=(double)(y_int-s_y[k])/(double)(s_y[k_next]-s_y[k]);
					if((int_comp>0)&&(int_comp<1))
					{
						interseccion=1;
					}
					else
					{
						interseccion=0;
					}
				}
				else if(med_v_x==0)
				{
					x_int=mx;
					y_int=((double)v_y[k]/(double)v_x[k])*(mx-s_x[k])+s_y[k];
					int_comp=(double)(x_int-s_x[k]/(double)(s_x[k_next]-s_x[k]));
					if((int_comp>0)&&(int_comp<1))
					{
						interseccion=1;
					}
					else
					{
						interseccion=0;
					}
				}
				else if((double)v_y[k]/(double)v_x[k]==(double)med_v_y/(double)med_v_x)
				{
					interseccion=0;
				}
				else
				{
					x_int=(double)(my-s_y[k]+((double)(v_y[k]*s_x[k])/(double)v_x[k])-((double)(med_v_y*mx)/(double)med_v_x))/(double)(((double)v_y[k]/(double)v_x[k])-((double)med_v_y/(double)med_v_x));
					y_int=((double)v_y[k]/(double)v_x[k])*(x_int-s_x[k])+s_y[k];
					int_comp=(double)(x_int-s_x[k])/(double)(s_x[k_next]-s_x[k]);
					if((int_comp>0)&&(int_comp<1))
					{
						interseccion=1;
					}
					else
					{
						interseccion=0;
					}
				}
	
				
				if(interseccion==1)		// Si la mediatriz corta al entorno de "i"
				{
					n_intersecciones++;
					corta=1;
					if(med_v_x!=0)
					{
						y1=s_y[k]-(((double)med_v_y/(double)med_v_x)*(s_x[k]-mx)+my);					// apuntamos el segmento donde corta la mediatriz y cual es el punto que quedaría fuera de los dos posibles
						y3=coord[i].y-(((double)med_v_y/(double)med_v_x)*(coord[i].x-mx)+my);
					}
					else
					{
						y1=s_x[k]-mx;
						y3=coord[i].x-mx;
					}
					if(((double)y1/(double)y3)>=0)		// Si el punto del segmento que sigue formando parte del enotrno es "k", no "k_next", marcamos ese punto como 
					{									// el inicio del tramo que quedará excluido. Este será "corte_inicio"
						corte_inicio=k;
						y_corte_inicio=y_int;
						x_corte_inicio=x_int;
						//~ printf("Inicio\t%ld\t%ld\t%ld\t%lf\t%lf\n",corte_inicio,n_intersecciones,j,x_int,y_int);
					}
					else 								// Si el punto del segmento que queda excluido del entorno es "k" lo marcamos como el final del tramo que quedará excluido
					{										// Este será "corte_fin"
						corte_fin=k;
						y_corte_fin=y_int;
						x_corte_fin=x_int;
						y_corte_fin_2=s_y[k_next];
						x_corte_fin_2=s_x[k_next];
						//~ printf("Fin\t%ld\t%ld\t%ld\t%lf\t%lf\n",corte_fin,n_intersecciones,j,x_int,y_int);	
					}
														
										// Excluiremos todos los puntos entre "corte_inicio+1" y "corte_fin".
										// Tenemos en cuenta que si "corte_inicio">"corte_fin" hay que unir el elemento "n_segmentos" con el "0" 
				}
			}

			if(corta==1)
			{
				if(corte_inicio<corte_fin)
				{

					puntos_nuevos=2-(corte_fin-corte_inicio);
										
					for(l=0;l<n_segmentos+puntos_nuevos-2;l++)
					{
						s_x_new[l]=s_x[l+corte_fin+1-n_segmentos*(int)floor((double)(l+corte_fin+1)/(double)(n_segmentos))];
						s_y_new[l]=s_y[l+corte_fin+1-n_segmentos*(int)floor((double)(l+corte_fin+1)/(double)(n_segmentos))];
						v_x_new[l]=v_x[l+corte_fin+1-n_segmentos*(int)floor((double)(l+corte_fin+1)/(double)(n_segmentos))];
						v_y_new[l]=v_y[l+corte_fin+1-n_segmentos*(int)floor((double)(l+corte_fin+1)/(double)(n_segmentos))];
						s_particle_new[l]=s_particle[l+corte_fin+1-n_segmentos*(int)floor((double)(l+corte_fin+1)/(double)(n_segmentos))];
					}
					
					s_x[n_segmentos+puntos_nuevos-2]=x_corte_inicio;
					s_y[n_segmentos+puntos_nuevos-2]=y_corte_inicio;
					v_x[n_segmentos+puntos_nuevos-2]=x_corte_fin-x_corte_inicio;
					v_y[n_segmentos+puntos_nuevos-2]=y_corte_fin-y_corte_inicio;
					s_particle_new[n_segmentos+puntos_nuevos-2]=jj;
					
					s_x[n_segmentos+puntos_nuevos-1]=x_corte_fin;
					s_y[n_segmentos+puntos_nuevos-1]=y_corte_fin;
					v_x[n_segmentos+puntos_nuevos-1]=x_corte_fin_2-x_corte_fin;
					v_y[n_segmentos+puntos_nuevos-1]=y_corte_fin_2-y_corte_fin;	
					s_particle_new[n_segmentos+puntos_nuevos-1]=s_particle[corte_fin];
					
					for(l=0;l<n_segmentos+puntos_nuevos-2;l++)
					{
						s_x[l]=s_x_new[l];
						s_y[l]=s_y_new[l];
						v_x[l]=v_x_new[l];
						v_y[l]=v_y_new[l];
						s_particle[l]=s_particle_new[l];
					}
					s_particle[n_segmentos+puntos_nuevos-2]=s_particle_new[n_segmentos+puntos_nuevos-2];
					s_particle[n_segmentos+puntos_nuevos-1]=s_particle_new[n_segmentos+puntos_nuevos-1];
					
				}
				else
				{
					puntos_nuevos=2-(corte_fin+n_segmentos-corte_inicio);	
					
					for(l=0;l<n_segmentos+puntos_nuevos-2;l++)
					{
						s_x_new[l]=s_x[l+corte_fin+1-n_segmentos*(int)floor((double)(l+corte_fin+1)/(double)(n_segmentos))];
						s_y_new[l]=s_y[l+corte_fin+1-n_segmentos*(int)floor((double)(l+corte_fin+1)/(double)(n_segmentos))];
						v_x_new[l]=v_x[l+corte_fin+1-n_segmentos*(int)floor((double)(l+corte_fin+1)/(double)(n_segmentos))];
						v_y_new[l]=v_y[l+corte_fin+1-n_segmentos*(int)floor((double)(l+corte_fin+1)/(double)(n_segmentos))];
						s_particle_new[l]=s_particle[l+corte_fin+1-n_segmentos*(int)floor((double)(l+corte_fin+1)/(double)(n_segmentos))];
					}
					
					
					s_x[n_segmentos+puntos_nuevos-2]=x_corte_inicio;
					s_y[n_segmentos+puntos_nuevos-2]=y_corte_inicio;
					v_x[n_segmentos+puntos_nuevos-2]=x_corte_fin-x_corte_inicio;
					v_y[n_segmentos+puntos_nuevos-2]=y_corte_fin-y_corte_inicio;
					s_particle_new[n_segmentos+puntos_nuevos-2]=jj;

					
					s_x[n_segmentos+puntos_nuevos-1]=x_corte_fin;
					s_y[n_segmentos+puntos_nuevos-1]=y_corte_fin;
					v_x[n_segmentos+puntos_nuevos-1]=x_corte_fin_2-x_corte_fin;
					v_y[n_segmentos+puntos_nuevos-1]=y_corte_fin_2-y_corte_fin;	
					s_particle_new[n_segmentos+puntos_nuevos-1]=s_particle[corte_fin];	
					
					for(l=0;l<n_segmentos+puntos_nuevos-2;l++)
					{
						s_x[l]=s_x_new[l];
						s_y[l]=s_y_new[l];
						v_x[l]=v_x_new[l];
						v_y[l]=v_y_new[l];
						s_particle[l]=s_particle_new[l];
					}
					s_particle[n_segmentos+puntos_nuevos-2]=s_particle_new[n_segmentos+puntos_nuevos-2];
					s_particle[n_segmentos+puntos_nuevos-1]=s_particle_new[n_segmentos+puntos_nuevos-1];
				
				}
				
				n_segmentos+=puntos_nuevos;
			}	
		}
		
		area_tot=0;
		for(j=0;j<n_segmentos;j++)
		{
			k_next=j+1;
			if(k_next==n_segmentos)
			{
				k_next=0;
			}
			area[j]=sqrt(pow(s_x[j]-s_x[k_next],2)+pow(s_y[j]-s_y[k_next],2));
			if(pow(s_x[j]-coord[i].x,2)+pow(s_y[j]-coord[i].y,2)>=(double)sp->verlet_radius_2/(double)4)
			{
				coord[i].condensed=0;
			}
			area_tot+=area[j];
		}
		
	
		
		coord[i].n_neighbor=0;
		sv->orientational_param_re[i]=0;
		sv->orientational_param_im[i]=0;
		//		Añade los vecinos a la lista de vecinos de la partícula i //////
		for(j=0;j<n_segmentos;j++)
		{
			coord[i].n_neighbor++;
			coord[i].voronoi.voronoi_edge_x[coord[i].n_neighbor-1]=s_x[j];
			coord[i].voronoi.voronoi_edge_y[coord[i].n_neighbor-1]=s_y[j];
			
			dx=displacement_x(sp,coord[i].x,coord[s_particle[j]].x);
			dy=displacement_y(sp,coord[i].y,coord[s_particle[j]].y);
			if(sv->Orientat_parameter==1)
			{
				weighted_bond_orientation(sp,sv,dx,dy,i,(double)area[j]/(double)area_tot);	
					
			}
			coord[i].voronoi.neighbor_list[coord[i].n_neighbor]=s_particle[j];
		}
		if(sv->Orientat_parameter==1)
		{
			sv->particle_prop_list[sv->samp_particle_prop*sp->n_part+i]=sqrt(pow(sv->orientational_param_re[i],2)+pow(sv->orientational_param_im[i],2));
			sv->particle_prop_list[(sv->samp_particle_prop+1)*sp->n_part+i]=fmod(atan2(sv->orientational_param_im[i],sv->orientational_param_re[i])+periodic_angles,pi_2);	
			sv->global_orientation_re+=sv->orientational_param_re[i];
			sv->global_orientation_im+=sv->orientational_param_im[i];
		}
	}
	if(sv->Orientat_parameter==1)
	{
		sv->samp_particle_prop+=2;
		sv->global_orientation_mod=sqrt(pow(sv->global_orientation_re,2)+pow(sv->global_orientation_im,2))/(double)sp->n_part;
		sv->global_orientation_phase=fmod(atan2(sv->global_orientation_im,sv->global_orientation_re)+periodic_angles,pi_2);	
		fprintf(file->orientation_parameter_out,"%lld\t%lf\t\t%lf\n",sp->steps_performed,sv->global_orientation_mod,sv->global_orientation_phase);
		fflush(file->orientation_parameter_out);
	}
	//*****************************		Defect's ratio calculation	*********************************
	if(sv->Defect_ratio==1)
	{
		defects_ratio(sp,sv,file,coord);
	}
	//***********************************************************************************************
	
	//***************************		Defect's Radial Distribution Function (rdf)	*****************
	if(sv->Defects_rdf==1)
	{
		defects_rdf(sp,sv,file,coord);
	}
	//************************************************************************************************
}

void voronoi_print(Simulation_Parameters *sp,Sampling_Variables *sv,Files *file,Coord *coord,long long int i,double dx,double dy,int n_segmentos)
{
	long long int j,jj;
	fprintf(file->voronoi_diagram,"%lf\t%lf\t%d\t%d\t",coord[i].x+dx,coord[i].y+dy,coord[i].n_neighbor,coord[i].condensed);		
	for(j=0;j<=n_segmentos;j++)		// Pinta los polígonos normales
	{
		jj=j;
		if(j==n_segmentos)
		{
			jj=0;
		}
		fprintf(file->voronoi_diagram,"%lf\t%lf\t",coord[i].voronoi.voronoi_edge_x[jj]+dx,coord[i].voronoi.voronoi_edge_y[jj]+dy);
	}
	for(j=0;j<sv->particle_properties;j++)
	{
		fprintf(file->voronoi_diagram,"%lf\t",sv->particle_prop_list[j*sp->n_part+i]);
	}	
	
	fprintf(file->voronoi_diagram,"\n");
}	
	

void voronoi_output(Simulation_Parameters *sp,Sampling_Variables *sv,Files *file,Coord *coord)
{
	long int j,i,k_next,n_segmentos;
	short int replica_x,replica_y;
	
	
	for(i=0;i<sp->n_part;i++)
	{
		n_segmentos=coord[i].n_neighbor;
		if(coord[i].condensed==0)
		{
			n_segmentos=1;
			coord[i].voronoi.voronoi_edge_x[0]=coord[i].x;
			coord[i].voronoi.voronoi_edge_y[0]=coord[i].y;
		}
		
		replica_x=0;
		replica_y=0;
		for(j=0;j<n_segmentos;j++)
		{
			k_next=j+1;
			if(k_next==n_segmentos)
			{
				k_next=0;
			}
			
			if(coord[i].voronoi.voronoi_edge_x[j]>sp->box_x)
			{
				replica_x=2;
			}
			if(coord[i].voronoi.voronoi_edge_x[j]<0)
			{
				replica_x=1;
			}
			if(coord[i].voronoi.voronoi_edge_y[j]>sp->box_y)
			{
				replica_y=2;
			}
			if(coord[i].voronoi.voronoi_edge_y[j]<0)
			{
				replica_y=1;
			}
		}
		
		
		voronoi_print(sp,sv,file,coord,i,0.0,0.0,n_segmentos);
		
		
		if(replica_x==1)			//Borde Izquierdo
		{
			if(replica_y==1)		// Borde Izquierdo-Inferior
			{
				voronoi_print(sp,sv,file,coord,i,sp->box_x,sp->box_y,n_segmentos);
				voronoi_print(sp,sv,file,coord,i,sp->box_x,0.0,n_segmentos);
				voronoi_print(sp,sv,file,coord,i,0.0,sp->box_y,n_segmentos);
					
			}
			else if(replica_y==2)	// Borde Izquierdo-Superior
			{
				voronoi_print(sp,sv,file,coord,i,sp->box_x,-sp->box_y,n_segmentos);
				voronoi_print(sp,sv,file,coord,i,sp->box_x,0.0,n_segmentos);
				voronoi_print(sp,sv,file,coord,i,0.0,-sp->box_y,n_segmentos);
			}
			else 					// Borde Izquierdo Solo
			{
				voronoi_print(sp,sv,file,coord,i,sp->box_x,0.0,n_segmentos);
			}
			
		}
		else if(replica_x==2)		// Borde Derecho
		{
			if(replica_y==1)		// Borde Derecho-Inferior
			{
				voronoi_print(sp,sv,file,coord,i,-sp->box_x,sp->box_y,n_segmentos);
				voronoi_print(sp,sv,file,coord,i,-sp->box_x,0.0,n_segmentos);
				voronoi_print(sp,sv,file,coord,i,0.0,sp->box_y,n_segmentos);
				
				
			}
			else if(replica_y==2)	// Borde Derecho-Superior
			{
				voronoi_print(sp,sv,file,coord,i,-sp->box_x,-sp->box_y,n_segmentos);
				voronoi_print(sp,sv,file,coord,i,-sp->box_x,0.0,n_segmentos);
				voronoi_print(sp,sv,file,coord,i,0.0,-sp->box_y,n_segmentos);
			}
			else 					// Borde Derecho Solo
			{
				voronoi_print(sp,sv,file,coord,i,-sp->box_x,0.0,n_segmentos);
			}				
		}
		else 						// Borde Solo vertical
		{
			if(replica_y==1)		// Borde Inferior Solo
			{
				voronoi_print(sp,sv,file,coord,i,0.0,sp->box_y,n_segmentos);
			}
			else if(replica_y==2)	// Borde Superior Solo
			{
				voronoi_print(sp,sv,file,coord,i,0.0,-sp->box_y,n_segmentos);
			}		
		}
	}
	
	fprintf(file->voronoi_diagram,"\n");
	
}	


