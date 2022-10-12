import os
from os.path import join

from src.api.utils.paths import CONDITIONS_PATH


class InputRepository:

    def get_file_path_from_name(self, file_name: str) -> str:
        return join(CONDITIONS_PATH, file_name + ".txt")

    def check_file_exist_by_name(self, file_name: str) -> bool:
        file_path = self.get_file_path_from_name(file_name)
        return os.path.exists(file_path)

    def create_new_file(self, file_name: str, text_content: str) -> None:
        file_path = self.get_file_path_from_name(file_name)
        # "x" - Create - Creates the specified file, returns an error if the file exist
        file_connection = open(file_path, "x")
        file_connection.write(text_content)
        file_connection.close()

    def override_file(self, file_name: str, text_content: str) -> None:
        file_path = self.get_file_path_from_name(file_name)
        # "w" - Write - Opens a file for writing, creates the file if it does not exist
        file_connection = open(file_path, "w")
        file_connection.write(text_content)
        file_connection.close()

    def delete_file(self, file_name: str) -> None:
        file_path = self.get_file_path_from_name(file_name)
        os.remove(file_path)

    def list_existing_files(self) -> list:
        return os.listdir(CONDITIONS_PATH)

    def get_file(self, file_name: str) -> str:
        file_path = self.get_file_path_from_name(file_name)
        file_connection = open(file_path, "r")
        text: str = file_connection.read()
        file_connection.close()
        return text
