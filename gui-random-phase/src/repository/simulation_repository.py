import os

from src.api.utils.paths import PathTo


class SimulationRepository:

    def exists(self, simulation_name: str) -> bool:
        simulation_folder = PathTo.simulation_folder(simulation_name)
        return os.path.exists(simulation_folder)

    def new_folder_structure(self, simulation_name):
        os.chdir(PathTo.SIMULATIONS_FOLDER)
        os.mkdir(f"simulation_{simulation_name}")
        os.chdir((PathTo.simulation_folder(simulation_name)))
        os.mkdir(f"conditions_{simulation_name}")
        os.mkdir(f"results_{simulation_name}")
        os.mkdir(f"visualizations_{simulation_name}")

    def create_new_simulation(self, simulation_name, initial_conditions):
        self.new_folder_structure(simulation_name)
        PathTo.conditions_folder()

    def update_state(self, new_state):
        pass

