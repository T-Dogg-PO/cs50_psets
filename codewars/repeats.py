from sys import argv

def main():
    duplicate_count(argv[1])

def duplicate_count(text):
    # Your code goes here
    # Create a counter to track the number of letters that repeat
    repeat_counter = 0

    # Create a list to track which letters have already been registered as repeats
    repeated_letters = []

    # Loop through the number of lettersin the provided text
    for i in range(len(text) - 1):
        # Check to see if the letter has already been marked as a repeat
        if text.lower()[i] in repeated_letters or text.upper()[i] in repeated_letters:
            continue
        # Loop through again for the check
        for j in range(i + 1, len(text)):
            if (text.lower()[i] == text.lower()[j]):
                repeat_counter += 1
                repeated_letters.append(text[i])
                break

    # Print out the number of repeated letters
    print(f"{repeat_counter}")

main()