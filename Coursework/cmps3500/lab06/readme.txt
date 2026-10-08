The prolog interpreter on Odin is GNU Prolog 1.4.5 (gprolog and gplc)

GNU prolog has an interactive interpreter that uses a read-execute-write loop
(gprolog) and a compiler that produces byte code (gplc).

The Makefile uses gplc, but if there are no initialization statements, the
produced binaries will start gprolog to prompt for queries.

To start the interpreter, use the following commmand:

gprolog

The gprolog prompt looks like the following:

| ?- 

To exit the interpreter, use the following command:

| ?- halt.


Important notes once in the Prolog interpreter:

o all statements must be terminated by . (period character)

o Prolog variables must begin with uppercase letters 

o Predicate names CANNOT have dashes

o the up arrow will recall previous commands

o TAB completes commands

o a prolog program consists of facts, rules, or queries

o facts and rules are usually read in from a file (although can be typed in)

o queries are generally entered interactively 

o to compile and load test.pl (do not type the .pl extension): 

    | ?- [test]. 

o you can trace a program with
  
    | ?-  trace.

o you can turn off tracing with

    | ?-  notrace.

o you can get a listing of the database with

    | ?-  listing. 

o hit ; to continue query 

o hit RETURN to end query.

o Hit ESC- for escape code.

o hit TAB for listing of all available queries (TAB 'a' will list commands
  beginning with 'a'.

