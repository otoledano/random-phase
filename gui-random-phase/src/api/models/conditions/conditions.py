from src.api.models.conditions.initial_positions import InitialPositions
from src.api.models.conditions.potential_interaction import PotentialInteraction
from src.api.models.conditions.simulation_metadata import SimulationMetadata
from src.api.models.conditions.simulation_varialbes import SimulationVariables
from src.api.models.conditions.universe_simulation import UniverseSimulation


class Conditions:

    def __init__(self):
        self.simulation_metadata: SimulationMetadata = SimulationMetadata()
        self.universe_simulation: UniverseSimulation = UniverseSimulation()
        self.potential_interaction: PotentialInteraction = PotentialInteraction()
        self.simulation_variables: SimulationVariables = SimulationVariables()
        self.initial_positions: InitialPositions = InitialPositions()

