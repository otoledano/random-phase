from src.api.dto.initial_conditions.initial_conditions import InitialConditions


class ConditionsTemplate:
    @staticmethod
    def fill_template(conditions: InitialConditions) -> str:
        return f"""#########################		Defining the Universe of the Simulation		########################################################

Simulation_Ensemble   '{conditions.universe_simulation.simulation_ensemble}'		# (string) 		2 possibilities: NVT or NPT ensemble. 							
Oriented_Particles	'{conditions.universe_simulation.oriented_particles}'		# (boolean)  		If true, the particle has orientation. 
Potential_Tabulated	'{conditions.universe_simulation.potential_tabulated}'		# (boolean)		If true, the potential must be supplied by in input file, if false, the potential is analytic.
Potential_PATH		'{conditions.universe_simulation.potential_path}'	# (string)	Path for reading the potential file, between simple quotes ''.
Potential_Function	'{conditions.universe_simulation.potential_function}'		# (string)		Possible potential interactions: 'LJ' for Lennard Jones, 'Morse' for Morse interaction, 'HD' for hard discs, 'GB' for Gay Berne elliptical potential (with oriented particles), 'AR' for algebraic repulsion, 'ARA' for algebraic repulsion and attraction.



#################################################################################################################################################

#########################	Defining the Potential interaction and the System Parameters		#########################################

Box_x			{conditions.potential_interaction.box_x}		# (double)		Length of the simulation box in the x axis. Overrided if initial positions are read from file
Box_y			{conditions.potential_interaction.box_y}		# (double)		Length of the simulation box in the y axis. Overrided if initial positions are read from file
Particles_Num		{conditions.potential_interaction.particles_num}		# (long long int)  	Number of particles of each specie. This value is overrided if the particles are placed in a Bravais lattice or initial positions are read from file  

Temperature_Sys  	{conditions.potential_interaction.temperature_sys}		# (double)		Temperature in Kelvin.
Target_Pressure	{conditions.potential_interaction.target_pressure}		# (double) 		Surface pressure targeted in the NPT ensemble in N/m

Dipole_Moment		{conditions.potential_interaction.dipole_moment}		# (double)		Value of the dipolar moment for each specie
Potential_Sigma	{conditions.potential_interaction.potential_sigma}		# (double)		Characteristic length for the potential energy calculation (if it is not obtained from a table) for each specie
Potential_Epsilon	{conditions.potential_interaction.potential_epsilon}		# (double)		Characteristic energy for the potential energy calculation (if it is not obtained from a table) for each specie
Potential_Width	{conditions.potential_interaction.potential_width}		# (double)		Parameter that controls the well width of the Morse potential for each specie
Rigid_Elements		{conditions.potential_interaction.rigid_elements}		# (long long int)	Number of elements contained if the particles have more than one component
Epsilon_EndEnd		{conditions.potential_interaction.epsilon_end_end}		# (double)		Value of the well depth in the end to end configuration for the Gay-Berne potential for each specie
Epsilon_SidSid		{conditions.potential_interaction.epsilon_sid_sid}		# (double)		Value of the well depth in the side to side configuration for the Gay-Berne potential for each specie
Sigma_Par		{conditions.potential_interaction.sigma_par}		# (double)		Value of the mayor axis of the ellipse (must be greater or equal than the minor axis value) for the Gay-Berne potential for each specie
Sigma_Perp		{conditions.potential_interaction.sigma_perp}		# (double)		Value of the minor axis of the ellipse for the Gay-Berne potential for each specie
Mu_Ellipse		{conditions.potential_interaction.mu_ellipse}		# (double)		Value of the exponent mu for the epsilon construction of Gay-Berne potential for each specie
Nu_Ellipse		{conditions.potential_interaction.nu_ellipse}		# (double)		Value of the exponent nu for the epsilon construction of Gay-Berne potential for each specie

Rep_Exponent		{conditions.potential_interaction.rep_exponent}			# (double)		Vale of the exponent of the algebraic repulsive potential
Atr_Exponent		{conditions.potential_interaction.atr_exponent}			# (double)		Vale of the exponent of the algebraic atractive potential (must be smaller than the repulsive)



#################################################################################################################################################

#########################################	Sampling Variables		#################################################################





#################################################################################################################################################

#########################################	Simulation Variables		#################################################################


Num_Steps		{conditions.simulation_variables.num_steps}		# (long long int)	Number of trial movements performed in the simulation (in millions)
Num_Processors		{conditions.simulation_variables.num_processors}		# (int)			Number of processors employed in the simulation
Potential_Analytic	'{conditions.simulation_variables.potential_analytic}'		# (boolean)		If true, the potential is calculated analytically for each interaction, if false, it is stored in memory
Potential_Interpolat	'{conditions.simulation_variables.potential_interpolat}'	# (boolean)		If true, the interaction energy is calculated with trilinear interpolation, if false, it is taken from the nearest point in the table
Potential_Out		'{conditions.simulation_variables.potential_out}'	# (boolean)		If true, the potential is stored in an output file, if false, it is not. 
System_Units		'{conditions.simulation_variables.system_units}'	# (string)		'Internal' for LJ, Morse or HS internal units, 'Nano' for eV, Angstrom

Radial_Disp		{conditions.simulation_variables.radial_displacement}		# (double)		Amplitude of the longitudinal displacements
Angular_Disp		{conditions.simulation_variables.angular_displacement}		# (double)		Amplitude of the angular displacements in degrees.
Rdf_Precision		{conditions.simulation_variables.rdf_precision}		# (double)		Width of the rdf grid in length units
Cutoff_Radius  	{conditions.simulation_variables.cutoff_radius}		# (double)		Maximum distance for which energies are computed





#################################################################################################################################################

#########################################	Initial Positions		#################################################################

Initial_File		'{conditions.initial_positions.initial_file}'		# (boolean)		If true, the initial positions are read from a file
Initial_Path		'{conditions.initial_positions.initial_path}'	# (string)	Path to the input file for the initial positions

Initial_Lattice		'{conditions.initial_positions.initial_lattice}'		# (boolean)		If true, initial positions are placed in a lattice. If not they are placed randomly. It is overrided if initial positions come from a file

Lattice_a		{conditions.initial_positions.lattice_a}		# (double)		Value of the lattice constant "a" (along the X axis)
Lattice_b		{conditions.initial_positions.lattice_b}		# (double)		Value of the lattice constant "b" (deprecated
Lattice_alpha		{conditions.initial_positions.lattice_alpha}		# (double)		Value of the angle between "a" and "b" lattice vectors in degrees (from 0º to 180º)
Lattice_Elements	{conditions.initial_positions.lattice_elements}		# (int)			Number of particles present in each unit cell of the lattice


					# Block containing the specie index and coordinates of the different atoms that are in each unit cell
					# The first and second columns are the "x" and "y" fractional coordinates. A third column must be suplied if the particles have orientation, describing their orientation respect to the X axis in degrees. Fractional coordinates in the range [0,1]
%Begin_Lattice_Coordinates		
0.0 0.0		
0.5 0.5	
%End_Lattice_Coordinates


#################################################################################################################################################"""
