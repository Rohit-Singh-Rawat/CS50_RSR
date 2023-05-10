height = 0
while not (height > 0 and height < 9):
    try:
        height = int(input("Height:"))
    except ValueError:  # Checking for only integers
        print("Please type an integer!!!")
    else:
        if not (height > 0 and height < 9):  # Chechking for integers between 1 and 8
            print("Please Enter a height between 1 and 8!!!")
for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i + "  " + "#" * i)  # Print one line at a time
