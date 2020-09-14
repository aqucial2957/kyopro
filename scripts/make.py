import argparse
import os
import sys
from pathlib import Path

def parse() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser()
    parser.add_argument('contest')
    parser.add_argument('-n', '--number', type=int, default=6)

    return parser

def generate_files(args: argparse.Namespace) -> None:
    contest = args.contest
    number = args.number

    if contest.startswith('abc'):
        os.chdir('AtCoder/ABC')
    elif contest.startswith('arc'):
        os.chdir('AtCoder/ARC')
    elif contest.startswith('agc'):
        os.chdir('AtCoder/AGC')
    else:
        os.chdir('AtCoder/others')

    if not os.path.exists(contest):
        os.mkdir(contest)
    os.chdir(contest)

    for i in range(number):
        filename = chr(ord('a') + i) + '.cpp'
        if not os.path.exists(filename):
            Path(filename).touch()
        os.system('code ' + filename)

def main() -> None:
    parser = parse()
    args = parser.parse_args()
    generate_files(args)

if __name__ == '__main__':
    main()