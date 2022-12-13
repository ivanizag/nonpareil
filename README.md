# Nonpareil - A Calculator Simulator 

Archived fork. For the latest version go to https://github.com/brouhaha/nonpareil

https://nonpareil.brouhaha.com/

Version 0.78 source code downloaded from https://www.hpcalc.org/details/2813

Original notice:
```
Nonpareil - a calculator simulator
Copyright 1995, 2003, 2004, 2005, 2006 Eric L. Smith <eric@brouhaha.com>

Nonpareil is Free Software, licensed under the Free Software Foundation's General Public License, Version 2. There is NO WARRANTY for Nonpareil.

Nonpareil is not an HP product, and is not supported or warranted by HP. 
```

[Original README](README)


## Additions

### Docker compilation
I didn't manage to build nonpareil in Ubuntu 20.04, but a container with 18.04 could, with lots of warnings.

To compile, run `./build.sh`. The executable and required files will be on the `dist` directory.

### Double size for hdpi displays
Use the parameter `--big` to double the size of the user interface.
