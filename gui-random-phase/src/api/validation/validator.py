from src.api.validation.validation_codes import ValidationCode


class Validator:
    def with_function(self, validation_function_code, *args) -> bool:

        if validation_function_code == ValidationCode.NUMBER_MIN_10_MAX_20:
            return self.validate_number_min_10_max_20(args[1])

    def validate_number_min_10_max_20(self, number):
        if 10 <= number <= 20:
            return True
        return False
