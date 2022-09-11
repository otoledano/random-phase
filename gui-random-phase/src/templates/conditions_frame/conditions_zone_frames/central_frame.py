import tkinter as tk

from src.api.dto.dummy_condition import DummyConditions


class CentralFrame(tk.Frame):
    """Central frame where the info from the conditions is displayed"""

    def __init__(self, parent, service):
        super().__init__(parent)

        # Visual variables
        self.entry_conditions_name = None
        self.label_conditions_name = None
        self.label_text_field = None
        self.entry_text_field = None
        self.button_test = None

        # Non visual variables
        self.parent = parent
        self.service = service
        self.var_conditions_name = tk.StringVar()
        self.var_text_field = tk.StringVar()

        # Initialize
        self.paint()

        # Layout
        self.layout()

    def paint(self) -> None:
        # First One
        self.label_conditions_name = tk.Label(self)
        self.label_conditions_name.config(text="conditions Name")
        self.label_conditions_name.grid(row=0, column=0, sticky="n", padx=(30, 0), pady=(10, 3))

        self.entry_conditions_name = tk.Entry(self, textvariable=self.var_conditions_name)
        self.entry_conditions_name.config(width=20)
        self.entry_conditions_name.grid(row=1, column=0, sticky="n", padx=(30, 0), pady=(0, 0))

        # Row Two
        self.label_text_field = tk.Label(self)
        self.label_text_field.config(text="Field 1")
        self.label_text_field.grid(row=2, column=0, sticky="n", padx=(30, 0), pady=(10, 3))

        self.entry_text_field = tk.Entry(self, textvariable=self.var_text_field)
        self.entry_text_field.config(width=20)
        self.entry_text_field.grid(row=3, column=0, sticky="n", padx=(30, 0), pady=(0, 0))

        # Row Three
        self.button_test = tk.Button(self)
        self.button_test.config(text="Test Button", command=self.send_test_data)
        self.button_test.grid(row=4, column=0, sticky="n", padx=(30, 0), pady=(30, 0), ipadx=10, ipady=0)

    def layout(self):
        pass

    def send_test_data(self):
        dummy_conditions = DummyConditions()
        dummy_conditions.conditions_name = self.var_conditions_name.get()
        dummy_conditions.dummy_text = self.var_text_field.get()
        self.service.create_conditions_and_run(dummy_conditions)
