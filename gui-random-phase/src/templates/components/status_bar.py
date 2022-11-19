from tkinter import ttk, StringVar

from src.api.constants.constants import Cts


class StatusBar(ttk.Frame):

    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent

        self.label_text = ttk.Label(self)
        self.var_text = StringVar()

        # Display
        self.paint()

    def paint(self) -> None:
        self.grid(Cts.STICKY_ALL)
        self.rowconfigure(0, weight=1)

        self.config(borderwidth=1, relief="groove")
        self.label_text.config(text="Status bar", textvariable=self.var_text, anchor="w")
        self.label_text.grid(Cts.GRID_0_0, sticky="EW", padx=(10, 5), pady=3)

    def set_text(self, text):
        self.label_text.config(text=text, foreground="black")

    def set_error(self, text):
        self.label_text.config(text=text, foreground="red")

    def reset(self):
        self.label_text.config(text="")
