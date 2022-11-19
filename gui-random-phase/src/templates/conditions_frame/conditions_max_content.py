from tkinter import ttk, StringVar

from src.api.constants.constants import Cts
from src.api.models.conditions.conditions import Conditions


class ConditionsMaxContent(ttk.Frame):
    """FILL"""

    def __init__(self, parent, service):
        super().__init__(parent)
        # Visual variables

        # self.test_component = ComponentTextEntry(self, "Componente de prueba", "Texto de ayuda")

        self.button_testing_run_simulation = ttk.Button(self)
        self.entry_testing_simulation_name = ttk.Entry(self)
        self.var_testing_simulation_name = StringVar()

        # Universe simulation
        self.label_simulation_name = ttk.Label(self)
        self.entry_simulation_name = ttk.Entry(self)
        self.var_simulation_name = StringVar()

        self.label_simulation_ensemble = ttk.Label(self)
        self.combobox_simulation_ensemble = ttk.Combobox(self)
        self.var_simulation_ensemble = StringVar()

        self.label_oriented_particles = ttk.Label(self)
        self.combobox_oriented_particles = ttk.Combobox(self)
        self.var_oriented_particles = StringVar()

        self.label_potential_tabulated = ttk.Label(self)
        self.combobox_potential_tabulated = ttk.Combobox(self)
        self.var_potential_tabulated = StringVar()

        self.label_potential_path = ttk.Label(self)
        self.entry_potential_path = ttk.Entry(self)
        self.var_potential_path = StringVar()

        self.label_potential_function = ttk.Label(self)
        self.combobox_potential_function = ttk.Combobox(self)
        self.var_potential_function = StringVar()

        # Potential interaction
        self.label_box_x = ttk.Label(self)
        self.entry_box_x = ttk.Entry(self)
        self.var_box_x = StringVar()

        self.label_box_y = ttk.Label(self)
        self.entry_box_y = ttk.Entry(self)
        self.var_bow_y = StringVar()

        self.label_particles_num = ttk.Label(self)
        self.entry_particles_num = ttk.Entry(self)
        self.var_particles_num = StringVar()

        self.label_temperature_sys = ttk.Label(self)
        self.entry_temperature_sys = ttk.Entry(self)
        self.var_temperature_sys = StringVar()

        self.label_target_pressure = ttk.Label(self)
        self.entry_target_pressure = ttk.Entry(self)
        self.var_target_pressure = StringVar()

        self.label_dipole_moment = ttk.Label(self)
        self.entry_dipole_moment = ttk.Entry(self)
        self.var_dipole_moment = StringVar()

        self.label_potential_sigma = ttk.Label(self)
        self.entry_potential_sigma = ttk.Entry(self)
        self.var_potential_sigma = StringVar()

        self.label_potential_epsilon = ttk.Label(self)
        self.entry_potential_epsilon = ttk.Entry(self)
        self.var_potential_epsilon = StringVar()

        self.label_potential_width = ttk.Label(self)
        self.entry_potential_width = ttk.Entry(self)
        self.var_potential_width = StringVar()

        self.label_rigid_elements = ttk.Label(self)
        self.entry_rigid_elements = ttk.Entry(self)
        self.var_rigid_elements = StringVar()

        self.label_epsilon_end_end = ttk.Label(self)
        self.entry_epsilon_end_end = ttk.Entry(self)
        self.var_epsilon_end_end = StringVar()

        self.label_epsilon_sid_sid = ttk.Label(self)
        self.entry_epsilon_sid_sid = ttk.Entry(self)
        self.var_epsilon_sid_sid = StringVar()

        self.label_sigma_par = ttk.Label(self)
        self.entry_sigma_par = ttk.Entry(self)
        self.var_sigma_par = StringVar()

        self.label_sigma_perp = ttk.Label(self)
        self.entry_sigma_perp = ttk.Entry(self)
        self.var_sigma_perp = StringVar()

        self.label_mu_ellipse = ttk.Label(self)
        self.entry_mu_ellipse = ttk.Entry(self)
        self.var_mu_ellipse = StringVar()

        self.label_nu_ellipse = ttk.Label(self)
        self.entry_nu_ellipse = ttk.Entry(self)
        self.var_nu_ellipse = StringVar()

        self.label_rep_exponent = ttk.Label(self)
        self.entry_rep_exponent = ttk.Entry(self)
        self.var_rep_exponent = StringVar()

        self.label_atr_exponent = ttk.Label(self)
        self.entry_atr_exponent = ttk.Entry(self)
        self.var_atr_exponent = StringVar()

        # Simulation variables

        self.label_num_steps = ttk.Label(self)
        self.entry_num_steps = ttk.Entry(self)
        self.var_num_steps = StringVar()

        self.label_num_processors = ttk.Label(self)
        self.entry_num_processors = ttk.Entry(self)
        self.var_num_processors = StringVar()

        self.label_potential_analytic = ttk.Label(self)
        self.entry_potential_analytic = ttk.Entry(self)
        self.var_potential_analytic = StringVar()

        self.label_potential_interpolat = ttk.Label(self)
        self.combobox_potential_interpolat = ttk.Combobox(self)
        self.var_potential_interpolat = StringVar()

        self.label_potential_out = ttk.Label(self)
        self.combobox_potential_out = ttk.Combobox(self)
        self.var_potential_out = StringVar()

        self.label_system_units = ttk.Label(self)
        self.combobox_system_units = ttk.Combobox(self)
        self.var_system_units = StringVar()

        self.label_radial_displacement = ttk.Label(self)
        self.entry_radial_displacement = ttk.Entry(self)
        self.var_radial_displacement = StringVar()

        self.label_angular_displacement = ttk.Label(self)
        self.entry_angular_displacement = ttk.Entry(self)
        self.var_angular_displacement = StringVar()

        self.label_rdf_precision = ttk.Label(self)
        self.entry_rdf_precision = ttk.Entry(self)
        self.var_rdf_precision = StringVar()

        self.label_cutoff_radius = ttk.Label(self)
        self.entry_cutoff_radius = ttk.Entry(self)
        self.var_cutoff_radius = StringVar()

        # Initial positions

        self.label_initial_file = ttk.Label(self)
        self.combobox_initial_file = ttk.Combobox(self)
        self.var_initial_file = StringVar()

        self.label_initial_path = ttk.Label(self)
        self.entry_initial_path = ttk.Entry(self)
        self.var_initial_path = StringVar()

        self.label_initial_lattice = ttk.Label(self)
        self.combobox_initial_lattice = ttk.Combobox(self)
        self.var_initial_lattice = StringVar()

        self.label_lattice_a = ttk.Label(self)
        self.entry_lattice_a = ttk.Entry(self)
        self.var_lattice_a = StringVar()

        self.label_lattice_b = ttk.Label(self)
        self.entry_lattice_b = ttk.Entry(self)
        self.var_lattice_b = StringVar()

        self.label_lattice_alpha = ttk.Label(self)
        self.entry_lattice_alpha = ttk.Entry(self)
        self.var_lattice_alpha = StringVar()

        self.label_lattice_elements = ttk.Label(self)
        self.entry_lattice_elements = ttk.Entry(self)
        self.var_lattice_elements = StringVar()

        self.label_lattice_coordinates = ttk.Label(self)
        self.entry_lattice_coordinates = ttk.Entry(self)
        self.var_lattice_coordinates = StringVar()

        """-------------------------------------"""

        self.label_ = ttk.Label(self)
        self.combobox_ = ttk.Combobox(self)
        self.var_ = StringVar()

        self.label_ = ttk.Label(self)
        self.entry_ = ttk.Entry(self)
        self.var_ = StringVar()

        # Non visual variables
        self.parent = parent
        self.service = service

        # Initialize
        self.paint()

        # Layout
        self.layout()

    def paint(self) -> None:

        self.button_testing_run_simulation.config(text="Play >>", command=self.run_simulation)
        self.button_testing_run_simulation.grid(Cts.GRID_0_0, sticky="N", **Cts.PAD_10_2, ipadx=10, ipady=0)

        self.entry_testing_simulation_name.config(textvariable=self.var_testing_simulation_name)
        self.entry_testing_simulation_name.grid(Cts.GRID_0_1, sticky="N", **Cts.PAD_10_2)



    def layout(self):
        self.rowconfigure(0, weight=1)
        self.columnconfigure(0, weight=1)

    def run_simulation(self):
        conditions = Conditions()
        conditions.simulation_metadata.name = self.var_testing_simulation_name.get()
        self.service.save_conditions(conditions)
        simulation_name = conditions.simulation_metadata.name
        self.service.run_simulation(simulation_name)
