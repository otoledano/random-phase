import tkinter as tk
from tkinter import ttk


class ResultsFrame(ttk.Frame):
    """Tab to create, load or manage results files"""

    def __init__(self, parent, service):
        super().__init__(parent)
