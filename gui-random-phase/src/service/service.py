from src.api.paths import INPUT_PATH
from src.api.dto.dummy_input import DummyInput
from os.path import join


class Service:
    """Class made for managing all the business logic of the app
    MODIFY Has to be refactored in different classes for more specific purposes"""

    def create_input(self, dummy_input: DummyInput):
        dummy_text: str = dummy_input.dummy_text
        input_file_name: str = dummy_input.input_name + ".txt"
        input_file_path: str = join(INPUT_PATH, input_file_name)
        input_file_connection = open(input_file_path, "w")
        input_file_connection.write(dummy_text)
        input_file_connection.close()

    def run_input(self, input_name: str):
        pass

    def create_input_and_run(self, dummy_input: DummyInput):
        self.create_input(dummy_input)
        self.run_input(dummy_input.input_name)