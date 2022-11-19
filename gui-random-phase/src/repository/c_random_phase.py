import subprocess
from os.path import join

from src.api.utils.paths import PathTo


class CRandomPhase:

    def is_running(self) -> bool:
        return False

    def run(self, simulation_name):
        input_example = join(PathTo.C_RANDOM_PHASE_FOLDER, "input.txt")
        command = PathTo.C_EXECUTABLE_FILE + " " + input_example + " " + PathTo.SIMULATIONS_FOLDER + " " + simulation_name
        subprocess.call(command, shell=True)

    def stop(self):
        pass
