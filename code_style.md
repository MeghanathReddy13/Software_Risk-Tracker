# Coding style standard verification

This repo contains a modified version of the configuration file for the `clang-format` tool. The format is based on the Mozilla rules for C++ with a few local changes.

The clang-format tool is installed on the server. This tool is also integrated with git.

## How to use clang-format

Show formatting issues (but don't change anything):

* Change into the folder with your source code
* Type `clang-format --dry-run filename.cpp`
* Formatting problems will be displayed similar to the way the compiler displays diagnostics

Automatically fix formatting issues (reformat your code):

* Change into the folder with your source code
* Type `clang-format -i filename.cpp`
* The specified file will be re-formatted and saved (replacing the existing file)

Reformat code in staged files:

* Change into the repo folder that contains the code to reformat
* Type `git clang-format`
* The formatted source code will written to the working tree

Reformat code in the most recent commit:

* Change into the repo folder that contains the code to reformat
* Type `git clang-format HEAD~1`
* The formatted source code will be written to the working tree

Type `clang-format --help` for more information about the stand-alone tool.  
Type `git clang-format -h` in your repo for more information about the git integrated tool.

[Back](/README.md)
