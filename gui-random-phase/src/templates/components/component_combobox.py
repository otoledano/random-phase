from tkinter import ttk, StringVar

from src.api.constants.constants import Cts


class ComponentNumberEntry(ttk.Frame):

    def __init__(self, parent, label_text, tooltip_text):
        super().__init__(parent)

        self.parent = parent
        self.label_number = label_text
        self.tooltip_text = tooltip_text

        # Component variables
        self.label = ttk.Label(self)
        self.entry = ttk.Entry(self)
        self.var_entry = StringVar()

        # Initialize
        self.paint()

        # Layout
        self.layout()

    def paint(self):
        self.label.config(text=self.label_text)
        self.label.grid(Cts.GRID_0_0, sticky="EW", pady=(10, 5), padx=(0, 10))

        self.entry.config(textvariable=self.var_entry, width=100)
        self.entry.grid(Cts.GRID_1_0, sticky="EW", pady=(10, 5), padx=(0, 10))

    def layout(self):
        self.rowconfigure(0, weight=1)
        self.rowconfigure(1, weight=1)

    def get_value(self):
        return self.var_entry.get()

    def get_entry(self):
        return self.entry

    def get_label(self):
        return self.label

    def state_readonly(self):
        self.entry.config(state="readonly")

    def state_normal(self):
        self.entry.config(state="normal")