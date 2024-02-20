def get_grade(raw: str) -> str:
    letters = sum(1 for char in raw if char.isalpha())
    words = len(raw.split())
    sentences = sum(1 for char in raw if char in '?!.')
    L = letters / words * 100
    S = sentences / words * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)
    if index < 1:
        return "Before Grade 1"
    elif index > 16:
        return "Grade 16+"
    else:
        return f"Grade {index}"


if __name__ == "__main__":
    raw = input("Text: ")
    grade = get_grade(raw)
    print(grade)
