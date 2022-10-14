import pathlib
import argparse
import shutil
import subprocess
import sys


def checkdeps(xs):
    for x in xs:
        if shutil.which(x) is None:
            sys.exit(f"Executable `{x}` not found!")


def select(args):
    jvbench_tests = list(
        map(
            lambda t: ".".join(t.split(".")[-2:]),
            (
                subprocess.check_output(f"java -jar {args.jar} -l", shell=True)
                .__str__()
                .split("\\n")[1:-1]
            ),
        )
    )

    if args.range:
        return jvbench_tests[args.range[0] : args.range[1]]

    while True:
        for i, test in enumerate(jvbench_tests):
            print(i, test)

        a = input(f"Select a benchmark (q: quit, a: all) [0, {len(jvbench_tests)-1}] ")

        if a.isdigit() and int(a) >= 0 and int(a) < len(jvbench_tests):
            return [jvbench_tests[int(a)]]
        if a == "q":
            sys.exit(0)
        if a == "a":
            return jvbench_tests


def main(args):
    xs = ["java", "make"]
    checkdeps(xs)

    if not pathlib.Path(args.jar).is_file():
        sys.exit(f"File Not Found `{args.jar}`")

    if args.range:
        if args.range[0] > args.range[1]:
            print("error: invalid -r [begin, end] range (note: begin < end)")
            parser.print_help()
            sys.exit()
        if args.range[0] < 0:
            print("error: invalid -r [begin, end] range (note: begin >= 0)")
            parser.print_help()
            sys.exit()

    benchmark_s = select(args)

    for b in benchmark_s:
        if (
            subprocess.run(
                f"TEST_NAME={b} TEST_OUT={b.replace('.', '_')} make bench",
                shell=True,
            ).returncode
            != 0
        ):
            sys.exit("ERR")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="jvbench benchmarks runner")

    parser.add_argument(
        "-j",
        "--jar",
        type=str,
        nargs=1,
        help="jvbench jar path (default: ./env/jvbench/JVBench-1.0.jar)",
        default="env/jvbench/JVBench-1.0.jar",
    )
    parser.add_argument(
        "-r",
        "--range",
        metavar=("begin", "end"),
        type=int,
        nargs=2,
        help="run a list of benchmarks [begin, end]",
    )

    args = parser.parse_args()

    main(args)
