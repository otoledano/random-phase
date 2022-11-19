import os

from src.api.utils.paths import PathTo


class ConditionsRepository:

    def file_path(self, simulation_name: str):
        return PathTo.conditions_file(simulation_name)

    def exists(self, simulation_name: str) -> bool:
        file_path = self.file_path(simulation_name)
        return os.path.exists(file_path)

    def read(self, simulation_name: str) -> str:
        file_path = self.file_path(simulation_name)
        file_connection = open(file_path, "r")
        text = file_connection.read()
        file_connection.close()
        return text

    def create_new_file(self, simulation_name: str, text_content: str) -> None:
        file_path = self.file_path(simulation_name)
        # "x" - Create - Creates the specified file, returns an error if the file exist
        file_connection = open(file_path, "x")
        file_connection.write(text_content)
        file_connection.close()

    def override(self, simulation_name: str, text_content: str) -> None:
        file_path = self.file_path(simulation_name)
        # "w" - Write - Opens a file for writing, creates the file if it does not exist
        file_connection = open(file_path, "w")
        file_connection.write(text_content)
        file_connection.close()

    def delete(self, simulation_name: str) -> None:
        file_path = self.file_path(simulation_name)
        os.remove(file_path)


