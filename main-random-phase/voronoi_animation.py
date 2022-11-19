import numpy as np
import time
from matplotlib import pyplot as plt
from shapely.geometry.polygon import Polygon
from descartes import PolygonPatch

from matplotlib.collections import PolyCollection
import matplotlib as mpl
from matplotlib.colors import LinearSegmentedColormap
from matplotlib import animation
import pdb



num_properties=3		# Number of properties of each particle

lines = []
break_points = []
break_points.append(-1)


x = []
y = []
neighbors = []
condensed = []
vertices_x = []
vertices_y = []
particle_properties = [[] for _ in range(num_properties)]


empty_element = [0]
empty_2 = []
empty_coord = [0,0]
prop = [[]]*num_properties


i=-1
filled_lines=-1
with open('ejemplo_25-9-2022/voronoi_diagram.txt') as file:
    for line in file:
    	i=i+1
    	lines.append(line)
    	
    	if lines[i] == "\n":
    		#break_points.append(i)
    		break_points.append(filled_lines)
    		
    	else:
    		filled_lines+=1
    		splitted_line = lines[i].split("\t")
    		x.append(splitted_line[0])
    		y.append(splitted_line[1])
    		neighbors.append(splitted_line[2])
    		condensed.append(splitted_line[3])
    		vertices_x.append([])
    		vertices_x[-1].extend([empty_element for j in range(0,int(neighbors[-1])+1)])
    		vertices_y.append([])
    		vertices_y[-1].extend([empty_element for j in range(0,int(neighbors[-1])+1)])
    		for j in range (0,int(neighbors[-1])):
    			vertices_x[-1][j]=splitted_line[4+2*j]
    			vertices_y[-1][j]=splitted_line[5+2*j]
    		vertices_x[-1][int(neighbors[-1])]=vertices_x[-1][0]
    		vertices_y[-1][int(neighbors[-1])]=vertices_y[-1][0]
    		
    		
    		#particle_properties[-1].extend([empty_element for j in range(0,num_properties)])
    		
    		for j in range (0,num_properties):
    			particle_properties[j].append(splitted_line[4+2*(int(neighbors[-1])+1)+j])
    			
    			
    		#prop.append([])
    		#prop[-1].extend([empty_element for j in range(0,num_properties)])
    		#prop[-1]=np.asarray(particle_properties[-1], dtype=float)
    		#print(prop[-1])
    		
    			
			
   		
x_float = np.asarray(x, dtype=float)
y_float = np.asarray(y, dtype=float)  

x_vert_float = []
y_vert_float = []

coord = [ [ None for y in range( 1 ) ] for x in range( filled_lines ) ]
for j in range (0,filled_lines):
	
	x_vert_float.extend([empty_element])
	y_vert_float.extend([empty_element])
	x_vert_float [j] = np.asarray(vertices_x[j], dtype=float)
	y_vert_float [j] = np.asarray(vertices_y[j], dtype=float)
		
	for a, b in zip( x_vert_float[j], y_vert_float[j] ):
		coord[j].append([ a, b ])
	coord[j].pop(0)

prop_float = []
for j in range (0,num_properties):
	prop_float.extend([empty_element])
	prop_float [j] = np.asarray(particle_properties[j], dtype=float)
	

#########		Animation	#####################

fig, ax = plt.subplots(figsize=(8,8))

z = np.asarray(neighbors, dtype=float)

#property_plot = np.asarray(prop_float[1])

#z=property_plot

colors = [(1, 0, 0), (0, 1, 0), (0, 0, 1)]
n_bins = 100
cmap_name = 'my_list'
cmap = LinearSegmentedColormap.from_list(cmap_name, colors, N=n_bins)
#cmap='viridis'


plt.xlim([0, 40])
plt.ylim([0, 40])
clim=(5,7)

def init():
    coll = PolyCollection(coord[break_points[0]+1:break_points[1]+1], array=z[break_points[0]+1:break_points[1]+1], cmap=cmap, edgecolors='black',linewidth=0.8,clim=clim)
    ax.add_collection(coll)
    return ax,
    
def animate(i):
    coll = PolyCollection(coord[break_points[i]+1:break_points[i+1]+1], array=z[break_points[i]+1:break_points[i+1]+1], cmap=cmap, edgecolors='black',linewidth=0.8,clim=clim) 
    plt.xlim([0, 40])
    plt.ylim([0, 40])
    ax.add_collection(coll)
    ax.autoscale_view()
    #fig.colorbar(coll, ax=ax)
    return ax,


anim = animation.FuncAnimation(fig, animate, init_func=init,frames=100, interval=2000, blit=True)

Writer = animation.writers['ffmpeg']
writer = Writer(fps=2,metadata= {'artist':'Me'},bitrate=-1,codec="libx264")
anim.save('particle_box.mp4', writer)
pdb.set_trace()
#anim = animation.FuncAnimation(fig, animate, init_func=init, frames=100, interval=2000, blit=True)
#plt.show()
plt.pause(1000)


###########	Voronoi Partition

fig, ax = plt.subplots()

# Make the collection and add it to the plot.
#z = np.random.random(filled_lines) * 500
z = np.asarray(neighbors, dtype=float)
colors = [(1, 0, 0),(1, 0, 0), (0, 1, 0), (0, 0, 1), (0, 0, 1)]
n_bins = 100
cmap_name = 'my_list'

cmap = LinearSegmentedColormap.from_list(cmap_name, colors, N=n_bins)

i=0
with plt.ion():
	while i < 50:
		
		if i == 0:
		
			coll = PolyCollection(coord[0:break_points[0]+1], array=z, cmap=cmap, edgecolors='black',linewidth=0.8,clim=(5,7))
			ax.add_collection(coll)
			ax.autoscale_view()
		
			fig.colorbar(coll, ax=ax, extend='both',boundaries=[5,7])
			plt.xlim([0, 40])
			plt.ylim([0, 40])
	
			plt.show()
			plt.pause(100)
			

		else:
			coll = PolyCollection(coord[break_points[i-1]:break_points[i]+1], array=z, cmap=cmap, edgecolors='black',linewidth=0.8)
			ax.add_collection(coll)
			ax.autoscale_view()
			fig.colorbar(coll, ax=ax)
			
			plt.xlim([0, 40])
			plt.ylim([0, 40])
			plt.show()
			plt.pause(1)
		i+=1	
	






########## Dynamic of the position of particles
i=0
plt.figure(figsize=(8,8))
with plt.ion():
	while i < 50:
		plt.clf()
		if i == 0:	
			plt.scatter(x_float[0:break_points[0]+1], y_float[0:break_points[0]+1],marker='.',color='b')
			plt.xlim([0, 40])
			plt.ylim([0, 40])
			plt.show()
			plt.pause(1)
		else:
			plt.scatter(x_float[break_points[i-1]:break_points[i]+1], y_float[break_points[i-1]:break_points[i]+1],marker='.',color='b')
			plt.xlim([0, 40])
			plt.ylim([0, 40])
			plt.show()
			plt.pause(1)
		
		i+=1
    		
    		
