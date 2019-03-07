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

### Usage

Generate new list of N-many simulated processes:

```bash
    $ ./generate <N>
```

Recommended usage (e.g. 200 processes):

```bash
    $ ./generate 200 > $datadir/processes.dat
    $ ./run < $datadir/processes.dat
```

### TODO: update usage as scope expands

