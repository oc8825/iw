import sys
import argparse
import subprocess
import os

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

def main():
    try:
        args = parser.parse_args()
        print(args.out1)
        print(args.out2)

    except Exception as ex:
        parser.print_usage()
        print(f"{sys.argv[0]}: {ex}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()