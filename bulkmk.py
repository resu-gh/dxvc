#!//usr/bin/env python3

import pathlib
import argparse
import shutil
import subprocess
import sys


def benchmarks():
    return list(
        map(
            lambda t: ".".join(t.split(".")[-2:]),
            (
                subprocess.check_output(f"java -jar {args.jar} -l", shell=True)
                .__str__()
                .split("\\n")[1:-1]
            ),
        )
    )


def main(args):
    benchmark_l = benchmarks()

    if args.list:
        for k, v in enumerate(benchmark_l):
            print(k, v)
        return

    benchmark_s = []

    hl = "\033[32m"
    hl2 = "\033[35m"
    rs = "\033[0m"

    if len(args.range) == 2:
        benchmark_s = benchmark_l[args.range[0] : args.range[1]]
        print(f"{hl}Running benchmarks{rs} #[{args.range[0]}, {args.range[1]}]")
    else:
        if args.range[0] >= len(benchmark_l):
            args.range[0] = len(benchmark_l) - 1
        benchmark_s = [benchmark_l[args.range[0]]]
        print(f"{hl}Running benchmark{rs} #{args.range[0]}")

    for b in benchmark_s:
        print(f"{hl}Running Makefile target{rs}")
        print(f"{hl2}", end="")
        print(f".SILENT: {b}")
        print(f".PHONY: {b} # run the {b} benchmark")
        print(f"{b}:")
        print(f"\tBENCH_NAME={b} BENCH_OUT={b.replace('.', '_')} $(MAKE) bench -s")
        print(f"{rs}", end="")
        if (
            subprocess.run(
                f"BENCH_NAME={b} BENCH_OUT={b.replace('.', '_')} make bench -s",
                shell=True,
            ).returncode
            != 0
        ):
            sys.exit("ERR")


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


def parserPanic(parser, msg):
    eprint(msg)
    parser.print_help()
    sys.exit()


def checkDeps(xs):
    for x in xs:
        if shutil.which(x) is None:
            sys.exit(f"Executable `{x}` not found!")


def checkJAR():
    class CheckJAR(argparse.Action):
        def __call__(self, parser, args, values, _) -> None:
            if not pathlib.Path(values).is_file():
                parserPanic(parser, f"error: file Not Found `{values}`")
            isJAR = subprocess.check_output(
                f"file --mime-type {values} | cut -d ':' -f 2 | tr -d ' \\n'",
                shell=True,
            ).decode("UTF-8")
            if isJAR != "application/java-archive":
                parserPanic(parser, f"error: wrong type, `{values}` is not a JAR")
            setattr(args, self.dest, values)

    return CheckJAR


def checkRange():
    class CheckRange(argparse.Action):
        def __call__(self, parser, args, values, _) -> None:
            if not 1 <= len(values) <= 2:
                parserPanic(parser, "error: invalid -r [begin, end?] length: (1 or 2)")
            if len(values) == 2 and values[0] > values[1]:
                parserPanic(
                    parser, "error: invalid -r [begin, end] range (note: begin < end)"
                )
            if values[0] < 0:
                parserPanic(
                    parser, "error: invalid -r [begin, end] range (note: begin >= 0)"
                )
            setattr(args, self.dest, values)

    return CheckRange


if __name__ == "__main__":
    checkDeps(["java", "make", "cut", "file", "tr"])

    parser = argparse.ArgumentParser(description="jvbench benchmarks runner")

    parser.add_argument(
        "-j",
        "--jar",
        type=str,
        help="jvbench jar path (default: ./env/jvbench/JVBench-1.0.jar)",
        action=checkJAR(),
        default="env/jvbench/JVBench-1.0.jar",
    )
    parser.add_argument(
        "-r",
        "--range",
        type=int,
        nargs="+",
        help="run a list of benchmarks [begin, end?]",
        action=checkRange(),
    )
    parser.add_argument(
        "-l", "--list", help="list available benchmarks w/ indexes", action="store_true"
    )

    args = parser.parse_args()

    if not args.list and not args.range:
        parserPanic(parser, "error: -l or -r [begin, end?] flags are required")

    main(args)
