import re


def main():
    text = input("Text: ")
    grade = calc_grade(text)
    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    elif grade >= 1 and grade < 16:
        print(f"Grade {grade}")


def count_letters(text):
    return sum(1 for char in text if char.isalpha())


def count_words(text):
    words = text.split()
    return len(words)


def count_sentences(text):
    # We use a regular expression to search for dots, exclamation marks, and question marks
    sentence_endings = re.compile(r'[.!?]')
    # We find all the matches to the expression and count them
    sentences = sentence_endings.findall(text)
    return len(sentences)


def calc_coleman_liau_index(letters, words, sentences):
    average_number_of_letters = letters / words * 100
    average_number_of_sentences = sentences / words * 100
    index = round(0.0588 * average_number_of_letters - 0.296 * average_number_of_sentences - 15.8)
    return index


def calc_grade(text):
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    grade = calc_coleman_liau_index(letters, words, sentences)
    return grade


main()
