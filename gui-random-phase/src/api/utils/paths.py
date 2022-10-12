from os.path import dirname, abspath, curdir, join

import __main__

"""Module to reference the path to folders and files needed by the gui"""


class PathTo:
    # Path to the root project folder
    # PROJECT_FOLDER: str = dirname(dirname(abspath(curdir)))
    PROJECT_FOLDER: str = dirname(dirname(abspath(__main__.__file__)))

    # Path to  gui-random-phase folder
    GUI_RANDOM_PHASE_FOLDER: str = dirname(abspath(curdir))

    # Path to resources folder
    RESOURCES_FOLDER: str = join(GUI_RANDOM_PHASE_FOLDER, "resources")

    # Path to calculator ico image
    CALC_ICO_IMAGE: str = join(RESOURCES_FOLDER, "calc.ico")

    # Path to simulations folder
    SIMULATIONS_FOLDER: str = join(PROJECT_FOLDER, "simulations")

    # Path to C random phase
    C_RANDOM_PHASE_FOLDER: str = join(PROJECT_FOLDER, "main-random-phase")

    # Path to C executable
    C_EXECUTABLE_FILE: str = join(C_RANDOM_PHASE_FOLDER, "RP.o")

    # Concrete simulation paths
    @staticmethod
    def simulation_folder(simulation_name: str) -> str:
        return join(PathTo.SIMULATIONS_FOLDER, f"simulation_{simulation_name}")

    @staticmethod
    def metadata_file(simulation_name: str) -> str:
        simulation_folder = PathTo.simulation_folder(simulation_name)
        return join(simulation_folder, f"metadata_{simulation_name}.txt")

    @staticmethod
    def initial_conditions_folder(simulation_name: str) -> str:
        simulation_folder = PathTo.simulation_folder(simulation_name)
        return join(simulation_folder, f"initial_conditions_{simulation_name}")

    @staticmethod
    def initial_conditions_file(simulation_name: str) -> str:
        initial_conditions_folder = PathTo.initial_conditions_folder(simulation_name)
        return join(initial_conditions_folder, f"initial_conditions_{simulation_name}.txt")

    @staticmethod
    def results_folder(simulation_name: str) -> str:
        simulation_folder = PathTo.simulation_folder(simulation_name)
        return join(simulation_folder, f"results_{simulation_name}")

    @staticmethod
    def visualizations_folder(simulation_name: str) -> str:
        simulation_folder = PathTo.simulation_folder(simulation_name)
        return join(simulation_folder, f"visualizations_{simulation_name}")

