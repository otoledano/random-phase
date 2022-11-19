from tkinter import ttk, StringVar

from src.api.constants.constants import Cts


class ComponentTextEntry(ttk.Frame):

    def __init__(self, parent, label_text, tooltip_text):
        super().__init__(parent)

        self.parent = parent
        self.label_text = label_text
        self.tooltip_text = tooltip_text

        # Component variables
        self.label = ttk.Label(self)
        self.text_entry = ttk.Entry(self)
        self.var_text = StringVar()

        # Initialize
        self.paint()

        # Layout
        self.layout()

    def paint(self):
        self.label.config(text=self.label_text)
        self.label.grid(Cts.GRID_0_0, sticky="EW", pady=(10, 5), padx=(0, 10))

        self.text_entry.config(textvariable=self.var_text, width=100)
        self.text_entry.grid(Cts.GRID_1_0, sticky="EW", pady=(10, 5), padx=(0, 10))

    def layout(self):
        self.rowconfigure(0, weight=1)
        self.rowconfigure(1, weight=1)

    def get_value(self):
        return self.var_text.get()

    def get_entry(self):
        return self.text_entry

    def get_label(self):
        return self.label

    def state_readonly(self):
        self.text_entry.config(state="readonly")

    def state_normal(self):
        self.text_entry.config(state="normal")

    def is_valid(self):
        pass

    def validate(self):
        pass