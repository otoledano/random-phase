from enum import Enum

from numpy import long


class SimulationVariables:
    def __init__(self):
        self.num_steps: long = 100  # Number of trial movements performed in the simulation (in millions)
        self.num_processors: int = 2  # Number of processors employed in the simulation
        self.potential_analytic: bool = True  # If true, the potential is calculated analytically for each interaction, if false, it is stored in memory
        self.potential_interpolat: bool = False  # If true, the interaction energy is calculated with trilinear interpolation, if false, it is taken from the nearest point in the table
        self.potential_out: bool = False  # If true, the potential is stored in an output file, if false, it is not.
        self.system_units: SystemUnits = SystemUnits.INTERNAL  # 'Internal' for LJ, Morse or HS internal units, 'Nano' for eV, Angstrom

        self.radial_displacement: float = 0.1  # Amplitude of the longitudinal displacements
        self.angular_displacement: float = 10.0  # Amplitude of the angular displacements in degrees
        self.rdf_precision: float = 0.03  # Width of the rdf grid in length units
        self.cutoff_radius: float = 10.1  # Maximum distance for which energies are computed


class SystemUnits(Enum):
    INTERNAL = "Internal"
    NANO = "Nano"
