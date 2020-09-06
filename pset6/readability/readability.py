from sys import exit

# Declare the main function, which will call all of our other functions
def main():
    # Get text snippet from user
    text = input("Text: ")

    # We need to calculate the number of letters, number of words and number of sentences
    # Call the function for counting the letters
    letters = count_letters(text)

    # Call the function for counting the number of words
    words = count_words(text)

    # Call the function for counting the number of sentences
    sentences = count_sentences(text)

    # Call the function for the calculation of the Coleman-Liau index
    index = calculation(letters, words, sentences)

    # Print the results
    if (index < 1):
        print("Before Grade 1")
        exit(0)
    elif (index >= 16):
        print("Grade 16+")
        exit(0)
    else:
        print(f"Grade {index}")
        exit(0)

# Function for finding the number of letters (only alphabetic characters)
def count_letters(text):
    # Succinct loop (loops through i characters in text, adding to sum if it's alpha)
    letters = sum(i.isalpha() for i in text)
    return letters

# Function for counting the number of words
def count_words(text):
    # Use the split method to split
    tmp = text.split()
    # Then use the len() function to find the number of items in the new list
    words = len(tmp)
    return words

# Function for counting the number of sentences
def count_sentences(text):
    # Define a variable for tracking the number of sentences
    sentences = 0
    # Loop through the text and count the number of sentences endings ('.', '!', '?')
    for i in text:
        if (i == '.') or (i == '!') or (i == '?'):
            sentences += 1
    return sentences

# Function for the calculation of the Coleman-Liau index
def calculation(letters, words, sentences):
    # Perform initial calculations to convert letters and sentences to averages per 100 words
    L = (letters / words) * 100
    S = (sentences / words) * 100
    # Perform the calculation
    index = (0.0588 * L) - (0.296 * S) - 15.8
    return round(index)

# Finally run the program
main()