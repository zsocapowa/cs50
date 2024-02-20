from cs50 import get_int


def get_height() -> int:
    while True:
        n = get_int("Height: ")
        if 1 <= n < 9:
            return n


def print_pyramid(height: int):
    current = 1
    while current < height + 1:
        spaces = " " * (height - current)
        hashmarks = "#" * current
        print(f"{spaces}{hashmarks}  {hashmarks}")
        current += 1


if __name__ == "__main__":
    height = get_height()
    print_pyramid(height)
