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
parser.add_argument("source",
    type=str,
    help="name of LLM that generated this code: 'Claude' or 'Qwen'"
)

def main():
    try:
        args = parser.parse_args()

        exe = "execute.exe"

        # use filename as input
        with open(os.path.join("testing", args.filename), 'r', encoding="utf-8") as input:
            # process first line, which provides programname
            program_name = input.readline().strip()
            program_name_short = program_name.split('.')[0].strip()
            output_file = program_name_short + args.source + ".out"

            # compile given program
            compile_result = subprocess.run(
                ["gcc", program_name, "-o", exe],
                capture_output=True,
                text=True,
                shell=True,
            )

            # verify success of compilation
            if compile_result.returncode != 0:
                print("Unsucessful compile of", program_name)
                print(compile_result.stderr, file=sys.stderr)
                sys.exit(3)
            
            # print test cases to programname.out
            with open(output_file, 'w') as output:
                for i, line in enumerate(input):
                    # label which test case this is
                    output.write("----------------\n")
                    test_case_identifier = "Test Case " + str(i + 1)
                    output.write(test_case_identifier)
                    output.write("\n")
                    output.write("Command Line Arguments:\n")
                    output.write(line.strip())
                    output.write("\n")
                    output.write("\n")

                    # run named program on this test case
                    execute_command = [exe]
                    command_line_args = line.split(' ')
                    for arg in command_line_args:
                        execute_command.append(arg)
                    run_result = subprocess.run(
                        execute_command,
                        capture_output=True,
                        text=True,
                        shell=True,
                    )

                    # print standard output
                    output.write("Program Output:\n")
                    output.write(run_result.stdout)
                    output.write("\n")

                    # print error output
                    output.write("Error Output:\n")
                    if run_result.stderr:
                        output.write(run_result.stderr)
                    else:
                        output.write("None.")
                    output.write("\n")
                    output.write("\n")
                    
                    # print exit status
                    output.write("Exit Status:\n")
                    output.write(str(run_result.returncode))
                    output.write("\n")
                    output.write("\n")

    except Exception as ex:
        parser.print_usage()
        print(f"{sys.argv[0]}: {ex}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
