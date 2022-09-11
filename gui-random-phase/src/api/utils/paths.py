from os.path import dirname, abspath, curdir, join

"""Module to reference the path to folders and files needed by the gui"""

# Path to the root project folder
PROJECT_PATH: str = dirname(dirname(abspath(curdir)))

# Path to  gui-random-phase folder
GUI_PATH: str = dirname(abspath(curdir))

# Path to resources folder
RESOURCES_PATH: str = join(GUI_PATH, "resources")
CALC_ICO_PATH: str = join(RESOURCES_PATH, "calc.ico")

# Path to io folder
IO_PATH: str = join(PROJECT_PATH, "io")
CONDITIONS_PATH: str = join(IO_PATH, "conditions")
