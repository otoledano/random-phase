from src.api.models.conditions.conditions import Conditions
from src.api.mappers.conditions_template import ConditionsTemplate


class Mapper:

    @staticmethod
    def to_csv_text(initial_conditions: Conditions) -> str:
        return ConditionsTemplate.fill_template(initial_conditions)
