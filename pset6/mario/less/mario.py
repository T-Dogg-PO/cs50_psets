from cs50 import get_int

# Declare the main function
def main():
    # First get height of pyramid from the user
    height = get_height()

    # Loops for printing out the pyramid in the terminal
    # Loop through the whole thing 'height' number of times
    for i in range(height):
        # Calculate the number of spaces needed for each line
        spaces = height - i - 1

        # Loop for printing the spaces on each line using above variable
        for n in range(spaces):
            print(" ", end="")

        # Loop for printing the hashes based on where we are in the loop (i)
        for j in range(i + 1):
            print("#", end="")

        # Print a new line at the end of each loop
        print()

# Prompt the user for the height of the pyramid, using a while loop to make sure it's in range
def get_height():
    while True:
        height = get_int("Height: ")
        if (height > 0) and (height < 9):
            break
    return height

main()