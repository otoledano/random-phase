from src.api.dto.dummy_condition import DummyConditions

from src.repository.conditions_repository import InputRepository


class Service:
    """Class made for managing all the business logic of the app
    MODIFY Has to be refactored in different classes for more specific purposes"""

    def __init__(self):
        self.input_repository: InputRepository

    def create_input(self, dummy_input: DummyConditions):
        dummy_text: str = dummy_input.dummy_text
        input_file_name: str = dummy_input.input_name + ".txt"


    def run_input(self, input_name: str):
        pass

    def create_input_and_run(self, dummy_input: DummyConditions):
        self.create_input(dummy_input)
        self.run_input(dummy_input.input_name)
