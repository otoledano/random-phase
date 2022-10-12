from tkinter import ttk, StringVar

from src.api.constants.constants import Cts
from src.api.dto.initial_conditions.initial_conditions import InitialConditions


class ConditionsMaxContent(ttk.Frame):
    """FILL"""

    def __init__(self, parent, service):
        super().__init__(parent)
        # Visual variables
        self.button_run_simulation = None
        self.entry_simulation_name = None

        # Non visual variables
        self.parent = parent
        self.service = service

        self.var_simulation_name = StringVar()

        # Initialize
        self.paint()

        # Layout
        self.layout()

    def paint(self) -> None:
        self.button_run_simulation = ttk.Button(self)
        self.button_run_simulation.config(text="New Initial Conditions", command=self.run_simulation)
        self.button_run_simulation.grid(Cts.GRID_0_0, sticky="N", **Cts.PAD_10_2, ipadx=10, ipady=0)

        self.entry_simulation_name = ttk.Entry(self)
        self.entry_simulation_name.config(textvariable=self.var_simulation_name)
        self.entry_simulation_name.grid(Cts.GRID_0_1, sticky="N", **Cts.PAD_10_2)

    def layout(self):
        self.rowconfigure(0, weight=1)
        self.columnconfigure(0, weight=1)

    def run_simulation(self):
        initial_conditions = InitialConditions()
        initial_conditions.simulation_metadata.name = self.var_simulation_name.get()
        self.service.save_initial_conditions(initial_conditions)
