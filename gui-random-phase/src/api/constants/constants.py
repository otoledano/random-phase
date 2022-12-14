class Cts:
    # Paddings
    PAD_10_10 = {'padx': (10, 10), 'pady': (10, 10)}
    PAD_10_5 = {'padx': (10, 10), 'pady': (5, 5)}
    PAD_10_2 = {'padx': (10, 10), 'pady': (2, 2)}

    # Internal paddings
    IPAD_2 = {'ipadx': (2, 2), 'ipady': (2, 2)}

    # Sticky
    STICKY_X = {'sticky': "EW"}
    STICKY_Y = {'sticky': "NS"}
    STICKY_ALL = {'sticky': "NSEW"}

    # Grid
    #   Row 0
    GRID_0_0 = {'row': 0, 'column': 0}
    GRID_0_1 = {'row': 0, 'column': 1}
    GRID_0_2 = {'row': 0, 'column': 2}
    GRID_0_3 = {'row': 0, 'column': 3}
    GRID_0_4 = {'row': 0, 'column': 4}

    #   Row 1
    GRID_1_0 = {'row': 1, 'column': 0}
    GRID_1_1 = {'row': 1, 'column': 1}
    GRID_1_2 = {'row': 1, 'column': 2}
    GRID_1_3 = {'row': 1, 'column': 3}
    GRID_1_4 = {'row': 1, 'column': 4}

    # Simulation states
    BRAND_NEW = "Brand_new"
    CONDITIONS_OPEN = "Conditions_open"
    CONDITIONS_CLOSED = "Conditions_closed"
    RESULTS_IN_PROGRESS = "Results_in_progress"
    RESULTS_FINISHED = "Results_finished"
    VISUALIZATION_IN_PROGRESS = "Visualization_in_progress"
    VISUALIZATION_FINISHED = "Visualization_finished"

    # Panel sizes
    MAXIMIZED_SIZE = "Maximized_size"
    MINIMIZED_SIZE = "Minimized_size"
    STANDARD_SIZE = "Standard_size"
    BIG_SIZE = "Big_size"

    # Panel names
    CONDITIONS_FRAME = "Conditions_frame"
    VISUALIZATION_FRAME = "Visualization_frame"
    RESULTS_FRAME = "Results_frame"

    # Component's validation state
    COMPONENT_UNCHECKED = "Component_unchecked"
    COMPONENT_VALID = "Component_valid"
    COMPONENT_NOT_VALID = "Component_not_valid"

    # Component's state actions
    SHOW_TOOLTIP = "Show_tooltip"
    HIDE_TOOLTIP = "Hide_tooltip"
