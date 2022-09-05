import tkinter as tk

from src.template.new_input_frame import NewInputFrame


class Content(tk.Frame):
    """Main panel which stores all the global data of the application.
    Also acts as a controller organizing his siblings open, close and data transfer operations"""

    def __init__(self, parent_element):
        super().__init__()
        self.parent_element = parent_element
        self.paint()
        self.open_new_input_frame()

    def paint(self):
        self.config(borderwidth=5, relief="sunken")
        self.grid(column=0, row=0, sticky="nsew")
        self.parent_element.grid_columnconfigure(0, weight=1)
        self.parent_element.grid_rowconfigure(0, weight=1)

    def open_new_input_frame(self):
        NewInputFrame(self)
