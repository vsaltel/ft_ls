# ft_ls

My version of the standard ls program.
Display files in a directory.

42 Paris school algorithm project.

## Build

Compilation :
```
make
```

Clean objects files :
```
make clean
```

Clean entire project :
```
make fclean
```

## Usage

```
./ft_ls [-CGRSaflrt1] [file ...]
```

## Options

- -C  : Force multi-column output; this is the default when output is to a terminal
- -G  : Enable colorized output
- -R  : Recursively list subdirectories encountered
- -S  : Sort files by size
- -a  : Include directory entries whose names begin with a dot
- -f  : Output is not sorted. This option turns on the -a option
- -r  : Reverse the order of the sort to get reverse lexicographical order or the oldest entries first
- -t  : Sort by time modified (most recently modified first)
- -1  : Force output to be one entry per line.
