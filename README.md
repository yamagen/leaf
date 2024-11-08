# leaf

stem leaf calculator

## Synopsis

```zsh
$ leaf input.txt > output.txt
```

## Description

This program reads a file and calculates the number of stems and leaves in the file.

## Data File

```text
$ cat data1.txt
kihon_data
-3
5
6
12
12
15
23
$ leaf data1.txt

Processing file: data1.txt
        kihon_data

   stem * 10 + leaf = 1 * data
 ==================================
 stem | leaf (N = 7)
 ----------------------------------
    0 | 3
    0 | 56
    1 | 225
    2 | 3

```
