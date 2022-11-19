from src.api.constants.constants import Cts
from src.api.models.conditions.conditions import Conditions
from src.api.mappers.mapper import Mapper
from src.repository.c_random_phase import CRandomPhase

from src.repository.conditions_repository import ConditionsRepository
from src.repository.simulation_repository import SimulationRepository


class Service:
    """Class made for managing all the business logic of the app
    MODIFY Has to be refactored in different classes for more specific purposes"""

    def __init__(self):
        self.simulation_repository = SimulationRepository()
        self.conditions_repository = ConditionsRepository()

    def simulation_exists(self, simulation_name: str) -> bool:
        return self.simulation_repository.exists(simulation_name)

    def run_simulation(self, simulation_name: str):
        c_random_phase = CRandomPhase()
        c_random_phase.run(simulation_name)

    def save_conditions(self, initial_conditions: Conditions):
        simulation_name = initial_conditions.simulation_metadata.name
        conditions_csv_text = Mapper.to_csv_text(initial_conditions)
        if self.simulation_exists(simulation_name):
            self.conditions_repository.override(simulation_name, conditions_csv_text)
            self.simulation_repository.update_state(Cts.CONDITIONS_OPEN)
        else:
            self.simulation_repository.new_folder_structure(simulation_name)
            self.conditions_repository.override(simulation_name, conditions_csv_text)
            self.simulation_repository.update_state(Cts.CONDITIONS_OPEN)


