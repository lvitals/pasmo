**PASMO, CROSS-PLATFORM Z80 ASSEMBLER**  
(C) 2004-2022 Julián Albo  
Usage and distribution permitted under the terms of the GPL v.3 license.

For updates or more information:  
[https://pasmo.speccy.org/](https://pasmo.speccy.org/)

- - -

### To compile the project:

#### Configure the project:

`cmake -S . -B build`

#### Build the project:

`cmake --build build`

#### Run automatic tests via CTest:

`cd build && ctest --output-on-failure`

#### Run custom tests manually:

`./test_cli.sh`

- - -

### Documentation

The documentation is available only in English in the file `pasmodoc.html`, included in this package, or on the Pasmo website. Example `.asm` files are also available in the source package.

- - -

### To assemble:

`pasmo [ options ] file.asm file.bin [ symbols_file [ public_file ] ]`

- - -

### Options:

| **Option** | **Description** |
| --- | --- |
| `-d` | Show debug information during assembly. |
| `-1` | Show debug information also on the first pass. |
| `-v` | Verbose mode. Displays progress during assembly. |
| `-I` | Add a directory to the search path for files in `INCLUDE` and `INCBIN`. |
| `--bin` | Generate the object file in pure binary format, without a header. |
| `--hex` | Generate the object file in Intel HEX format. |
| `--prl` | Generate the object file in PRL format, suitable for CP/M Plus RSX. |
| `--cmd` | Generate the object file in CMD format for CP/M 86. |
| `--plus3dos` | Generate the object file with a PLUS3DOS header (Spectrum disk). |
| `--tap` | Generate a `.tap` file for Spectrum emulators (tape image). |
| `--tzx` | Generate a `.tzx` file for Spectrum emulators (tape image). |
| `--cdt` | Generate a `.cdt` file for Amstrad CPC emulators (tape image). |
| `--tapbas` | Same as `--tap`, but adds a Basic loader. |
| `--tzxbas` | Same as `--tzx`, but adds a Basic loader. |
| `--cdtbas` | Same as `--cdt`, but adds a Basic loader. |
| `--amsdos` | Generate the object file with an Amsdos header (Amstrad CPC disk). |
| `--msx` | Generate the object file with a header for use with `BLOAD` in MSX Basic. |
| `--public` | The symbol table listing will include only symbols declared as PUBLIC. |
| `--name` | Name for the header in formats that use it. If not specified, the file name will be used. |
| `--err` | Direct error messages to standard output instead of standard error. |
| `--nocase` | Make identifiers case-insensitive. |
| `--alocal` | Autolocal mode: labels starting with `_` are local, and their scope ends at the next global label. |
| `-B`, `--bracket` | Bracket-only mode: parentheses are reserved for expressions. |
| `-E`, `--equ` | Predefine a label. |
| `-8`, `--w8080` | Display a warning when using Z80 instructions that do not exist in the 8080. |
| `--86` | Generate 8086 code. |

- - -

**Note:** If no output format option is specified, `--bin` is assumed.

- - -

### Debug Information

Debug information is sent to standard output, while error messages are sent to standard error.

- - -

**Comments and feedback:**  
julian.notfound@gmail.com