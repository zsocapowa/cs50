from cs50 import get_float


def get_cents() -> int:
    while True:
        cents = get_float("Input: ")
        if cents >= 0:
            return cents


def calculate_change(cents: float) -> int:
    num_coins = 0
    for i in [0.25, 0.1, 0.05, 0.01]:
        c = cents // i
        if c == 0:
            continue
        num_coins += c
        cents = round(cents - (i * c), 2)
    return int(num_coins)


if __name__ == "__main__":
    cents = get_cents()
    change = calculate_change(cents)
    print(change)
