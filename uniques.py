def main():
    iterable = ['A', 'A', 'A', 'A', 'B', 'B', 'B', 'C', 'C', 'D', 'A', 'A', 'B', 'B', 'B']
    unique_in_order(iterable)

def unique_in_order(iterable):
    lst = []
    counter = 0
    # Iterate over each element in the provided sequence
    for i in range(len(iterable)):
        j = counter
        for j in range(len(iterable) - counter):
            if iterable[j] != iterable[counter]:
                lst.append(iterable[counter])
                counter = j
                break
    print(f"{lst}")
    return lst

main()