# Square equation solver (only real solutions)
## Decription
Program takes three floating-point numbers assuming them as coefficients of square equation. Input via standard input interface and command line arguments is supported.
## Compilation
### Requaremets: 
Build: g++ version 10 or higher
Documentation: doxygen version 1.5 or higher

### Build:

* To compile program in USER standart input and command-line argument mode with make run 
```
 make -f Makefile-oos 
```

* To compile program in TEST mode with make run 
```
make -f Makefile-oos OPTIONS="-DTEST"
```
or 
```
make -f Makefile-oos tests
```

* To generate documentation with make, use 
```
make -f Makefile-oos docs
```

## Usage

* To specify coefficients using command-line as flags, run
```
./main.out -flag=[float]
```
where flag can be 'a', 'b' or 'c'.
>[!NOTE]
>Zeros as default. If specified at least one argument (even incorect), all unspecified coefficients will be zeros.

* To use program in terminal input mode, run ./main.out without flags


