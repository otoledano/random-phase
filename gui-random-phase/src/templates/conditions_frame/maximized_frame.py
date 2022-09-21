from tkinter import ttk
import tkinter as tk


class MaximizedFrame(ttk.Frame):
    """FILL"""

    def __init__(self, parent, service):
        super().__init__(parent)

        # Visual variables
        self.labelframe_options = None
        self.radiobutton_new_conditions = None
        self.radiobutton_load_conditions = None
        self.labelframe_conditions_state = None
        self.checkbutton_completed_results = None
        self.checkbutton_in_progress_results = None
        self.checkbutton_completed_conditions = None
        self.checkbutton_incomplete_conditions = None
        self.radiobutton_templates = None
        self.radiobutton_examples = None
        self.label_files_found = None
        self.list_files = None
        self.button_first_action: ttk.Button = ttk.Button()
        self.button_second_action: ttk.Button = ttk.Button()
        self.button_third_action: ttk.Button = ttk.Button()
        self.button_fourth_action: ttk.Button = ttk.Button()

        # Non visual variables
        self.parent = parent
        self.service = service

        #   Radiobutton action possible values
        self.NEW_CONDITIONS = "new_conditions"
        self.LOAD_CONDITIONS = "load_conditions"
        self.LOAD_TEMPLATE = "load_template"
        self.LOAD_EXAMPLE = "load_example"

        #   Check possible values
        self.COMPLETED_RESULTS = "completed_results"
        self.IN_PROGRESS_RESULTS = "in_progress_results"
        self.COMPLETED_CONDITIONS = "completed_conditions"
        self.INCOMPLETE_CONDITIONS = "incomplete_conditions"

        #   Radio Action
        self.global_action_var = tk.StringVar(value=self.NEW_CONDITIONS)

        #       State check variables
        self.completed_results_var = tk.StringVar(value=self.COMPLETED_RESULTS)
        self.in_progress_results_var = tk.StringVar(value=self.IN_PROGRESS_RESULTS)
        self.completed_conditions_var = tk.StringVar(value=self.COMPLETED_CONDITIONS)
        self.incomplete_conditions_var = tk.StringVar(value=self.INCOMPLETE_CONDITIONS)

        # Layout variables
        self.pady10 = {'padx': (10, 10), 'pady': (10, 10)}
        self.pady5 = {'padx': (10, 10), 'pady': (5, 5)}
        self.pady2 = {'padx': (10, 10), 'pady': (2, 2)}

        # Initialize
        self.paint()

        # Layout
        self.layout()

    def paint(self) -> None:
        # Options labelframe
        self.labelframe_options = ttk.Labelframe(self)
        self.labelframe_options.config(text="Options")
        self.labelframe_options.grid(row=0, column=0, sticky="EW", **self.pady10)

        self.radiobutton_new_conditions = ttk.Radiobutton(self.labelframe_options)
        self.radiobutton_new_conditions.config(text="New simulation conditions", variable=self.global_action_var,
                                               value=self.NEW_CONDITIONS,
                                               command=self.selected_radiobutton_new_conditions)
        self.radiobutton_new_conditions.grid(row=0, column=0, sticky="W", **self.pady10)

        self.radiobutton_load_conditions = ttk.Radiobutton(self.labelframe_options)
        self.radiobutton_load_conditions.config(text="Load existing simulation conditions",
                                                variable=self.global_action_var, value=self.LOAD_CONDITIONS,
                                                command=self.selected_radiobutton_load_conditions)
        self.radiobutton_load_conditions.grid(row=1, column=0, sticky="W", **self.pady10)

        #   ->State of simulation to load
        self.labelframe_conditions_state = ttk.Labelframe(self.labelframe_options)
        self.labelframe_conditions_state.config(text="State of the simulations")
        self.labelframe_conditions_state.grid(row=2, column=0, sticky="W", **self.pady10)

        self.checkbutton_completed_results = ttk.Checkbutton(self.labelframe_conditions_state)
        self.checkbutton_completed_results.config(text="Completed results", variable=self.completed_results_var,
                                                  onvalue=self.COMPLETED_RESULTS, offvalue="",
                                                  command=self.upload_search_by_state)
        self.checkbutton_completed_results.grid(row=0, column=0, sticky="W", **self.pady10)

        self.checkbutton_in_progress_results = ttk.Checkbutton(self.labelframe_conditions_state)
        self.checkbutton_in_progress_results.config(text="In progress results", variable=self.in_progress_results_var,
                                                    onvalue=self.IN_PROGRESS_RESULTS, offvalue="",
                                                    command=self.upload_search_by_state)
        self.checkbutton_in_progress_results.grid(row=1, column=0, sticky="W", **self.pady10)

        self.checkbutton_completed_conditions = ttk.Checkbutton(self.labelframe_conditions_state)
        self.checkbutton_completed_conditions.config(text="Completed conditions",
                                                     variable=self.completed_conditions_var,
                                                     onvalue=self.COMPLETED_CONDITIONS, offvalue="",
                                                     command=self.upload_search_by_state)
        self.checkbutton_completed_conditions.grid(row=2, column=0, sticky="W", **self.pady10)

        self.checkbutton_incomplete_conditions = ttk.Checkbutton(self.labelframe_conditions_state)
        self.checkbutton_incomplete_conditions.config(text="Incomplete conditions",
                                                      variable=self.incomplete_conditions_var,
                                                      onvalue=self.INCOMPLETE_CONDITIONS, offvalue="",
                                                      command=self.upload_search_by_state)
        self.checkbutton_incomplete_conditions.grid(row=3, column=0, sticky="W", **self.pady10)
        # We deactivate these buttons for the initialization where the selected radiobutton is the new conditions one
        self.deactivate_check_buttons()

        # <-(Options)
        self.radiobutton_templates = ttk.Radiobutton(self.labelframe_options)
        self.radiobutton_templates.config(text="Initial conditions templates", variable=self.global_action_var,
                                          value=self.LOAD_TEMPLATE, command=self.selected_radiobutton_load_templates)
        self.radiobutton_templates.grid(row=3, column=0, sticky="W", **self.pady10)

        self.radiobutton_examples = ttk.Radiobutton(self.labelframe_options)
        self.radiobutton_examples.config(text="Illustrative simulations", variable=self.global_action_var,
                                         value=self.LOAD_EXAMPLE, command=self.selected_radiobutton_load_examples)
        self.radiobutton_examples.grid(row=4, column=0, sticky="W", **self.pady10)

        # File list
        self.label_files_found = ttk.Label(self)
        self.label_files_found.config(text="Files founded:")
        self.label_files_found.grid(row=5, column=0, sticky="EW", **self.pady5)

        self.list_files = tk.Listbox(self)
        self.list_files.config(height=25)
        self.list_files.grid(row=6, column=0, sticky="EW", **self.pady5)
        # Concrete action buttons
        self.button_first_action = ttk.Button(self)
        self.button_first_action.config(text="First Action")
        self.button_first_action.grid(row=7, column=0, sticky="EW", **self.pady2, ipadx=10, ipady=0)

        self.button_second_action = ttk.Button(self)
        self.button_second_action.config(text="Second Action")
        self.button_second_action.grid(row=8, column=0, sticky="EW", **self.pady2, ipadx=10, ipady=0)

        self.button_third_action = ttk.Button(self)
        self.button_third_action.config(text="Third Action")
        self.button_third_action.grid(row=9, column=0, sticky="EW", **self.pady2, ipadx=10, ipady=0)

        self.button_fourth_action = ttk.Button(self)
        self.button_fourth_action.config(text="Fourth Action")
        self.button_fourth_action.grid(row=10, column=0, sticky="EW", **self.pady2, ipadx=10, ipady=0)

    def layout(self):
        self.rowconfigure(0, weight=1)
        self.rowconfigure(1, weight=1)
        self.rowconfigure(2, weight=1)

        # Select radio button and change action mode

    def selected_radiobutton_new_conditions(self):
        self.deactivate_check_buttons()
        self.button_first_action.config(text="Create blank conditions")

    def selected_radiobutton_load_conditions(self):
        self.activate_check_buttons()
        self.button_first_action.config(text="Load selected conditions")

    def selected_radiobutton_load_templates(self):
        self.deactivate_check_buttons()
        self.button_first_action.config(text="Load selected template")

    def selected_radiobutton_load_examples(self):
        self.deactivate_check_buttons()
        self.button_first_action.config(text="Load selected example")

        # Other functions

    def deactivate_check_buttons(self):
        self.checkbutton_completed_results.config(state="disabled")
        self.checkbutton_in_progress_results.config(state="disabled")
        self.checkbutton_completed_conditions.config(state="disabled")
        self.checkbutton_incomplete_conditions.config(state="disabled")

    def activate_check_buttons(self):
        self.checkbutton_completed_results.config(state="normal")
        self.checkbutton_in_progress_results.config(state="normal")
        self.checkbutton_completed_conditions.config(state="normal")
        self.checkbutton_incomplete_conditions.config(state="normal")

    def state_upload_search(self):
        pass

    def upload_search_by_state(self):
        pass
