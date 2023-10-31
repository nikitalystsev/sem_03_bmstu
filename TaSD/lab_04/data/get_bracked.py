import random as rm


def gen_str_with_braked():
    """
    функция генерирует строку со скобками
    """
    bracked = ["{", "(", "[", "}", "]", ")"]

    result_string = ""

    for i in range(0, 1000):
        result_string += rm.choice(bracked)

    # for i in range(0, 10001):
    #     result_string += bracked[0]

    # for i in range(0, 0):
    #     result_string += bracked[3]
        
    return result_string

def write_gen_str_to_file():
    """
    функция записывает строку со скобками в файл
    """

    with open("data_bracked.txt", "w") as file:
        file.write(gen_str_with_braked())

def main():
    write_gen_str_to_file()


if __name__ == '__main__':
    main()
