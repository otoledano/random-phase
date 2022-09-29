from numpy import long


class PotentialInteraction:
    def __init__(self):
        self.box_x: float = 40.0  # Length of the simulation box in the x axis. Overrided if initial positions are read from file
        self.box_y: float = 40.0  # Length of the simulation box in the y axis. Overrided if initial positions are read from file
        self.particles_num: long = 500  # Number of particles of each specie. This value is overrided if the particles are placed in a Bravais lattice or initial positions are read from file

        self.temperature_sys: float = 420.0  # Temperature in Kelvin
        self.target_pressure: float = 0.03  # Surface pressure targeted in the NPT ensemble in N/m

        self.dipole_moment: float = 1.5  # Value of the dipolar moment for each specie
        self.potential_sigma: float = 3.5  # Characteristic length for the potential energy calculation (if it is not obtained from a table) for each specie
        self.potential_epsilon: float = 0.01  # Characteristic energy for the potential energy calculation (if it is not obtained from a table) for each specie
        self.potential_width: float = 5.0  # Parameter that controls the well width of the Morse potential for each specie

        self.rigid_elements: long = 2  # Number of elements contained if the particles have more than one component
        self.epsilon_end_end: float = 0.08  # Value of the well depth in the end to end configuration for the Gay-Berne potential for each specie
        self.epsilon_sid_sid: float = 0.10  # Value of the well depth in the side to side configuration for the Gay-Berne potential for each specie
        self.sigma_par: float = 4.9  # Value of the mayor axis of the ellipse (must be greater or equal than the minor axis value) for the Gay-Berne potential for each specie
        self.sigma_perp: float = 3.3  # Value of the minor axis of the ellipse for the Gay-Berne potential for each specie
        self.mu_ellipse: float = 2.0  # Value of the exponent mu for the epsilon construction of Gay-Berne potential for each specie
        self.nu_ellipse: float = 1.0  # Value of the exponent nu for the epsilon construction of Gay-Berne potential for each specie

        self.rep_exponent: float = 12.0  # Vale of the exponent of the algebraic repulsive potential
        self.atr_exponent: float = 6.0  # Vale of the exponent of the algebraic atractive potential (must be smaller than the repulsive)
