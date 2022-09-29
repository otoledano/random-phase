from enum import Enum


class UniverseSimulation:
    def __init__(self):
        self.simulation_ensemble: SimulationEnsemble = SimulationEnsemble.NVT  # NVT or NPT ensemble
        self.oriented_particles: bool = False  # If true, the particle has orientation
        self.potential_tabulated: bool = False  # If true, the potential must be supplied by in input file, if false, the potential is analytic
        self.potential_path: str = "Route to the file"  # Path for reading the potential file, between simple quotes ''
        self.potential_function: PotentialFunction = PotentialFunction.LJ  # ossible potential interactions: 'LJ' for Lennard Jones,
            # 'Morse' for Morse interaction, 'HD' for hard discs, 'GB' for Gay Berne elliptical potential (with oriented particles),
            # 'AR' for algebraic repulsion, 'ARA' for algebraic repulsion and attraction.


class SimulationEnsemble(Enum):
    NVT = "NVT"
    NPT = "NPT"


class PotentialFunction(Enum):
    LJ = "LJ"  # Leonard Jones
    MORSE = "Morse"
    HD = "HD"  # Hard discs
    GB = "GB"  # Gay Berne
    AR = "AR"  # Algebraic repulsion
    ARA = "ARA"  # Algebraic repulsion and attraction
