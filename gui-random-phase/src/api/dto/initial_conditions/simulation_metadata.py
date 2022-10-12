from src.api.constants.constants import Cts
from src.api.utils.paths import PathTo


class SimulationMetadata:
    def __init__(self):
        self.name: str = ""
        self.state: str = Cts.CONDITIONS_OPEN
        self.route: str = ""
