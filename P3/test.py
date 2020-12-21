import os

TESTS = "generated"

if TESTS == "given":
        NUM_TESTS = 8
elif TESTS == "generated":
        NUM_TESTS = 200

built = "./kruskaldriver"

def build():
    pass
        # os.system("make clean")
        # os.system("make")

def run_given_tests():
        for i in range(1, NUM_TESTS + 1):
                print(f"\nTEST {i}")

                os.system(f"{built} < ./learn_tests/test0{i}.in > test.out")
                print(os.system(f'diff test.out ./learn_tests/test0{i}.out'))

                input("Press enter to continue: ")


def run_generated_tests():
        for i in range(1, NUM_TESTS + 1):
                print(f"\nTEST {i}")

                os.system(f"{built} < ./test_cases_v2/{i}.in > test.out")
                print(os.system(f"diff test.out ./test_cases_v2/{i}.out"))

                input("Press enter to continue: ")

def main():
        build()

        if TESTS == "given":
                run_given_tests()
        elif TESTS == "generated":
                run_generated_tests()

        os.system("rm test.out")


if __name__ == "__main__":
        main()

