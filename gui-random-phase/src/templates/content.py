from tkinter import ttk
from tkinter.ttk import Notebook

from src.service.service import Service
from src.templates.conditions_frame.conditions_frame import ConditionsFrame
from src.templates.results_frame.results_frame import ResultsFrame


class Content(ttk.Frame):
    """Main panel which stores all the global data of the application.
    Also acts as a controller organizing his siblings open, close and data transfer operations
    Initializes the tabs and the status bar"""

    def __init__(self, parent):
        super().__init__(parent)

        # Visual variables
        self.notebook = None
        self.conditions_frame = None
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
        self.notebook = Notebook(self)
        self.conditions_frame = ConditionsFrame(self.notebook, self.service)
        self.results_frame = ResultsFrame(self.notebook, self.service)
        self.notebook.add(self.conditions_frame, text="Conditions")
        self.notebook.add(self.results_frame, text="Results")
        self.notebook.grid(column=0, row=0, sticky="nsew")

    def layout(self):
        self.rowconfigure(0, weight=1)
        self.columnconfigure(0, weight=1)
