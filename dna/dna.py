import csv
import sys


def main():
    # Checking the correct number of command line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Reading the contents of a database file into a variable
    database_filename = sys.argv[1]
    with open(database_filename) as database_file:
        database = list(csv.DictReader(database_file))

    # Reading the contents of a DNA sequence file into a variable
    sequence_filename = sys.argv[2]
    with open(sequence_filename) as sequence_file:
        dna_sequence = sequence_file.read()

    # Dictionary for storing the longest series of each STR
    longest_runs = {}

    # Getting a list of all STRs from a database file
    str_list = database[0].keys()

    # Search for the longest series for each STR in the DNA sequence
    for str_seq in str_list:
        if str_seq == "name":
            continue  # Skip the first column with the name
        longest_runs[str_seq] = longest_match(dna_sequence, str_seq)

    # Checking the database for matching profiles
    for individual in database:
        if all(int(individual[str_seq]) == longest_runs[str_seq] for str_seq in str_list if str_seq != "name"):
            print(individual["name"])
            return

    print("No match")


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
