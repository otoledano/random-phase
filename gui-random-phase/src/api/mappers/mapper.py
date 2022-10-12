from src.api.dto.initial_conditions.initial_conditions import InitialConditions
from src.api.mappers.conditions_template import ConditionsTemplate


class Mapper:

    @staticmethod
    def to_csv_text(initial_conditions: InitialConditions) -> str:
        return ConditionsTemplate.fill_template(initial_conditions)
