from sys import argv

def main():
    print(f"{pig_it(argv[1])}")

def pig_it(text):
    #your code here
    text_list = text.split()

    for word in text_list:
        if word.isalpha():
            word = [word[1:] + word[:1] + 'ay']
        else:
            word = word

    return (' '.join(text_list))

main()