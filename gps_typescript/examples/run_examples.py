from gps_python.general_problem_solver import gps
import json
import os
import copy

example_files = ['monkeys.json']

example_data = {}

for filename in example_files:
    fp = os.path.join(os.path.dirname(__file__), filename)
    with open(fp, 'r') as data_file:
        data = json.load(data_file)
        example_data[filename[:-5]] = data

def main():
    while True:
        choice = run_menu()
        start = example_data[choice]['start']
        finish = example_data[choice]['finish']
        ops = copy.deepcopy(example_data[choice]['ops'])

        for action in gps(start, finish, ops):
            print(action)

def run_menu():
    prompt = """Choose one of the following:
              1. Monkeys
              Type 'quit' to exit
           """
    while True:
        choice = input(prompt)
        try:
            choice = int(choice)
            if choice in [1]:
                choice = example_files[choice-1][:-5]
                break
        except ValueError:
            pass # try string
        if type(choice) == str and choice+'.json' in example_files:
            break
        elif type(choice) == str and choice == 'quit':
            exit(1)
        else:
            print("Invalid input please try again")
    return choice

if __name__ == '__main__':
    main()
