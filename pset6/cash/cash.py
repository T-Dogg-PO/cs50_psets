from cs50 import get_float

# Ask the user for their input (how much change they are owed in dollars and cents)
# Ensure that change is non-negative
while True:
    change = get_float("Change owed: ")
    if (change > 0):
        break

# Convert the change value to cents for use in the calculations
cents = round(change * 100)

# Create the coins variable to store the number of coins making up the change
coins = 0

# Start the while loop which will continue to loop through while the cents value > 0
while (cents > 0):
    # Loop for adding 25 cent coins
    if (cents >= 25):
        cents -= 25
        coins += 1
    # Loop for adding 10 cent coins
    elif (cents >= 10):
        cents -= 10
        coins += 1
    # Loop for adding 5 cent coins
    elif (cents >= 5):
        cents -= 5
        coins += 1
    # Loop for adding 1 cent coins
    else:
        cents -= 1
        coins += 1

# Print out the number of coins that make up the change
print(f"{coins}")