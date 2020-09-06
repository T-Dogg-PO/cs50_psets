from cs50 import SQL
from sys import argv, exit
import csv

# First check to see that one command line arguments were provided. If not, exit
if len(argv) != 2:
    print("Usage: python import.py data.csv")
    exit(1)

# Access the database through db
db = SQL("sqlite:///students.db")

# Open provided csv file
with open(argv[1], "r") as characters:

    # Create DictReader
    reader = csv.DictReader(characters)

    # Iterate over the csv file
    for row in reader:

        # Split the entry in the name row into a list
        list_name = row["name"].split(" ")

        # Count the number of items in said list
        number_name = len(list_name)

        # Add all info to the database depending on whether number_name is 2 or 3
        if (number_name == 3):
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
            list_name[0], list_name[1], list_name[2], row["house"], row["birth"])
        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
            list_name[0], None, list_name[1], row["house"], row["birth"])