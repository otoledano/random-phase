import tkinter

from src.api.utils.paths import CALC_ICO_PATH
from .content import Content


class Root(tkinter.Tk):
    """The root window. Responsible to manage the menus, state-bars and other window level widgets
    Element at the top of the Tkinter hierarchy"""

    def __init__(self):
        super().__init__()

        # Visual variables
        self.content = None

        # Initialize
        self.paint()

        # Layout of the window
        self.layout()

        # Main loop
        self.mainloop()

    def paint(self):
        # Define window
        self.title("Random Phase GUI Application")
        self.iconbitmap(CALC_ICO_PATH)
        self.geometry('400x400')
        self.resizable(True, True)

        # Creates the content frame and set which is his position and how it grows
        self.content: Content = Content(self)
        self.content.grid(column=0, row=0, sticky="nsew")

    def layout(self):
        self.rowconfigure(0, weight=1)
        self.columnconfigure(0, weight=1)
