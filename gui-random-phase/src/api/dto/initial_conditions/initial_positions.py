class InitialPositions:
    def __init__(self):
        self.initial_file: bool = True  # If true, the initial positions are read from a file
        self.initial_path: str = "Default route"  # Path to the input file for the initial positions
        self.initial_lattice: bool = False  # If true, initial positions are placed in a lattice. If not they are placed randomly. It is override if initial positions come from a file
        self.lattice_a: float = 4.0  # Value of the lattice constant "a" (along the X axis)
        self.lattice_b: float = 4.0  # Value of the lattice constant "b" (deprecated)
        self.lattice_alpha: float = 60.0  # Value of the angle between "a" and "b" lattice vectors in degrees (from 0º to 180º)
        self.lattice_elements: int = 2  # Number of particles present in each unit cell of the lattice
        self.lattice_coordinates = [(0.0, 0.0, None), (0.5, 0.5, None)]  # Block containing the specie index and coordinates of the different atoms that are in each unit cell
                    # The first and second columns are the "x" and "y" fractional coordinates. A third column must be supplied if the particles have orientation,
                    # describing their orientation respect to the X axis in degrees. Fractional coordinates in the range [0,1]
