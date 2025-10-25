import sys
import argparse
import re
#import subprocess
#import os

# set up argparse
parser = argparse.ArgumentParser(
    description="Take in two output files to compare against each " \
    "other, print to comparator.out file whether or not the output" \
    "matches, with details about the differing output if needed"
)
parser.add_argument("out1",
    type=str,
    help="the name of the first output file to compare"
)
parser.add_argument("out2",
    type=str,
    help="the name of the second output file to compare"
)

def split_test_cases(full_out):
    return [
        test_case.strip() 
        for test_case in re.split(r'-{16}', full_out.strip())
        if test_case.strip()
    ]

def parse_test_case(test_case):
    sections = {}
    current_section = None
    lines = test_case.splitlines()

    for line in lines:
        line = line.strip()

        if line.endswith(':') and line [:-1] in [
            "Command Line Arguments",
            "Program Output",
            "Error Output",
            "Exit Status",
        ]:
            current_section = line[:-1]
            sections[current_section] = ""
        elif current_section:
            sections[current_section] += line + "\n"
        
    return {
        section_name: section_contents.strip()
        for section_name, section_contents in sections.items()
    }

def compare_test_cases(test_case1, test_case2):
    differing_sections = []
    all_keys = set(test_case1.keys()).union(set(test_case2.keys()))

    for key in all_keys:
        test_case1_contents = test_case1.get(key, "").strip()
        test_case2_contents = test_case2.get(key, "").strip()

        if test_case1_contents != test_case2_contents:
            differing_sections.append(key)
    
    return (len(differing_sections) == 0, differing_sections)

def main():
    try:
        args = parser.parse_args()

        with open(args.out1, 'r') as o1, open(args.out2, 'r') as o2:
            out1 = o1.read()
            out2 = o2.read()

        out1_cases = split_test_cases(out1)
        out2_cases = split_test_cases(out2)

        if len(out1_cases) != len(out2_cases):
            print("Warning: Number of test cases differ between outputs")
        
        with open("Comparator.out", 'w') as output:
            have_found_diff = False

            for out1_case, out2_case in zip(out1_cases, out2_cases):
                parsed_case1 = parse_test_case(out1_case)
                parsed_case2 = parse_test_case(out2_case)
                match, differing_sections = compare_test_cases(
                    parsed_case1, parsed_case2)
                if not match:
                    if "Command Line Arguments" in differing_sections:
                        print("Warning: mismatching command line arguments"\
                        " between supposedly matching cases")
                    if not have_found_diff:
                        output.write("Differing Output\n")
                        have_found_diff = True
                    output.write("With command line arguments ")
                    output.write(parsed_case1["Command Line Arguments"])
                    output.write(", get differing output in:\n")
                    for section in differing_sections:
                        output.write(section)
                        output.write("\n")
            
            # finished looping through all test cases and no differences found
            if not have_found_diff:
                output.write("Matching Output")

    except Exception as ex:
        parser.print_usage()
        print(f"{sys.argv[0]}: {ex}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()