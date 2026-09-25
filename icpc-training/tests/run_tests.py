#!/usr/bin/env python3
"""Compile every solution and run it on its sample tests.

Usage:  python3 tests/run_tests.py [topic ...]      (topics: greedy bitwise number-theory)

A test is  tests/<topic>/<name>.<k>.in  with expected output  <name>.<k>.out.
Problems that accept several correct outputs have a checker
tests/checkers/<name>.py exposing  check(inp, expected, got) -> bool.
Otherwise outputs are compared token by token.
"""
import importlib.util, os, subprocess, sys, glob

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILD = os.path.join(ROOT, "tests", ".build")
os.makedirs(BUILD, exist_ok=True)
CXX = os.environ.get("CXX", "g++")

def checker(name):
    path = os.path.join(ROOT, "tests", "checkers", name + ".py")
    if not os.path.exists(path):
        return None
    spec = importlib.util.spec_from_file_location(name, path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod.check

def main():
    topics = sys.argv[1:] or ["greedy", "bitwise", "number-theory"]
    fails = total = 0
    for topic in topics:
        for src in sorted(glob.glob(os.path.join(ROOT, topic, "*.cpp"))):
            name = os.path.basename(src)[:-4]
            exe = os.path.join(BUILD, topic + "_" + name)
            r = subprocess.run([CXX, "-std=c++17", "-O2", "-Wall", "-Wextra", "-o", exe, src],
                               capture_output=True, text=True)
            if r.returncode != 0 or r.stderr.strip():
                print(f"[BUILD] {topic}/{name}\n{r.stderr}")
                if r.returncode != 0:
                    fails += 1
                    continue
            chk = checker(name)
            tests = sorted(glob.glob(os.path.join(ROOT, "tests", topic, name + ".*.in")))
            if not tests:
                print(f"[WARN ] {topic}/{name}: no tests")
            for tin in tests:
                total += 1
                inp = open(tin).read()
                exp = open(tin[:-3] + ".out").read()
                got = subprocess.run([exe], input=inp, capture_output=True, text=True, timeout=20).stdout
                ok = chk(inp, exp, got) if chk else exp.split() == got.split()
                if not ok:
                    fails += 1
                    print(f"[FAIL ] {os.path.basename(tin)}\n--- expected\n{exp}--- got\n{got}")
    print(f"{total - fails}/{total} sample tests passed")
    sys.exit(1 if fails else 0)

if __name__ == "__main__":
    main()
