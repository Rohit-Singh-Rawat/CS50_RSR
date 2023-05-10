import sys
import re

number = input("Number: ")  # Takes input(Card number) from user


def main():

    if validity(number) == False:
        print("INVALID")
        sys.exit(0)
    if (re.match("34", number) or re.match("37", number)) and len(number) == 15:  # Using match to find same starting number.
        print("AMEX")
    elif (any(re.match(n, number) for n in ["51", "52", "53", "54", "55"])) and len(number) == 16:
        print("MASTERCARD")
    elif (re.match("4", number)) and (len(number) == 13 or len(number) == 16):
        print("VISA")
    else:
        print("INVALID")


def validity(number):  # Function to check if card number is valid or not.
    sum1 = 0
    for i in range(len(number) - 1, -1, -2):  # Adding every second number from last
        sum1 += int(number[i])
    sum2 = 0
    tmp = 0
    for i in range(len(number) - 2, -1, -2):  # Applying Luhn’s algorithm.
        tmp = 2 * int(number[i])
        for i in str(tmp):
            sum2 += int(i)
    sum = sum1 + sum2
    if sum % 10 == 0:
        return True
    else:
        return False


main()  # Main function to run whole program.