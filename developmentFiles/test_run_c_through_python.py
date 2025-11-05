import subprocess
import os

c_code = "TestRunningC.c"
exe = "TestRunningC.exe"

compile_result = subprocess.run(
    ["gcc", c_code, "-o", exe],
    capture_output=True,
    text=True,
    shell=True,
)

if compile_result.returncode != 0:
    print("compilation error")
    print(compile_result.stderr)
else:
    print("successful compile")
    run_result = subprocess.run(
        [exe],
        capture_output=True,
        text=True,
        shell=True,
    )

    print("Program Output:")
    print(run_result.stdout)

    if run_result.stderr:
        print("Error Output:")
        print(run_result.stderr)
