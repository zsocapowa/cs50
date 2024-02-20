import csv
import sys


def read_csv(file_path: str) -> list[dict]:
    data = []
    with open(file_path, 'r') as file:
        csv_reader = csv.DictReader(file)
        for row in csv_reader:
            data.append(row)
    return data


def read_text(file_path: str) -> str:
    with open(file_path, 'r') as file:
        text_content = file.read()
        return text_content


def get_matching_name(table: list[dict], text: str) -> str:
    dna_dict = {key: str(longest_match(text, key)) for key in table[0] if key != 'name'}
    for user in table:
        if all(user.get(k) == v for k, v in dna_dict.items() if k != 'name'):
            return user['name']
    return "No match"


def main() -> None:

    if len(sys.argv) != 3:
        print('Usage: python dna.py data.csv sequence.txt')
        sys.exit()

    table = read_csv(sys.argv[1])
    text = read_text(sys.argv[2])

    name = get_matching_name(table, text)
    print(name)

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
