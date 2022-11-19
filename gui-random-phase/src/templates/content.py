from tkinter import ttk

from src.api.constants.constants import Cts

from src.service.service import Service
from src.templates.components.status_bar import StatusBar
from src.templates.conditions_frame.conditions_frame import ConditionsFrame
from src.templates.results_frame.results_frame import ResultsFrame
from src.templates.visualization_frame.visualization_frame import VisualizationFrame


class Content(ttk.Frame):
    """Main panel which stores all the global data of the application.
    Also acts as a controller organizing his siblings open, close and data transfer operations
    Initializes the tabs and the status bar"""

    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent
        self.service = Service()

        self.conditions_frame = ConditionsFrame(self, self.service)
        self.visualization_frame = VisualizationFrame(self, self.service)
        self.results_frame = ResultsFrame(self, self.service)
        self.status_bar = StatusBar(self)

        # Display
        self.paint()

    def paint(self) -> None:

        self.grid(Cts.STICKY_ALL)

        self.rowconfigure(0, weight=1)

        self.columnconfigure(0, weight=0)
        self.columnconfigure(1, weight=1)
        self.columnconfigure(2, weight=0)

        self.conditions_frame.config(borderwidth=1, relief="groove")
        self.conditions_frame.grid(**Cts.GRID_0_0, **Cts.STICKY_ALL)

        self.visualization_frame.config(borderwidth=1, relief="groove")
        self.visualization_frame.grid(**Cts.GRID_0_1, **Cts.STICKY_ALL)

        self.results_frame.config(borderwidth=1, relief="groove")
        self.results_frame.grid(**Cts.GRID_0_2, **Cts.STICKY_ALL)

        self.status_bar.grid(Cts.GRID_1_0, columnspan=3)

    def handle_size_change(self, changing_frame, new_size):

        if changing_frame == Cts.CONDITIONS_FRAME:

            if new_size == Cts.MINIMIZED_SIZE:
                self.conditions_frame.activate_minimized_size()
                self.columnconfigure(0, weight=0)
                self.columnconfigure(1, weight=1)
                self.columnconfigure(2, weight=0)

            elif new_size == Cts.STANDARD_SIZE:
                if self.conditions_frame.size == Cts.MAXIMIZED_SIZE:
                    self.conditions_frame.activate_standard_size()
                    self.visualization_frame.activate_standard_size()
                    self.results_frame.activate_standard_size()
                    self.columnconfigure(0, weight=0)
                    self.columnconfigure(1, weight=1)
                    self.columnconfigure(2, weight=0)

                elif self.conditions_frame.size == Cts.MINIMIZED_SIZE:
                    self.conditions_frame.activate_standard_size()
                    self.visualization_frame.activate_standard_size()
                    self.columnconfigure(0, weight=0)
                    self.columnconfigure(1, weight=1)
                    self.columnconfigure(2, weight=0)

            elif new_size == Cts.MAXIMIZED_SIZE:
                self.conditions_frame.activate_maximized_size()
                self.results_frame.activate_minimized_size()
                self.visualization_frame.activate_minimized_size()
                self.columnconfigure(0, weight=1)
                self.columnconfigure(1, weight=0)
                self.columnconfigure(2, weight=0)

        elif changing_frame == Cts.VISUALIZATION_FRAME:
            if new_size == Cts.STANDARD_SIZE:
                self.visualization_frame.activate_standard_size()
                self.conditions_frame.activate_standard_size()
                self.results_frame.activate_standard_size()
                self.columnconfigure(0, weight=0)
                self.columnconfigure(1, weight=1)
                self.columnconfigure(2, weight=0)

            elif new_size == Cts.MAXIMIZED_SIZE:
                self.visualization_frame.activate_maximized_size()
                self.conditions_frame.activate_minimized_size()
                self.results_frame.activate_minimized_size()
                self.columnconfigure(0, weight=0)
                self.columnconfigure(1, weight=1)
                self.columnconfigure(2, weight=0)

        elif changing_frame == Cts.RESULTS_FRAME:

            if new_size == Cts.MINIMIZED_SIZE:
                self.results_frame.activate_minimized_size()
                self.columnconfigure(0, weight=0)
                self.columnconfigure(1, weight=1)
                self.columnconfigure(2, weight=0)

            elif new_size == Cts.STANDARD_SIZE:
                if self.results_frame.size == Cts.MAXIMIZED_SIZE:
                    self.results_frame.activate_standard_size()
                    self.visualization_frame.activate_standard_size()
                    self.conditions_frame.activate_standard_size()
                    self.columnconfigure(0, weight=0)
                    self.columnconfigure(1, weight=1)
                    self.columnconfigure(2, weight=0)

                elif self.results_frame.size == Cts.MINIMIZED_SIZE:
                    self.results_frame.activate_standard_size()
                    self.visualization_frame.activate_standard_size()
                    self.columnconfigure(0, weight=0)
                    self.columnconfigure(1, weight=1)
                    self.columnconfigure(2, weight=0)

            elif new_size == Cts.MAXIMIZED_SIZE:
                self.results_frame.activate_maximized_size()
                self.visualization_frame.activate_minimized_size()
                self.conditions_frame.activate_minimized_size()
                self.columnconfigure(0, weight=0)
                self.columnconfigure(1, weight=0)
                self.columnconfigure(2, weight=1)

    def show_tooltip(self, tooltip_text):
        self.status_bar.set_text(tooltip_text)

    def clear_tooltip(self):
        self.status_bar.set_text("")




