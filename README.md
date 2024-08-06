# get_next_line

### About

This project is about programming a function that returns a line read from a file descriptor. If the function is inserted into a loop, it allows the content of a file to be returned, line by line, until the end of the file.

### Mandatory

- [X] get_next_line() function should let you read the text file pointed to by the file descriptor, one line at a time.
- [X] The function should return the line that was read. If it's empty or gives an error returns NULL.
- [X] Function works when it's reading a file or a standard input.
- [X] Returned line should include the terminating \n character, except if it's the end of the file and the line does not end with \n.
- [X] The  get_next_line.h header file should include at least the get_next_line() function.
- [X] All aditional functions should be included in get_next_line_utils.c file.
- [X] To define the buffer size for read(), add the option to the compiled file -D BUFFER_SIZE = n.

FORBIDDEN:
 Libft
 lseek()
 Global variables

 ### Bonus

- [X] Use only one static variable.
- [X] Manage multiple file descriptors at the same time.
- [X] Bonus files should include a suffix _bonus.[c/h]:
  - [X] get_next_line_bonus.c
  - [X] get_next_line_bonus.h
  - [X] get_next_line_utils_bonus.c
