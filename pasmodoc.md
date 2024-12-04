# Pasmo documentation.

(C) 2004-2022 Julián Albo.

Use and distribution allowed under the terms of the GPL license.

Last revision date: 05-mar-2022

Current Pasmo version: 0.5.5

## Index.

*   [Introduction.](#intro)
*   [Installation.](#install)
*   [Command line use.](#command)
*   [Code generation modes.](#codegen)
    *   [Default mode.](#codegendefault)
    *   [\--bin mode.](#codegenbin)
    *   [\--hex mode.](#codegenhex)
    *   [\--prl mode.](#codegenprl)
    *   [\--cmd mode.](#codegencmd)
    *   [\--tap mode.](#codegentap)
    *   [\--tzx mode.](#codegentzx)
    *   [\--cdt mode.](#codegencdt)
    *   [\--tapbas mode.](#codegentapbas)
    *   [\--tzxbas mode.](#codegentzxbas)
    *   [\--cdtbas mode.](#codegencdtbas)
    *   [\--plus3dos mode.](#codegenplus3dos)
    *   [\--amsdos mode.](#codegenamsdos)
    *   [\--msx mode.](#codegenmsx)
    *   [\--sdrel mode.](#codegensdrel)
    *   [\--trs mode.](#codegentrs)
    *   [Symbol table.](#codegensymbol)
*   [Source code format.](#source)
    *   [Generalities.](#sourcegeneral)
    *   [Literals.](#sourcelit)
        *   [Numeric literals.](#sourcelitnum)
        *   [String literals.](#sourcelitstr)
    *   [Identifiers.](#sourceident)
    *   [File names.](#sourcefilename)
    *   [Labels.](#sourcelabel)
*   [Directives.](#directives)
    *   [.ERROR](#direrror)
    *   [.SHIFT](#dirshift)
    *   [.WARNING](#dirwarning)
    *   [DEFB](#dirdefb)
    *   [DEFL](#dirdefl)
    *   [DEFM](#dirdefm)
    *   [DEFS](#dirdefs)
    *   [DEFW](#dirdefw)
    *   [DS](#dirds)
    *   [DW](#dirdw)
    *   [ELSE](#direlse)
    *   [END](#dirend)
    *   [ENDIF](#direndif)
    *   [ENDM](#direndm)
    *   [ENDP](#direndp)
    *   [EQU](#direqu)
    *   [EXITM](#direxitm)
    *   [IF](#dirif)
    *   [IFDEF](#dirifdef)
    *   [IFNDEF](#dirifndef)
    *   [INCLUDE](#dirinclude)
    *   [INCBIN](#dirincbin)
    *   [IRP](#dirirp)
    *   [LOCAL](#dirlocal)
    *   [MACRO](#dirmacro)
    *   [ORG](#dirorg)
    *   [PROC](#dirproc)
    *   [PUBLIC](#dirpublic)
    *   [REPT](#dirrept)
*   [Operators.](#operators)
    *   [Generalities.](#opergeneral)
    *   [Table of precedence.](#opertable)
    *   [List of operators.](#operlist)
*   [Macros.](#macros)
    *   [Generalities.](#macrogeneral)
    *   [Directives.](#macrodirectives)
        *   [.SHIFT](#macroshift)
        *   [ENDM](#macroendm)
        *   [EXITM](#macroexitm)
        *   [IRP](#macroirp)
        *   [MACRO](#macromacro)
        *   [REPT](#macrorept)
*   [About suggestions and possible improvements.](#discussion)
*   [Tricks.](#tricks)
*   [Bugs.](#bugs)
*   [Epilogue.](#epilogue)

## Introduction.

Pasmo is a multiplatform Z80 cross-assembler, easy to compile and easy to use. It can generate object code in several formats suitable for many Z80 machines and emulators.  
Pasmo generates fixed position code, can not be used to create relocatable object files for use with linkers.

Pasmo is compatible with the syntax used in several old assemblers, by supporting several styles of numeric and string literals and by providing several names of the most used directives.  
However, in Pasmo the Z80 mnemonics, register and flags names and directives are reserved words, this may require changes of symbol names conflicting in some programs.

Pasmo can also generate the 8086 equivalent to the z80 assembly code. It can create COM files for ms-dos, by using the binary generation mode, or CMD files for CP/M 86, by using [the --cmd generation mode](#codegencmd). This feature is experimental, use with care.

## Command line use.

Pasmo is invoked from command line as:

	pasmo \[options\] file.asm file.bin \[file.symbol \[file.publics\] \]

Where file.asm is the source file, file.bin is the object file to be created and optionally file.symbol is the file where the symbol table will be written and file.publics is the file for the public symbols table. Both symbol file names can be an empty string for no generation or - to write in the standard output. When the --public option is used this is handled in another way, see below.

Options can be zero or more of the following:

\-d

Show debug info during second pass of assembly.

\-1 (digit 'one')

Show debug info during both passes of assembly.

\-8

Same as --w8080

\-v

Verbose mode. Show progress information about loading of files, progress of assembly and maybe other things.

\-I (upper case i)

Add directory to the list for searching files in INCLUDE and INCBIN.

\-B

Same as --bracket

\-E

Same as --equ

\--86

Generate 8086 code instead of Z80. This feature is experimental.

\--bin

Generate the object file in raw binary format without headers.

\--hex

Generate the object file in Intel HEX format.

\--prl

Generate the object file in CP/M PRL format.

\--cmd

Generate the object file in CP/M 86 CMD format.

\--tap

Generate the object file in .tap format.

\--tzx

Generate the object file in .tzx format.

\--cdt

Generate the object file in .cdt format.

\--tapbas

Same as --tap but adding a Basic loader before the code.

\--tzxbas

Same as --txz but adding a Basic loader before the code.

\--cdtbas

Same as --cdt but adding a Basic loader before the code.

\--plus3dos

Generate the object file in PLUS3DOS format.

\--amsdos

Generate the object file in Amsdos format.

\--msx

Generate the object file in MSX format.

\--sdrel

Generate the object file in sdcc .rel format.

\--trs

Generate the object file in TRS-80 cmd format.

\--public

Only the public symbols table is generated, using the file.symbol name, file.publics must not be specified when using this option.

\--name

Name to put in the header in the formats that use it. If unspecified the object file name will be used.

\--err

Direct error messages to standard output instead of error output (except for errors in options).

\--nocase

Make identifiers case insensitive.

\--alocal

Use autolocal mode. In this mode all labels that begins with '\_' are locals. See [the chapter about labels](#sourcelabel) for details.

\--bracket

Use bracket only mode. In this mode the parenthesis are valid only in expressions, for indirections brackets must be used.

\--equ

Predefine a symbol. Predefined symbol are treated in a similar way as defineds with EQU. Some possible uses are exemplified in the black.asm example file. The syntax is: '--equ label=value' where label must be a valid label name and value a numeric constant in a format valid in pasmo syntax. The part =value is optional, if not specified the value asigned is FFFF hex.

\--w8080

Show warnings when Z80 instructions that have no equivalent in 8080 are used. Makes easy to write programs for 8080 processor using Z80 assembler syntax.

When no option for code generation is specified, --bin is used by default.

The -d option is intended to debug pasmo itself, but can also be useful to find errors in asm code. When used the information is showed in the standard output. Error messages goes to error ouptut unless the --err option is used.

## Code generation modes.

### Default mode

If none of the code generation options is specified, then --bin mode is used by default.

### \--bin mode

The --bin mode just dumps the code generated from the first position used without any header. This mode can be used for direct generation of CP/M or MSX COM files, supposed that you use a ORG 100H directive at the beginning of the code, or to generate blocks of code to be INCBINed in other programs.

### \--hex mode

The --hex mode generates code in Intel HEX format. This format can be used with the LOAD or HEXCOM CP/M utilities, can be transmitted more easily than a binary format, and is also used in some PROM programming tools.

### \--prl mode

The prl format is used in several variants of Digital Research CP/M operating system. In pasmo is supported only to create RSX files for use in CP/M Plus, use for PRL files in MP/M is not supported because I don't have a MP/M system, real or emulated, where to test it.

### \--cmd mode

The --cmd option generates a CP/M 86 CMD mode, using the 8080 memory model of CP/M 86. Used in conjuction with the --86 option can easily generate CP/M 86 executables from CP/M 80 sources with minimal changes.

### \--tap mode

The --tap options generates a tap file with a code block, with the loading position set to the beginnig of the code so you can load it from Basic with a **LOAD "" CODE** instruction.

### \--tzx mode

Same as [\--tap](#codegentap) but using tzx format instead of tap.

### \--cdt mode

The --cdt options generates a cdt file with a code block, with the loading position set to the beginning of the code and the start address to the start point specified in the source, if any, so you can use **RUN ""** to execute it or **LOAD ""** to load it.

### \--tapbas mode

With the --tapbas option a tap file is generated with two parts: a Basic loader and a code block with the object code. The Basic loader does a CLEAR before the initial address of the code, loads the code, and executes it if a entry point is defined (see the [END](#dirend) directive). That way you can directly launch the code in a emulator, or transfer it to a tape for use in a real Spectrum.

### \--tzxbas mode

Same as [\--tapbas](#codegentapbas) but using tzx format instead of tap.

### \--cdtbas mode

Same as [\--tapbas](#codegentapbas) but using cdt format instead of tap and with a Locomotive Basic loader instead of Spectrum Basic.

### \--plus3dos mode

Generate the object file in plus3dos format, used by the Spectrum +3 disks. The file can be loaded from Basic with a **LOAD "filename" CODE** instruction.

### \--amsdos mode

Generate the object file with Amsdos header, used by the Amstrad CPC on disk files. The file generated can be loaded from Basic with **LOAD "filename", address** or executed with **RUN "filename"** if an entry point has been specified in the source (see the [END](#dirend) directive).

### \--msx mode

Generate the object file with header for use with BLOAD in MSX Basic.

### \--sdrel mode

The --sdrel option generates a .rel file for use with the sdcc linker. Under testing, use carefully.

### \--tzx mode

The --trs option generates a TRS-80 cmd file. Under testing, use carefully.

### Symbol table

The symbol table generated contains all identifiers used in the program, with the locals represented as a 8 digit hexadecimal number in order of use, unless the --public option is used. In that case only the symbols specified in PUBLIC directives are listed.

The symbol table format is a list of EQU directives. That way you can INCLUDE it in another source to create programs composed of several blocks.

## Source code format.

### Generalities.

Source code files must be valid text files in the platform used. The use of, for example, unix text files under pasmo in windows, is unsupported and the result is undefined (may depend of the compiler used to build pasmo, for example). The result of the use of a file that contains vertical tab or form feed characters is also undefined.

Everything after a ; in a line is a comment (unlees the ; is part of a string literal, of course). There are no multiline comments, you can use IF 0 .... ENDIF instead (but see [INCLUDE](#dirinclude)).

String literals are written to the object file without any character set translation. Then the use of any character with a different meaning in the platform were pasmo is running and the destination machine must be avoided, and the code of the character may be used instead. That also means that using Pasmo in any machine that uses a non ascii compatible character set may be difficult, and that a source written in utf-8 may give undesired results. This may be changed in future versions of Pasmo.

A line may begin with a decimal number followed by blanks. This number is ignored by the assembler, is allowed for compatibility with old assemblers. The line number reported in errors is the sequential number of the line in the file, not this.

Blanks are significative only in string literals and when they separate lexical elements. Any number of blanks has the same meaning as one. A blank between operators and operands is allowed but no required except when the same character has other meaning as prefix ('$' and '%', for example).

### Literals.

#### Numeric literals.

Numeric literals can be written in decimal, binary, octal and hexadecimal formats. Several formats are accepted to obtain compatibility with the source format of several assemblers.

A literal that begins with $ is a hexadecimal constant, except if the literal is only the $ symbol, in that case is an operator, see below.

A literal that begins with # is a hexadecimal constant, except if there are two consecitives #, see the ## operator.

A literal that begins with & can be hexadecimal, octal or binary constant, depending of the character that follows the &: H means hexadecimal, O octal and X hexadecimal, if none of this the caracter must be a valid hexadecimal digit and the constant is hexadecimal.

A literal that begins with % is a binary constant, except if the literal is only the % symbol, in that case is an operator, see below.

A literal that begins with a decimal digit can be a decimal, binary, octal or hexadecimal. If the digit is 0 and the following character is an X, the number is hexadecimal. If not, the suffix of the literal is examined: D means decimal, B binary, H hexadcimal and O or Q octal, in any other case is taken as decimal. Take care, FFFFh for example is not an hexadecimal constant, is an identifier, to write it with the suffix notation you must do it as 0FFFFh.

All numeric formats can have $ signs between the digits to improve readability. They are ignored.

#### String literals.

There are two formats of string literals: single or double quote delimited.

A string literal delimited with single quotes is the simpler format, all characters are included in the string without any special interpretation, with the only exception that two consecutive single quotes are taken as one single quote character to be included in the string. For example: the single quote delimited string 'That''s all folks' generates the same string as the double quote delimited "That's all folks".

A string literal delimited with double quotes is interpreted in a way similar to the C and C++ languages. The \\ character is taken as escape character, with the following interpretations: n is a new line character (0A hex), r is a carriage return (0D hex), t is a tabulator (09 hex), a is a bell (07 hex), x indicates that the two next characters will be considered the hexadecimal code of a char and a char with that code is inserted, an octal digit prefixes and begins an octal number of up to three digits, and the corresponding character is inserted into the string, the characters \\ and " means to insert itself in the string, and any other char is reserved for future use.

A string literal of length 1 can be used as a numeric constant with the numeric value of the character contained. This allows expressions such as 'A' + 80h to be evaluated as expected.

### Identifiers.

Identifiers are the names used for labels, EQU and DEFL symbols and macro names and parameters. The names of the Z80 mnemonics, registers and flag names, and of pasmo operands and assemble directives are reserved and can not be used as names of identifiers. Reserved names are case insensitive, even if case sensitive mode is used.

In the following 'letter' means an english letter character in upper or lower case. Characters that correspond to letters in other languages are not allowed in identifiers.

Identifiers begins with a letter, '\_', '?', '@' or '.', followed for zero or more letter, decimal digit, '\_', '?', '@', '.' or '$'. The '$' are ignored, but a reserved word with a '$' embedded or appended is not recognized as such.

Identifiers that begins with '\_' are special when using autolocal mode, see the --alocal option and [the chapter about labels](#sourcelabel) for details.

Identifiers are case sensitive if the option --nocase is not used. When using --nocase, they are always converted to upper case.

### File names.

File names are used in the INCLUDE and INCBIN directives. They follow special rules.

A file name that begins with a double quote character must end with another double quote, and the file name contains all character between them without any special interpretation.

A file name that begins with a single quote character must end with another single quote, and the file name contains all character between them without any special interpretation.

In any other case all characteres until the next blank or the end of line are considered part of the file name. Blank characters are space and tab.

### Labels.

A label can be placed at the beginning of any line, before any assembler mnemonic or directive. Optionally can be followed by a ':', but is not recommended to use it in directives, for compatibility with other assemblers. A line that has a label with no mnemonic nor directive is also valid.

The label has special meaning in the MACRO, EQU and DEFL directives, in any other case the value of the current code generation position is assigned to the label.

Labels can be used before his definition, but the result of doing this with labels assigned with DEFL is undefined.

The value of a label cannot be changed unless DEFL is used in all assignments of that label. If the value assigned to a label is different in the two passes of the assembly the program is illegal, but is not guaranteed that an error is generated. However, is legal to assign a value undefined in the first pass (by using an expression that contains a label not yet defined, for example).

In the default mode a label is global unless declared as LOCAL into a MACRO, REPT or IRP block, see the [LOCAL](#dirlocal) directive for details.

In the autolocal mode, introduced by using the --alocal command line option, all labels that begins with a '\_' are locals. His ambit ends at the next non local label or in the next PROC, LOCAL, MACRO, ENDP or ENDM directive.

Both automatic and explicit local labels are represented in the symbol table listing as 8 digit hexadecimal numbers, corresponding to the first use of the label in the source.

## Directives.

List of directives supported in Pasmo, in alphabetical order.

.ERROR

Generates an error during assembly if the line is actively used, that is, in a macro if it gets expanded, in an IF if the current branch is taken. All text following the directive is used as error message.

.SHIFT

Shift MACRO arguments, see [the chapter about macros](#macros).

.WARNING

Same as [.ERROR](#direrror) but emiting a a warning message instead of generating an error.

DB

Define Byte. The argument is a comma separated list of string literals or numeric expressions. The string literals are inserted in the object code, and the result of the numeric expression is inserted as a single byte, truncating it if needed.

DEFB

DEFine Byte, same as [DB](#dirdb).

DEFL

DEFine Label. Must be preced by a label. The argument must be a numeric expression, the result is assigned to the label. The label used can be redefined with other DEFL directive.

DEFM

DEFine Message, same as [DB](#dirdb).

DEFS

DEFine Space, same as [DS](#dirds).

DEFW

Same as [DW](#dirdw).

DS

Define Space. Take one or two comma separated arguments. The first or only argument is the amount of space to define, in bytes. The second is the value used to fill the space, if absent 0 will be used.

DW

Define Word. The argument is a comma separated list of numeric expressions. Each numeric expression is evaluated as a two byte word and the result inserted in the code in the Z80 word format.

ELSE

See [IF](#dirif).

END

Ends the assembly. All lines after this directive are ignored. If it has an argument is evaluated as a numeric expression and the result is set as the program entry point. The result of setting an entry point depends of the type of code generation used, may be none but even in this case may be used for documentation purposes.

ENDIF

See [IF](#dirif).

ENDM

Ends a macro, see [the chapter about macros](#macros).

ENDP

Marks the end of a PROC block, see PROC.

EQU

EQUate. Must be preceded by a label. The argument must be a numeric expression, the result is assigned to the label. The label used can't be redefined.

EXITM

Exits a macro, see [the chapter about macros](#macros).

IF

Contional assembly. The argument must be a numeric expression, a result of 0 is considered as false, any other as true. If the argument is true the following code is assembled until the end of the IF section or an ELSE directive is encountered, else is ignored. If the ELSE direcive is present the following code is ignored if the argument was true, or is assembled if was false.  
The IF section is ended with a ENDIF or a ENDM directive (in the last case the ENDM has also his usual effect).  
IF can be nested, in that case each ELSE and ENDIF takes effect only on his corresponding IF, but ENDM ends all pending IF sections.

IFDEF

IFDEF symbol is a shortcut for IF DEFINED symbol.

IFNDEF

IFNDEF symbol is a shortcut for IF ! DEFINED symbol.

INCLUDE

Include a file. See [the file names chapter](#sourcefilename) for the conventions used in the argument. The file is readed and the result is the same as if the file were copied in the current file instead of the INCLUDE line.  
The file included may contain INCLUDE directives, and so on.  
INCLUDE directives are processed before the assembly phases, so the use of IF directives to conditionally include different files is not allowed.

INCBIN

INClude BINary. Include a binary file. Reads a binary file and insert his content in the generated code at the current position. See [the file names chapter](#sourcefilename) for the conventions used in the argument.

IRP

Repeat a block of code substituing arguments. See [the chapter about macros](#macros).

LOCAL

Marks identifiers as local to the current block. The block may be a MACRO, REPT, IRP or PROC directive, the local ambit ends in the corresponding ENDM or ENDP directive. The ambit begins at the LOCAL directive, not at the beginning of the block, take care with that.  
If several LOCAL declations of the same identifier are used in the same block, only the first has effect, the others are ignored.

MACRO

Defines a macro, see [the chapter about macros](#macros).

ORG

ORiGin. Establishes the origin position where to place generated code. Several ORG directives can be used in the same program, but if the result is that code generated overwrites previous, the result is undefined.

PROC

Marks the begin of a PROC block. The only effect is to define an ambit for LOCAL directives. The block ends with a corresponding ENDP directive. The recommended use is to enclose a subroutine in a PROC block, but can also be used in any other situation.

PUBLIC

The argument is a comma separated list of identifiers. Each identifier is marked as public. When using the --public command line option only the identifiers marked as public are included in the symbol table listing.

REPT

REPeaTs a block. See [the chapter about macros](#macros).

## Operators.

### Generalities.

All numeric values are taken as 16 bits unsigned, using 2 complement or trucating when required. Logical operators return FFFF hex for true and 0 for false, in the arguments 0 is false and any other value true.

Parenthesis may be used to group parts of expressions. They are also used to express indirections in the z80 instructions that allows or require it. This can cause some errors when a parenthesized expression is used in a place were an indirections is allowed. Pasmo uses some heuristic to allow the expression to be correctly interpreted, but are far from perfect.

Using the bracket only mode the parenthesis have the unique meaning of grouping expressions, brackets are required for indirections, thus solving ambiguities.

Short circuit evaluation: the && and || operators and the conditional expression are short circuited. This means that if one of his operators need not be evaluted, it can include undefined symbols or divisions by 0 without generating an error (but still must have correct syntax). In the conditional expression this applies to the branch not taken, in the && operator to the second operand if the first is false, and in the || operator to the second operand if the first is true.

### Table of precedence.

Table of operators by order of precedence, those in the same line have the same precedence:

	## (see note)
	$, NUL, DEFINED
	\*, /, MOD, %, SHL, SHR, <<, >>
	+, - (binary)
	EQ, NE, LT, LE, GT, GE, =, !=, <, >, <=, >=
	NOT, ~, !, +, - (unary)
	AND, &
	OR, |, XOR
	&&
	||
	HIGH, LOW
	?

The ## operator is an special case, is processed during the macro expansion, see [the chapter about macros](#macros).

### Alphabetic list of operators.

!

Logical not. Returns true if his argument is 0, false otherwise.

!=

Same as NE.

##

Identifier pasting operator, see [the chapter about macros](#macros).

$

Gives the value of the position counter at the begin of the current sentence. For example, in a DW directive it gives the position of the first item in the list, not the current item.

%

Same as MOD.

&

Same as AND.

&&

Logical and. True if both operands are true.

\*

Multiplication.

+

Addition or unary +.

\-

Substraction or unary -.

/

Integer division, truncated.

<

Same as LT

<<

Same as SHL

<=

Same as LE

\=

Same as EQ

\>

Same as GT

\>=

Same as GE

\>>

Same as SHR

?

Condtional expression. Must be followed by two expressions separated by a :, if the expression on the right of ? is true, the first expressions is evaluted, if false, the second.

|

Same as OR.

||

Logical or. True if one of his operands is true.

~

Same as NOT

AND

Bitwise and operator.

DEFINED

The argument must be a identifier. The result is true if the identifier is defined, false otherwise.

EQ

Equals. True if both operands are equal, false otherwise.

GE

Greater or equal. True if the left operand is greater or equal than the right.

GT

Greater than. True if the left operand is greater than the right.

HIGH

Returns the high order byte of the argument.

LE

Less or equal. True if the left operand is lesser or equal than the right.

LOW

Returns the low order byte of the argument.

LT

Less than. True if the lefth operand is lesser than the right.

MOD

Modulus. The remainder of the integer division.

NE

Not equal. False if both operands are equal, true otherwise.

NOT

Bitwise not. Return the ones complement of his operand.

NUL

Returns true if there is something at his right, false in other case. Useful if the arguments are parameters of macros.

OR

Bitwise or operator.

SHL

Shif left. Returns the left operand shifted to the left the number of bits specified in the right operand, filling with zeroes.

SHR

Shif right. Returns the left operand shifted to the right the number of bits specified in the right operand, filling with zeroes.

XOR

Bitwise xor (exclusive or) operator.

## Macros.

### Generalities.

There are two types of macro directives: the proper MACRO directive and the repetition directives REPT and IRP. In addition the ENDM and EXITM directives controls the end of the macro expansion.

A macro parameter is an indentifier that when the macro is expanded is substitued by the value of the argument applied. The argument can be empty, or be composed by one or more tokens. If a MACRO is defined inside another macro directive the external parameters are not substitued, with the other macro directives the parameter substitution is done beginnig by the most external directive. The NUL operator can be used to check if an argument is not empty. The .SHIFT directive can be used to work with an undeterminated number of arguments.

Identifier pasting: inside a MACRO the operator ## can be used to join two idenfiers resulting in another identifier. This is intended to allow the creation of identifiers dependent of macro arguments.

### Directives.

.SHIFT

Can be used only inside a MACRO. The MACRO arguments are shitted one place to the left, the first argument is discarded. If there are not enough arguments to fill the parameter list after the shift, the remaining arguments get undefined.

ENDM

Marks the end of the current MACRO definition, or the current REPT or IRP block. All IF blocks contained in the macro block are also closed.

EXITM

Exits the curren MACRO, REPT or IRP block. In the case of MACRO, the macro expansion is finished, in the other cases the code generation of the block is terminated and the assembly continues after the corresponding ENDM.

IRP

	IRP parameter, argument list.

Repeats the block of code between the IRP directive and his corresponding ENDM one time for each of the arguments.

MACRO

Defines a macro. There are two forms that can be used:

	name	MACRO \[ list of parameters\]

or:

	MACRO name \[ , list of parameters\]

In all cases, list of paramenters is a comma separated list of identifiers, and name is the name assigned to the macro created.  
A macro is used by simply specifying his name, and optionally a list of arguments. The arguments list does not need to have the same length as the parameter list of the macro. If it is longer, the extra arguments are not used, but can be retrieved by using .SHIFT inside the MACRO. If it is shorter some parameters get undefined, this can be tested inside the MACRO by using the NUL operator.

REPT

Repeats the block of code between the REPT directive and his corresponding ENDM the number of times specified in his argument. The argument can be 0, in that case the block is skipped.  
Additionally a loop var can be specified. This var is not a macro parameter, is used as a LOCAL DEFL symbol, whose value is incremented in every loop iteration. The initial value and incement can be specified, with defaults of 0 and 1 respectively.

## About suggestions and possible improvements.

The assumption of Pasmo if that, being a cross-assembler, it will be used on a machine with many available resources. Then I do not make any effort to provide means to do things that can be easily made with other utilities, unless I think (or other people convince me) that including it in Pasmo can be much more convenient.  
For example, if you want to create a sin table you can write a program in your favourite language that writes a file with the table and INCLUDE that file, and if you want to automate that type of things you can use make.

Taken that into account, I am open to suggestions to improve Pasmo and to patches that implements it. In the later case please take care to write things in a portable way, without operating system or compiler dependences.

### Why Pasmo can not generate linkable code?

Pasmo has a simple code generator that uses absolute address of memory. That will make difficult to adapt it to generate relocatable code for use with linkers. I don't have plans to do it for the moment, maybe someone want to contribute?

### Game Boy.

Some people suggested to add support for Game Boy programming. There are two problems, the simplified way used to generate code in Pasmo, and my inexistent knowledge of the Game Boy.

### Thanks.

Thanks to all people that has made suggestions and notified or corrected bugs. And to these that show me the beautiful things they do with Pasmo.

## Tricks.

You can use Pasmo to convert any binary file to .tap, just write a tiny program called for example convert.asm:

	ORG address\_to\_load\_the\_file
	INCBIN file.bin

Assemble it with: pasmo --tap convert.asm file.tap, and you have it. The same may be done for the other formats supported.

## Bugs.

Pasmo emits a warning when using a expression that looks line a non existent z80 instruction, such as 'ld b, (nn)', but the simplified way used to detect that also warns in cases like 'ld b,(i1+i2)\*(i3+i4)'.  
A way to avoid the warning in that case is to prefix the expression with parenthesis with '+' or '0 +'.  
Using the bracket only mode the problem does not exist, in that case the parenthesis are always taken as expresssions (and the programmer is supposed to know that), thus the warning is not emitted.  
More suggestions about that are wellcome.

There is no way to include a file whose name contains blanks, single and double quoutes. Someone use file names like that?

## Epilogue.

That's all folks!

Send comments and criticisms to:

[julian.notfound@gmail.com](mailto:julian.notfound@gmail.com)
