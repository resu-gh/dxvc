import pathlib
import shutil
import subprocess
import sys


def checkdeps(xs):
    for x in xs:
        if shutil.which(x) is None:
            sys.exit(f"Executable `{x}` not found!")


def select():
    jvbench_tests = list(
        map(
            lambda t: ".".join(t.split(".")[-2:]),
            (
                subprocess.check_output("java -jar JVBench-1.0.jar -l", shell=True)
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


def main():
    benchmark_s = select()

    for b in benchmark_s:
        if (
            subprocess.run(
                f"TEST_NAME={b} TEST_OUT={b.replace('.', '_')} make",
                shell=True,
            ).returncode
            != 0
        ):
            sys.exit("ERR")


if __name__ == "__main__":
    xs = ["java", "make"]
    checkdeps(xs)

    jvbench_jar = pathlib.Path("JVBench-1.0.jar")
    if not jvbench_jar.is_file():
        sys.exit(
            "File Not Found `./JVBench-1.0.jar`. Download it from https://www.github.com/usi-dag/JVBench"
        )

    main()
