import sys
import argparse
import subprocess
import os

# set up argparse
parser = argparse.ArgumentParser(
    description="Take in a file with a program name and test " \
    "cases to run that program against, print output to " \
    "programname.out"
)
parser.add_argument("filename",
    type=str,
    help="name of the file containing programname and test cases"
)

def main():
    try:
        args = parser.parse_args()

        exe = "execute.exe"

        with open(args.filename, 'r') as input:
            for i, line in enumerate(input):
                if i == 0:
                    # compile given program
                    file_to_run = line.strip()
                    compile_result = subprocess.run(
                        ["gcc", file_to_run, "-o", exe],
                        capture_output=True,
                        text=True,
                        shell=True,
                    )
                    
                    # check success of compilation
                    if compile_result.returncode != 0:
                        print("Unsucessful compile of", file_to_run)
                        print(compile_result.stderr)
                        sys.exit(1)
                else:
                    


    except Exception as ex:
        parser.print_usage()
        print(f"{sys.argv[0]}: {ex}", file=sys.stderr)
        sys.exit(1)

if __name__ == '__main__':
    main()