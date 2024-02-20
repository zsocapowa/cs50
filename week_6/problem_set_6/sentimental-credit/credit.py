def check_format(raw: str) -> bool:
    is_digit = raw.isdigit()
    is_valid_len = len(raw) in [13, 15, 16]
    is_valid_start = raw[:2] in ['34', '37', '51', '52', '53', '54', '55'] or raw.startswith('4')
    return all([is_digit, is_valid_len, is_valid_start])


def calculate_luhn(raw: str) -> bool:
    mod_values = [int(i) * 2 for i in raw[-2::-2]]
    result = ''.join([str(i) for i in mod_values])
    sum_value = sum(int(i) for i in result)
    full_sum = sum(int(i) for i in raw[-1::-2]) + sum_value
    return full_sum % 10 == 0


def get_card_type(raw: str) -> str:
    card_type = 'INVALID\n'
    if not check_format(raw) or not calculate_luhn(raw):
        return card_type
    if raw[:2] in ['34', '37'] and len(raw) == 15:
        card_type = 'AMEX\n'
    elif raw[:2] in ['51', '52', '53', '54', '55'] and len(raw) == 16:
        card_type = 'MASTERCARD\n'
    elif raw.startswith('4') and len(raw) in (13, 16):
        card_type = 'VISA\n'
    return card_type


if __name__ == "__main__":
    raw = input("Number: ")
    card_type = get_card_type(raw)
    print(card_type)
