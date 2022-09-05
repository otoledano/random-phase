import tkinter as tk
from src.api.paths import CALC_ICO_PATH
from .content import Content


class Root:
    """The root window. Responsible to manage the menus, state-bars and other window level widgets
    Element at the top of the Tkinter hierarchy"""

    def __init__(self):
        super().__init__()
        self.paint()

    def paint(self):
        # Define window
        root = tk.Tk()
        root.title("Random Phase GUI Application")
        root.iconbitmap(CALC_ICO_PATH)
        root.geometry('400x400')
        root.resizable(True, True)
        Content(root)
        root.mainloop()
