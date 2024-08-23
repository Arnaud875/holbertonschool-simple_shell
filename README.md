<h1 align="left">Project Simple Shell</h1>

###

<h3 align="left">Description</h3>

###

<p align="left">This project is a simple shell implementation that allows users to execute basic commands in a Unix-like environment. It supports standard input/output redirection, running commands in the background, and basic command chaining with pipes. Ideal for learning how shells work and experimenting with process control in a minimalistic environment.</p>

###

<h3 align="left">List of allowed functions and system calls+</h3>

###

<p align="left">- all functions from string.h<br>- access<br>- chdir<br>- close<br>- closedir<br>- execve<br>- exit<br>- _exit<br>- fflush<br>- fork<br>- free<br>- getcwd<br>- getline<br>- getpid<br>- isatty<br>- kill<br>- malloc<br>- open<br>- opendir<br>- perror<br>- printf<br>- fprintf<br>- vfprintf<br>- sprintf<br>- putchar<br>- read<br>- readdir<br>- signal<br>- stat (__xstat)<br>- lstat (__lxstat)<br>- fstat (__fxstat)<br>- strtok<br>- wait<br>- waitpid<br>- wait3<br>- wait4<br>- write</p>

###

<h3 align="left">Compilation</h3>

###

<p align="left">gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh</p>

###

<p align="left">After compilation, you can run the shell with: <br>./hsh</p>

###

<h3 align="left">Example</h3>

###

<p align="left">Once running, you can enter commands and built-ins like you would in any other shell</p>

###

<p align="left">$ ls <br>$ pwd<br>$ clear<br>$ cat<br>$ env<br>$ printenv<br>$ exit</p>

###

<h3 align="left">Integrated features</h3>

###

<p align="left">The shell supports several built-in commands: <br>- cd <path>: Changes the current directory to <path>. <br>- env: Displays environment variables. <br>- exit: Exits the shell with the specified exit code.</path></path></p>

###

<h3 align="left">Code structure</h3>

###

<p align="left">The project is organized into several files: <br>- main.h: Contains structure definitions and function declarations. <br>- main.c: Contains the program entry point and the main shell loop. <br>- shell.c: Contains the main functions for command execution, built-in command management and memory management.</p>

###

<h3 align="left">Function details</h3>

###

<p align="left">- get_shell_instance: Returns a single instance of the shell. <br>- shell_exit: Releases memory and terminates the process with the specified exit code. <br>- cd: Changes the current directory. <br>- env: Displays environment variables. <br>- get_builtin_command: Checks whether a command is embedded and executes it.<br> - run_process_command: Executes a command as a child process.<br> - find_executable_path: Finds the executable path.<br>- execute_command: Executes a command, embedded or not.<br> - input: Reads a line of text from standard input. <br>- trim: Removes spaces at the beginning and end of a string. <br>- if_executable_exist: Checks whether an executable exists in a given directory. <br>- get_executable_path: Finds the path to an executable by searching the PATH. <br>- free_all: Frees memory allocated for an array of strings. <br>- make_tokens: divides a string into tokens <br>- handle_sigint: handles the SIGINT signal (interrupted by Ctrl+C).</p>

###

<h3 align="left">Feature</h3>

###

<h4 align="left">Interactive mode</h4>

###

<p align="left">To launch the shell in interactive mode, simply run : <br>./hsh<br>A command prompt ($) will appear, allowing you to execute commands as in a standard shell.</p>

###

<h4 align="left">Non-interactive mode</h4>

###

<p align="left">To use the shell in non-interactive mode, pass the commands as arguments when calling the program:<br>./hsh ls -l<br>The shell will execute the command and exit immediately.</p>

###

<h4 align="left">Flowchart</h4>

###

<p align="left">![image]https://github.com/Arnaud875/holbertonschool-simple_shell/blob/main/flowchart.png</p>

###

<h4 align="left">Authors</h4>

###

<p align="left">NChaouch<br>Arnaud875</p>

###

<h4 align="left">Licence</h4>

###

<p align="left">This project is licensed under the MIT license. You are free to use, modify and distribute it under the terms of the license.</p>

###

<h4 align="left"></h4>

###
