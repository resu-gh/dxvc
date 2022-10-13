import pathlib
import argparse
import shutil
import subprocess
import sys


def checkdeps(xs):
    for x in xs:
        if shutil.which(x) is None:
            sys.exit(f"Executable `{x}` not found!")


def select(jvbench_jar):
    jvbench_tests = list(
        map(
            lambda t: ".".join(t.split(".")[-2:]),
            (
                subprocess.check_output(f"java -jar {jvbench_jar} -l", shell=True)
                .__str__()
                .split("\\n")[1:-1]
            ),
        )
    )

    benchmark_s = []

    while not benchmark_s:
        for i, test in enumerate(jvbench_tests):
            print(i, test)

        a = input(f"Select a benchmark (q: quit, a: all) [0, {len(jvbench_tests)-1}] ")

        if a.isdigit() and int(a) >= 0 and int(a) < len(jvbench_tests):
            benchmark_s.append(jvbench_tests[int(a)])
        if a == "q":
            sys.exit(0)
        if a == "a":
            benchmark_s = jvbench_tests

    return benchmark_s


def main(jvbench_jar):
    xs = ["java", "make"]
    checkdeps(xs)

    if not pathlib.Path(jvbench_jar).is_file():
        sys.exit(f"File Not Found `{jvbench_jar}`")

    benchmark_s = select(jvbench_jar)

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
    )
    args = parser.parse_args()
    if args.jar:
        main(args.jar)
    else:
        main("env/jvbench/JVBench-1.0.jar")
