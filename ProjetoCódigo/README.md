[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=7781098&assignment_repo_type=AssignmentRepo)
# Project_Normal_Template

This is a C program template tailored for:

- GCC, GDB, MAKE, VALGRING and DOXYGEN
- VS CODE editor

## What's included?

### CSV Files

The following *comma separaved value* (CSV) files contain all information that must be imported:

- `csv_data/flights.csv` - Flight data ordered by date.

- `csv_data/airports.csv` - Airports information.

- `csv_data/airline.csv` - Airlines information.


#### Reading CSV files

You have examples on *parsing* CSV files in the course repositories.

Some **useful notes**:

- Be aware that you should *right trim* each CSV line before *tokenizing* the *string* (see `rtrim`), because there are usually some unwanted characters at the end of each line read, e.g., *newlines* and *carriage returns*.

- The `atof` function expects the decimal point as a *point* `.`; some values have commas as the
decimal point, i.e., `,`. You should use the provided `replace` function to convert them.

### Abstract Data Types

Includes the **ADT List** and **ADT Map** to support the project's development.

For each ADT, two implementations are provided: based on *array list* and *linked list*. You should choose the "best" implementation at compile time.


### Miscellaneous utilities

The following modules are provided; they can be extended/modified, if you wish:

- **`time`** module: time manipulation;

- **`input`** module: for user data input, includes an updated `splitString` function which automatically deals with *windows/linux* CSV line terminations.
  
