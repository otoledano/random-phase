from tkinter import ttk

from src.api.constants.constants import Cts
from src.templates.visualization_frame.visualization_max_content import VisualizationMaxContent
from src.templates.visualization_frame.visualization_standard_content import VisualizationStandardContent


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
        self.panel_standard_content = None
        self.panel_minimized_content = None

        # Non visual variables
        self.parent: Content = parent
        self.service = service
        self.size = Cts.STANDARD_SIZE
        self.name = Cts.CONDITIONS_FRAME

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
        self.label_panel_title.config(text="Initial conditions", anchor="center")
        self.label_panel_title.grid(Cts.GRID_0_0, sticky="EW")

        # Size Buttons
        self.button_minimize = ttk.Button(self.labelframe_title)
        self.button_minimize.config(text="_", width=3, command=self.minimize)
        self.button_minimize.grid(Cts.GRID_0_1, sticky="E")

        self.button_maximize = ttk.Button(self.labelframe_title)
        self.button_maximize.config(text="*", width=3, command=self.maximize)
        self.button_maximize.grid(Cts.GRID_0_2, sticky="E")

        # Content frames depending on the size
        self.panel_standard_content = VisualizationStandardContent(self, self.service)
        self.panel_standard_content.grid(Cts.GRID_1_0)

        self.panel_maximized_content = VisualizationMaxContent(self, self.service)
        self.panel_maximized_content.grid(Cts.GRID_1_0)
        self.panel_maximized_content.grid_remove()

    def layout(self):
        self.columnconfigure(0, weight=1)

    def minimize(self):
        if self.size == Cts.MAXIMIZED_SIZE:
            self.parent.handle_size_change(self.name, Cts.STANDARD_SIZE)
        elif self.size == Cts.STANDARD_SIZE:
            self.parent.handle_size_change(self.name, Cts.MINIMIZED_SIZE)

    def maximize(self):
        if self.size == Cts.STANDARD_SIZE:
            self.parent.handle_size_change(self.name, Cts.MAXIMIZED_SIZE)
        elif self.size == Cts.MINIMIZED_SIZE:
            self.parent.handle_size_change(self.name, Cts.STANDARD_SIZE)

    def activate_minimized_size(self):
        self.label_panel_title.grid_remove()
        self.button_minimize.grid_remove()
        self.button_maximize.grid()
        self.panel_standard_content.grid_remove()
        self.panel_maximized_content.grid_remove()
        self.size = Cts.MINIMIZED_SIZE

    def activate_standard_size(self):
        self.label_panel_title.grid()
        self.button_minimize.grid()
        self.button_maximize.grid()
        self.panel_standard_content.grid()
        self.panel_maximized_content.grid_remove()
        self.size = Cts.STANDARD_SIZE

    def activate_maximized_size(self):
        self.label_panel_title.grid()
        self.button_minimize.grid()
        self.button_maximize.grid_remove()
        self.panel_standard_content.grid_remove()
        self.panel_maximized_content.grid()
        self.size = Cts.MAXIMIZED_SIZE
