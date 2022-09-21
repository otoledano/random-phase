import tkinter as tk
from tkinter import ttk

from src.api.constants.constants import Cts
from src.templates.conditions_frame.maximized_frame import MaximizedFrame


class ConditionsFrame(ttk.Frame):
    """Conditions frame FILL"""

    def __init__(self, parent, service):
        super().__init__(parent)

        # Visual variables
        self.labelframe_title = None
        self.label_panel_title = None
        self.button_minimize = None
        self.button_maximize = None

        self.panel_maximized_content = None
        self.panel_standard_size_content = None
        self.panel_minimized_content = None

        # Non visual variables
        self.parent = parent
        self.service = service
        self.size = Cts.STANDARD_SIZE

        #   Radiobutton action possible values
        self.NEW_CONDITIONS = "new_conditions"
        self.LOAD_CONDITIONS = "load_conditions"
        self.LOAD_TEMPLATE = "load_template"
        self.LOAD_EXAMPLE = "load_example"

        #   Check possible values
        self.COMPLETED_RESULTS = "completed_results"
        self.IN_PROGRESS_RESULTS = "in_progress_results"
        self.COMPLETED_CONDITIONS = "completed_conditions"
        self.INCOMPLETE_CONDITIONS = "incomplete_conditions"

        # Initialize
        self.paint()

        # Layout
        self.layout()

    def paint(self) -> None:

        self.labelframe_title = ttk.Labelframe(self)
        self.labelframe_title.config()
        self.labelframe_title.grid(Cts.GRID_0_0, sticky="NEW")
        self.labelframe_title.columnconfigure(0, weight=1)

        self.label_panel_title = ttk.Label(self.labelframe_title)
        self.label_panel_title.config(text="Initial conditions")
        self.label_panel_title.grid(Cts.GRID_0_0, sticky="EW")

        # Size Buttons
        self.button_minimize = ttk.Button(self.labelframe_title)
        self.button_minimize.config(text="_", width=3, command=self.minimize)
        self.button_minimize.grid(Cts.GRID_0_1, sticky="E")

        self.button_maximize = ttk.Button(self.labelframe_title)
        self.button_maximize.config(text="*", width=3)
        self.button_maximize.grid(Cts.GRID_0_2, sticky="E")

        # Content frames depending on the size
        self.panel_maximized_content = MaximizedFrame(self, self.service)
        self.panel_maximized_content.grid(Cts.GRID_1_0)

    def layout(self):
        self.columnconfigure(0, weight=1)

    def minimize(self):
        if self.size == Cts.STANDARD_SIZE:
            self.label_panel_title.grid_remove()
            self.button_minimize.grid_remove()
            # Default content hide TODO
            # Use a setter to notify content frame
            self.size = Cts.MINIMIZED_SIZE


