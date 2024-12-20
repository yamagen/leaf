# slp: stem leaf plotter

![GitHub license](https://img.shields.io/github/license/yamagen/slp)
[![DOI](https://zenodo.org/badge/883773387.svg)](https://doi.org/10.5281/zenodo.14061335)
![Static Badge](https://img.shields.io/badge/github-repository-blue?logo=github)

## Synopsis and options

```zsh
Usage: slp [options] [data_file1 data_file2 ...]
Stem and leaf distribution plotter
by Hilofumi Yamamoto, Institute of Science Tokyo
Version 2.0 Last change: 2024/11/11-20:14:07.05
Options:
  -h, --help     Show this help message and exit
  -q, --quiet    Suppress header output
  -v, --verbose  Show detailed processing information
```

## Description

This program reads a file, calculates stems and leaves, and prints a stem-and-leaf display to show the data distribution. It now supports negative values, enabling analysis of datasets with a broader range of values.

## Data File

```zsh
$ cat data1.txt
data_name
-36
-12
-3
5
6
12
12
15
23
```

In case of a negative value, the program will calculate the stem and leaf as follows:

```zsh
$ slp data1.txt

Filename: data1.txt
data_name

stem * 10 + leaf = 1 * data  (N = 9)
--------------------
-4 | 6
-3 |
-2 | 2
-1 | 3
 0 | 56
 1 | 225
 2 | 3
 3 |
```

Hence, the -36 is calculated as -4 | 6 and -4 means the range from -40 to -30.
the leaf 6 means the value -36.
Do not mix up the stem and leaf with the original value.

## Standard input supported

```zsh
$ awk '{print $3}' data4.txt |./slp

Standard input:
Third_Year

Stem * 10 + Leaf = Data  (N = 10)
-----------------------------
 0 | 7
 1 | 49
 2 | 345
 3 | 2
 4 | 45
 5 | 2
 6 |
```

## Installation

```zsh
$ make
$ make install
```

## Author

Hilofumi Yamamoto, Ph.D. Institute of Science Tokyo

## License

MIT License

## References

```bibtex
@book{tukey1977eda,
  author    = {John W. Tukey},
  title     = {Exploratory Data Analysis},
  year      = {1977},
  publisher = {Addison-Wesley},
  address   = {Reading, MA},
  note      = {A foundational work in exploratory data analysis (EDA) that introduced the stem-and-leaf display as a way to visualize data distributions effectively.}
}

@article{tukey1962future,
  author    = {John W. Tukey},
  title     = {The Future of Data Analysis},
  journal   = {Annals of Mathematical Statistics},
  year      = {1962},
  volume    = {33},
  number    = {1},
  pages     = {1--67},
  note      = {An influential article that laid the groundwork for exploratory data analysis and inspired further development of data visualization methods, including the stem-and-leaf display. /home/yamagen/Dropbox/BIBFILES/BookArchive/Book035_20240420/1177704711.pdf}
}

@book{hoaglin1983robust,
  author    = {David C. Hoaglin and Frederick Mosteller and John W. Tukey},
  title     = {Understanding Robust and Exploratory Data Analysis},
  year      = {1983},
  publisher = {Wiley},
  address   = {New York},
  note      = {This book provides a comprehensive overview of EDA and robust statistical methods, covering various visualization techniques, including the stem-and-leaf display.}
}

@book{mosteller1977regression,
  author    = {Frederick Mosteller and John W. Tukey},
  title     = {Data Analysis and Regression: A Second Course in Statistics},
  year      = {1977},
  publisher = {Addison-Wesley},
  address   = {Reading, MA},
  note      = {Focuses on data analysis and regression from an EDA perspective, with insights into data visualization methods that aid in understanding data distributions.}
}
```

## History

```text
 leaf
 Stem and leaf style distribution printer
 by Hilofumi Yamamoto, Institute of Science Tokyo
 Version 2.0 2024.11.05
 by Hilofumi Yamamoto, University of Tsukuba
 Version 1.0 1996.06.18
 Usage: % leaf data_file
```
