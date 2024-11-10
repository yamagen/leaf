# leaf: stem leaf distribution printer

## Synopsis and options

```zsh
Usage: leaf [options] [data_file1 data_file2 ...]
Stem and leaf style distribution printer
by Hilofumi Yamamoto, Institute of Science Tokyo
Version 2.0 Last change: 2024/11/10-11:46:46.05
Options:
  -h, --help     Show this help message and exit
  -q, --quiet    Suppress header output
  -v, --verbose  Show detailed processing information
```

## Description

This program reads a file and calculates the number of stems and leaves in the file.

## Data File

```text
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

$ leaf data1.txt

Filename: data1.txt
data_name

stem * 10 + leaf = 1 * data  (N = 9)
----------------
 -4 | 4
 -3 |
 -2 | 8
 -1 | 7
  0 | 56
  1 | 225
  2 | 3
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
