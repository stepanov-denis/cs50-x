def main():
    while True:
        try:
            # get hieght value from user
            height = int(input("Enter an integer from 1 to 8 inclusive (the height of the half pyramid): "))
            if height > 0 and height < 9:
                print_pyramid(height)
                break
        except ValueError:
            print("Oops!  That was no valid number.  Try again...")


# print block's in current row
def print_block(n):
    for _ in range(n):
        print("#", end="")


# print whitespace's in current row
def print_whitespace(n):
    for _ in range(n):
        print(" ", end="")


# print pyramid
def print_pyramid(height):
    for i in range(height):
        print_whitespace(height - (i + 1))
        print_block(i + 1)
        print_whitespace(2)
        print_block(i + 1)
        print()


main()
