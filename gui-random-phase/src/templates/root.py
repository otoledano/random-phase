import tkinter

from .content import Content
from ..api.constants.constants import Cts
from ..api.utils.paths import PathTo


class Root(tkinter.Tk):
    """The root window. Responsible to manage the menus, state-bars and other window level widgets
    Element at the top of the Tkinter hierarchy"""

    def __init__(self):
        super().__init__()

        # Visual variables
        self.content: Content = Content(self)
        self.menu = None


        # Non Visual variables
        self.window_width = None
        self.window_length = None
        self.menu = None

        # Initialize
        self.paint()

        # Layout of the window
        self.layout()

        # Main loop
        self.mainloop()

    def paint(self):
        # Define window
        self.title("Random Phase GUI Application")
        self.iconbitmap(PathTo.CALC_ICO_IMAGE)

        self.geometry('1200x800')
        self.state('zoomed')
        self.resizable(True, True)

        # Creates the content frame and set which is his position
        self.content.grid(Cts.GRID_0_0)

    def layout(self):
        self.rowconfigure(0, weight=1)
        self.columnconfigure(0, weight=1)



