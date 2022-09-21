from tkinter import ttk

from src.api.constants.constants import Cts
from src.service.service import Service
from src.templates.conditions_frame.conditions_frame import ConditionsFrame
from src.templates.results_frame.results_frame import ResultsFrame
from src.templates.visualization_frame.visualization_frame import VisualizationFrame


class Content(ttk.Frame):
    """Main panel which stores all the global data of the application.
    Also acts as a controller organizing his siblings open, close and data transfer operations
    Initializes the tabs and the status bar"""

    def __init__(self, parent):
        super().__init__(parent)

        # Visual variables
        self.conditions_frame = None
        self.visualization_frame = None
        self.results_frame = None
        self.status_bar = None

        # Non visual variables
        self.parent = parent
        self.service = Service()

        # Initialize
        self.paint()

        # Layout
        self.layout()

    def paint(self) -> None:

        self.conditions_frame = ConditionsFrame(self, self.service)
        self.conditions_frame.config(borderwidth=1, relief="groove")
        self.conditions_frame.grid(**Cts.GRID_0_0, **Cts.STICKY_X)

        self.visualization_frame = VisualizationFrame(self, self.service)
        self.visualization_frame.grid(**Cts.GRID_0_1, **Cts.STICKY_ALL)

        self.results_frame = ResultsFrame(self, self.service)
        self.results_frame.grid(Cts.GRID_0_2, **Cts.STICKY_ALL)

    def layout(self):

        self.columnconfigure(1, weight=1)
        self.columnconfigure(2, weight=1)
