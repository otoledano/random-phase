from tkinter import ttk, StringVar

from src.api.constants.constants import Cts
from src.api.observer_pattern.subject import ConcreteSubject
from src.api.validation.validator import Validator


class ComponentTextEntry(ttk.Frame, ConcreteSubject):

    def __init__(self, parent, label_text, tooltip_text):
        ttk.Frame.__init__(parent)
        ConcreteSubject.__init__(self)
        self.parent = parent

        self.label_text = label_text
        self.tooltip_text = tooltip_text

        self.validation_codes = list()
        self.validation_state = Cts.COMPONENT_UNCHECKED

        self.label = ttk.Label(self)
        self.text_entry = ttk.Entry(self)
        self.var_text = StringVar()

        self.paint()

    def layout(self):
        self.rowconfigure(0, weight=1)
        self.rowconfigure(1, weight=1)

    def get_value(self):
        return self.var_text.get()

    def get_entry(self):
        return self.text_entry

    def get_label(self):
        return self.label

    def set_readonly(self):
        self.text_entry.config(state="readonly")

    def set_writable(self):
        self.text_entry.config(state="normal")

    def add_validation(self, validation_code):
        self.validation_codes.append(validation_code)

    def is_valid(self):
        is_valid = False
        for validation_code in self.validation_codes:
            if Validator.with_function(validation_code):
                is_valid = True
            else:
                return False
        return is_valid

    def validate(self):
        pass
        # if self.is_valid():
        #     self.validation_state =

    def on_mouseover(self):
        self._state = Cts.SHOW_TOOLTIP
        self.notify()

    def out_mouseover(self):
        self._state = Cts.HIDE_TOOLTIP
        self.notify()

    def paint(self):

        self.label.config(text=self.label_text)
        self.label.grid(Cts.GRID_0_0, sticky="EW", pady=(10, 5), padx=(0, 10))

        self.text_entry.config(textvariable=self.var_text, width=100)
        self.text_entry.grid(Cts.GRID_1_0, sticky="EW", pady=(10, 5), padx=(0, 10))
        self.text_entry.bind("Enter", self.on_mouseover)
