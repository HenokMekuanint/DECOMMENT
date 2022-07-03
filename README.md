# DECOMMENT USING DETERMINISTIC FINITE AUTOMATA

In this part you will implement a C program that will implement a subset of the De‑commenting job of
the C preprocessor. You should watch the Deterministic Finite Automata Lecture before you begin
working on this part.
Your C program must be a Linux filter. A filter is a program that reads characters from the standard
input stream, and writes characters to the standard output stream (the terminal screen) and possibly
to the standard error stream. Specifically, your program must (1) read text, presumably a C program,
from the standard input stream, (2) write that same text to the standard output stream with each
comment replaced with a space, as prescribed below, and (3) write error and warning messages as
appropriate to the standard error stream. A typical execution of your program from the shell might
look like this:

![DFA_DESIGN](https://user-images.githubusercontent.com/90408697/177046613-d002fdfc-53f8-468e-941e-b34ca03ea250.jpg)

