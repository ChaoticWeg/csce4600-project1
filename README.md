# OS Project 1

### Links

- [Project PDF]
- [Submission] (requires Canvas login)

[Project PDF]: https://trello-attachments.s3.amazonaws.com/5c41f63b13055631b33664ab/5c744b9e218626267cadcf28/cc86456e8319a2b8fe1d93db1c1d4afa/OSProject1-2019.pdf

[Submission]: https://unt.instructure.com/courses/10450/assignments/246326

### Building

```bash
    $ make
```

### Generating Data

```bash
    $ make data
```

Generates 200 simulated processes and writes them to `data/processes.dat`. Note that this is equivalent to:

```bash
    $ ./generate 200 > data/processes.dat
```

### Scheduling

Recommended usage (e.g. 200 processes):

```bash
    $ make all
    $ make data
    $ ./run < data/processes.dat
```

### TODO: update usage as scope expands

