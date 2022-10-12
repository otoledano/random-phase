import subprocess

from src.api.utils.paths import PathTo


class CConexion:

    def __init__(self, simulation_name: str):
        self.simulation_name: str = simulation_name
        self.simulation_folder_path = PathTo.simulation_folder(self.simulation_name)
        self.initial_conditions_file_path = PathTo.initial_conditions_file(self.simulation_name)

    def is_c_running(self) -> bool:
        return False

    def run_c(self):
        subprocess.call(["gcc", PathTo.C_EXECUTABLE_FILE])
        subprocess.call([PathTo.C_EXECUTABLE_FILE, self.initial_conditions_file_path])

    def stop_c(self):
        pass
