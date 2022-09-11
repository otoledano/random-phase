from tkinter import ttk

from src.templates.conditions_frame.conditions_zone_frames.central_frame import CentralFrame
from src.templates.conditions_frame.conditions_zone_frames.left_frame import LeftFrame
from src.templates.conditions_frame.conditions_zone_frames.right_frame import RightFrame


class ConditionsFrame(ttk.Frame):
    """Tab to create, load or manage conditions files"""

    def __init__(self, parent, service):
        super().__init__(parent)

        # Visual variables
        self.central_frame = None
        self.left_frame = None
        self.right_frame = None

        # Non visual variables
        self.parent = parent
        self.service = service

        # Initialize
        self.paint()

        # Layout
        self.layout()

    def paint(self) -> None:
        self.left_frame = LeftFrame(self, self.service)
        self.left_frame.grid(row=0, column=0)
        self.central_frame = CentralFrame(self, self.service)
        self.central_frame.grid(row=0, column=1)
        self.left_frame = RightFrame(self, self.service)
        self.left_frame.grid(row=0, column=2)

    def layout(self):
        pass
