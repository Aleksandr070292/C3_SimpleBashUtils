from itertools import combinations_with_replacement
from random import shuffle
from os import system
import os
import subprocess

your_cat = "./s21_cat"
system_cat = "cat"

file_name = 'test_files'
file_format = ".testing"

#Define a function to create test files with different contents
def create_test_files():
    test_files = [
        'test_files/test_1_cat.txt',
        'test_files/test_2_cat.txt',
        'test_files/test_3_cat.txt'
    ]

    for file in test_files:
        with open(file, 'w') as f:
            if 'test_1' in file:
                f.write("This is a simple test file.\n")
            elif 'test_2' in file:
                f.write("This is a test file with multiple lines.\nThis is the second line.\n")
            elif 'test_3' in file:
                f.write("\n\n\nThis is a test file with empty lines.\n")

#Define a function to compare files line - by - line
def compare_files(file1, file2):
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
        lines1 = f1.readlines()
        lines2 = f2.readlines()
        if lines1 == lines2:
            print("\033[42m\033[1m YES \033[0m")
        else:
            print("Files differ!")
            for i, (line1, line2) in enumerate(zip(lines1, lines2)):
                if line1 != line2:
                    print(f"Line {i+1}:")
                    print(f"  {line1.strip()} (from {file1})")
                    print(f"  {line2.strip()} (from {file2})")
            print()

#Define a function to run a command and capture its output
def run_command(command):
    try:
        process = subprocess.run(command.split(), capture_output=True, text=True, check=True)
        return process.stdout
    except subprocess.CalledProcessError as e:
        print(f"Error running command: {command}")
        print(f"Error message: {e.stderr}")
        return None

suite = [
    'test_files/test_1_cat.txt',
    'test_files/test_2_cat.txt',
    'test_files/test_3_cat.txt'
]

flags = {
    '-b',
    '-e',
    '-n',
    '-s',
    '-v',
    '-t'
}

all_var = list(combinations_with_replacement(flags, len(flags)))

#Create test files if they don't exist
if not os.path.exists('test_files'):
    os.mkdir('test_files')
create_test_files()

#Run tests
for test in range(len(all_var)):
    cur_flags_ = all_var[test]
    for cur_flags in (cur_flags_, set(cur_flags_)):
        shuffle(suite)
        print(f"Current TEST [{test + 1} / {len(all_var)}] - ", end='')

#Generate the command strings
        command_your_cat = f'{your_cat} {" ".join(cur_flags)} {" ".join(suite)} > {file_name+"-0"+file_format}'
        command_original = f'{system_cat} {" ".join(cur_flags)} {" ".join(suite)} > {file_name+"-1"+file_format}'

#Run commands and compare output
#output_falshivka = run_command(command_falshivka)
#output_original = run_command(command_original)

#Execute both commands in a single system call
        system(f"echo '{command_your_cat}' >> commands.testing; echo '{command_original}' >> commands.testing; {command_your_cat}; {command_original}")

#Compare outputs
        if os.path.exists(file_name+'-0'+file_format) and os.path.exists(file_name+'-1'+file_format):
            compare_files(file_name+'-0'+file_format, file_name+'-1'+file_format)

#Clear temporary files
        if os.path.exists(file_name+'-0'+file_format):
            os.remove(file_name+'-0'+file_format)
        if os.path.exists(file_name+'-1'+file_format):
            os.remove(file_name+'-1'+file_format)

system('rm -rf *' + file_format)