def main():
    cart_number = (input("Number: "))
    if len(cart_number) > 12 and len(cart_number) < 17:
        check_cart_number(cart_number)
    else:
        print("INVALID")


def reverse_array(str):
    array = []
    for i in str:
        array.insert(0, int(i))
    return array


def product_array(array):
    product_array = []
    for i in range(1, len(array), 2):
        product_array.append(array[i] * 2)
    return product_array


def luhns_algorithm_step1(array):
    result = 0
    for i in array:
        for j in str(i):
            result += int(j)
    return result


def luhns_algorithm_step2(array, int):
    for i in range(0, len(array), 2):
        int += array[i]
    return int


def check_cart_number(cart_number):
    reverse_number_array = reverse_array(cart_number)

    product_reverse_number_array = product_array(reverse_number_array)

    result_luhns_step1 = luhns_algorithm_step1(product_reverse_number_array)

    result_luhns_step2 = luhns_algorithm_step2(reverse_number_array, result_luhns_step1)

    if result_luhns_step2 % 10 == 0:
        first_cart_digit = int(cart_number[0])
        second_cart_digit = int(cart_number[1])
        first_digits_for_check = [3, 4, 5]
        second_digits_by_amex = [4, 7]
        second_digits_by_mastercard = [1, 2, 3, 4, 5]

        if first_cart_digit in first_digits_for_check:
            if first_cart_digit == 4:
                print("VISA")
            elif first_cart_digit == 3 and second_cart_digit in second_digits_by_amex:
                print("AMEX")
            elif first_cart_digit == 5 and second_cart_digit in second_digits_by_mastercard:
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")


main()
