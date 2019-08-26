# Simple_shell  :shell:

This repository contains a UNIX command line interpreter, called simple_shell written in C language.

![simple-shell](https://media.giphy.com/media/UW7G17H9PLQbw1ksHX/giphy.gif)

## What it does

 - Displays a prompt and waits for the user to type a command; the prompt is displayed again each time a command has been executed.

 - The command lines are simple, no semicolons, no pipes, no redirections or any other features.

 - The command lines are made only of one word. No arguments will be passed to programs.

 - If an executable cannot be found, prints an error message and displays the prompt again.

 - Handles the “end of file” condition (Ctrl+D).


## :computer:  Installation 

- Clone the repository in a new directory:

```bash
    $ git clone https://github.com/dabrabgellak/simple_shell.git
```

- The simple_shell will be compiled with gcc 4.8.4. To compile it use the following flags:

```bash
    $ gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

## Interactive mode

```bash
    $ ./hsh
```
## Non-interactive mode

```bash
    $ echo "/bin/ls" | ./hsh
```

## :pushpin: Examples

Some of the commands that work on the simple_shell.

```bash
    $env
    XDG_SESSION_ID=3
    TERM=xterm-256color
    SHELL=/bin/bash
    ...
```

```bash
    $pwd
    /home/vagrant/simple_shell
```

```bash
    $touch Hello
    $ls
      AUTHORS	functions.c   Hello...
    $vim Hello
      (Types something in the file)
    $cat Hello
      Hello Nats
    $rm Hello
    $ls
      AUTHORS	functions.c.  ...
```


## Authors
- [Barbara Calle](@889@holbertonschool.com)
- [Daniela Ramirez](dans@dans.com)
- [Natalia Medina](@865@holbertonschool.com)
