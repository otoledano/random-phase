import tkinter as tk

from src.api.dto.dummy_condition import DummyConditions


class RightFrame(tk.Frame):
    """Central frame where the info from the input is displayed"""

    def __init__(self, parent, service):
        super().__init__(parent)

        # Visual variables
        self.entry_input_name = None
        self.label_input_name = None
        self.label_text_field = None
        self.entry_text_field = None
        self.button_test = None

        # Non visual variables
        self.parent = parent
        self.service = service
        self.var_input_name = tk.StringVar()
        self.var_text_field = tk.StringVar()

        # Initialize
        self.paint()

        # Layout
        self.layout()

    def paint(self) -> None:
        # First One
        self.label_input_name = tk.Label(self)
        self.label_input_name.config(text="Input Name")
        self.label_input_name.grid(row=0, column=0, padx=(30, 0), pady=(10, 3))

        self.entry_input_name = tk.Entry(self, textvariable=self.var_input_name)
        self.entry_input_name.config(width=20)
        self.entry_input_name.grid(row=1, column=0, sticky="", padx=(30, 0), pady=(0, 0))

        # Row Two
        self.label_text_field = tk.Label(self)
        self.label_text_field.config(text="Field 1")
        self.label_text_field.grid(row=2, column=0, padx=(30, 0), pady=(10, 3))

        self.entry_text_field = tk.Entry(self, textvariable=self.var_text_field)
        self.entry_text_field.config(width=20)
        self.entry_text_field.grid(row=3, column=0, padx=(30, 0), pady=(0, 0))

        # Row Three
        self.button_test = tk.Button(self)
        self.button_test.config(text="Test Button", command=self.send_test_data)
        self.button_test.grid(row=4, column=0, padx=(30, 0), pady=(30, 0), ipadx=10, ipady=0, sticky="ew")

    def layout(self):
        pass

    def send_test_data(self):
        dummy_input = DummyConditions()
        dummy_input.input_name = self.var_input_name.get()
        dummy_input.dummy_text = self.var_text_field.get()
        self.service.create_input_and_run(dummy_input)

