// pasmo.cxx

#include "asm.h"
#include "asmerror.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::cerr;

namespace
{

using std::string;
using std::vector;
using std::runtime_error;

// Define the version of Pasmo (assembler)
const string pasmoversion(VERSION);

// Empty class for usage (help) message
class Usage { };

// Exception for when an option requires an argument
class NeedArgument : public runtime_error
{
public:
    NeedArgument(const string & option) :
        runtime_error("Option " + option + " requires argument")
    { }
};

// Exception for invalid options
class InvalidOption : public runtime_error
{
public:
    InvalidOption(const string & option) :
        runtime_error("Invalid option: " + option)
    { }
};

// Stream for standard error output
std::ostream * perr = & cerr;

// Command-line option definitions
const string opt1("-1");
const string opt8("-8");
const string optd("-d");
const string optv("-v");
const string optB("-B");
const string optE("-E");
const string optI("-I");

const string opt86("--86");
const string optalocal("--alocal");
const string optamsdos("--amsdos");
const string optbin("--bin");
const string optbracket("--bracket");
const string optcdt("--cdt");
const string optcdtbas("--cdtbas");
const string optcmd("--cmd");
const string optequ("--equ");
const string opterr("--err");
const string opthex("--hex");
const string optmsx("--msx");
const string optname("--name");
const string optnocase("--nocase");
const string optpass3("--pass3");
const string optplus3dos("--plus3dos");
const string optprl("--prl");
const string optpublic("--public");
const string optsdrel("--sdrel");
const string opttap("--tap");
const string opttapbas("--tapbas");
const string opttrs("--trs");
const string opttzx("--tzx");
const string opttzxbas("--tzxbas");
const string optw8080("--w8080");
const string optwerror("--werror");
const string opthelp("--help");
const string optshorthelp("-h");

class Options
{
public:
    Options(int argc, char * * argv);

    typedef void(Asm::* emitfunc_t) (std::ostream &);

    emitfunc_t getemit() const { return emitfunc; }
    bool redirerr() const { return redirecterr; }
    bool publiconly() const { return emitpublic; }
    bool getpass3() const { return pass3; }
    string getfilein() const { return filein; }
    string getfileout() const { return fileout; }
    string getfilesymbol() const { return filesymbol; }
    string getfilepublic() const;
    string getheadername() const { return headername; }
    void apply(Asm & assembler) const;
    void showHelp() const;
private:
    emitfunc_t emitfunc;
    static const emitfunc_t emitdefault;

    bool verbose;
    bool emitpublic;
    Asm::DebugType debugtype;
    bool redirecterr;
    bool nocase;
    bool autolocal;
    bool bracketonly;
    bool warn8080;
    bool mode86;
    bool werror;
    bool pass3;

    vector <string> includedir;
    vector <string> labelpredef;

    string filein;
    string fileout;
    string filesymbol;
    string filepublic;
    string headername;
};

// Definição da função de emissão padrão
const Options::emitfunc_t Options::emitdefault(& Asm::emitobject);

Options::Options(int argc, char * * argv) :
    emitfunc(emitdefault),
    verbose(false),
    emitpublic(false),
    debugtype(Asm::NoDebug),
    redirecterr(false),
    nocase(false),
    autolocal(false),
    bracketonly(false),
    warn8080(false),
    mode86(false),
    werror(false),
    pass3(false)
{
    int argpos;
    for (argpos = 1; argpos < argc; ++argpos)
    {
        const string arg(argv[argpos]);
        if (arg == optbin)
            emitfunc = &Asm::emitobject;
        else if (arg == opthex)
            emitfunc = &Asm::emithex;
        else if (arg == optprl)
            emitfunc = &Asm::emitprl;
        else if (arg == optcmd)
            emitfunc = &Asm::emitcmd;
        else if (arg == optsdrel)
            emitfunc = &Asm::emitsdrel;
        else if (arg == optpass3)
            pass3 = true;
        else if (arg == optplus3dos)
            emitfunc = &Asm::emitplus3dos;
        else if (arg == opttap)
            emitfunc = &Asm::emittap;
        else if (arg == opttrs)
            emitfunc = &Asm::emittrs;
        else if (arg == opttzx)
            emitfunc = &Asm::emittzx;
        else if (arg == optcdt)
            emitfunc = &Asm::emitcdt;
        else if (arg == opttapbas)
            emitfunc = &Asm::emittapbas;
        else if (arg == opttzxbas)
            emitfunc = &Asm::emittzxbas;
        else if (arg == optcdtbas)
            emitfunc = &Asm::emitcdtbas;
        else if (arg == optamsdos)
            emitfunc = &Asm::emitamsdos;
        else if (arg == optmsx)
            emitfunc = &Asm::emitmsx;
        else if (arg == optpublic)
            emitpublic = true;
        else if (arg == optname)
        {
            ++argpos;
            if (argpos >= argc)
                throw NeedArgument(optname);
            headername = argv[argpos];
        }
        else if (arg == optv)
            verbose = true;
        else if (arg == optd)
            debugtype = Asm::DebugSecondPass;
        else if (arg == opt1)
            debugtype = Asm::DebugAll;
        else if (arg == opterr)
            redirecterr = true;
        else if (arg == optnocase)
            nocase = true;
        else if (arg == optalocal)
            autolocal = true;
        else if (arg == optB || arg == optbracket)
            bracketonly = true;
        else if (arg == opt8 || arg == optw8080)
            warn8080 = true;
        else if (arg == opt86)
            mode86 = true;
        else if (arg == optwerror)
            werror = true;
        else if (arg == opthelp || arg == optshorthelp)
        {
            showHelp();
        }
        else if (arg == optI)
        {
            ++argpos;
            if (argpos >= argc)
                throw NeedArgument(optI);
            includedir.push_back(argv[argpos]);
        }
        else if (arg == optE || arg == optequ)
        {
            ++argpos;
            if (argpos >= argc)
                throw NeedArgument(arg);
            labelpredef.push_back(argv[argpos]);
        }
        else if (arg == "--")
        {
            ++argpos;
            break;
        }
        else if (arg.substr(0, 1) == "-")
            throw InvalidOption(arg);
        else
            break;
    }

    // File parameters.

    if (argpos >= argc)
        throw Usage();
    filein = argv[argpos];
    ++argpos;
    if (argpos >= argc)
        throw Usage();

    fileout = argv[argpos];
    ++argpos;

    if (argpos < argc)
    {
        filesymbol = argv[argpos];
        ++argpos;

        if (!emitpublic && argpos < argc)
        {
            filepublic = argv[argpos];
            ++argpos;
        }

        if (argpos < argc)
            cerr << "WARNING: Extra arguments ignored\n";
    }

    if (headername.empty())
        headername = fileout;
}

string Options::getfilepublic() const
{
    return emitpublic ? filesymbol : filepublic;
}

void Options::apply(Asm & assembler) const
{
    assembler.setdebugtype(debugtype);

    if (verbose)
        assembler.verbose();
    if (redirecterr)
        assembler.errtostdout();
    if (nocase)
        assembler.caseinsensitive();
    if (autolocal)
        assembler.autolocal();
    if (bracketonly)
        assembler.bracketonly();
    if (warn8080)
        assembler.warn8080();
    if (mode86)
        assembler.set86();
    if (werror)
        assembler.setwerror();
    if (pass3)
        assembler.setpass3();

    for (const auto& dir : includedir)
        assembler.addincludedir(dir);

    for (const auto& label : labelpredef)
        assembler.addpredef(label);

    assembler.setheadername(headername);
}

void Options::showHelp() const
{
    cerr << "Pasmo v." << pasmoversion
         << " (C) 2004-2021 Julian Albo\n"
         << "Usage:\n"
         << "\tpasmo [options] source object [symbol]\n\n"
         << "Options:\n"
         << "General options:\n"
         << "\t-h, --help\tShow this help message\n"
         << "\t-d\t\tShow debug information during assembly\n"
         << "\t-1\t\tShow debug information also on the first pass\n"
         << "\t-v\t\tVerbose mode. Displays progress during assembly\n"
         << "\t-B\t\tBracket-only mode: parentheses are reserved for expressions\n"
         << "\t-I <dir>\tAdd a directory to the search path for `INCLUDE` and `INCBIN`\n"
         << "\t--nocase\tMake identifiers case-insensitive\n"
         << "\t--err\t\tDirect error messages to standard output instead of standard error\n"
         << "\t--name <name>\tSet the header name (default is the file name)\n"
         << "\t--public\tInclude only public symbols in the symbol table listing\n\n"
         << "File output options:\n"
         << "\t--bin\t\tGenerate the object file in pure binary format (without header)\n"
         << "\t--hex\t\tGenerate the object file in Intel HEX format\n"
         << "\t--prl\t\tGenerate the object file in PRL format (CP/M Plus RSX)\n"
         << "\t--cmd\t\tGenerate the object file in CMD format (CP/M 86)\n"
         << "\t--msx\t\tGenerate the object file for MSX Basic with a `BLOAD` header\n"
         << "\t--tap\t\tGenerate a `.tap` file for Spectrum emulators (tape image)\n"
         << "\t--tzx\t\tGenerate a `.tzx` file for Spectrum emulators (tape image)\n"
         << "\t--cdt\t\tGenerate a `.cdt` file for Amstrad CPC emulators (tape image)\n"
         << "\t--amsdos\tGenerate the object file with an Amsdos header (Amstrad CPC disk)\n"
         << "\t--plus3dos\tGenerate the object file with a PLUS3DOS header (Spectrum disk)\n"
         << "\t--tapbas\tSame as `--tap`, but adds a Basic loader\n"
         << "\t--tzxbas\tSame as `--tzx`, but adds a Basic loader\n"
         << "\t--cdtbas\tSame as `--cdt`, but adds a Basic loader\n\n"
         << "Additional options:\n"
         << "\t--werror\tTreat warnings as errors\n"
         << "\t--alocal\tAutolocal mode: labels starting with `_` are local, ending at the next global label\n"
         << "\t--sdrel\t\tGenerate object files in SDCC linker `.rel` format\n"
         << "\t--trs\t\tGenerate object files in TRS-80 CMD format\n"
         << "\t--w8080\t\tDisplay a warning when using Z80 instructions that don't exist in 8080\n"
         << "\t--86\t\tGenerate 8086 code\n";
    exit(0);
}

int doit(Asm & assembler, int argc, char * * argv)
{
    // Process command line options.

    Options option(argc, argv);

    if (option.redirerr())
        perr = &cout;

    option.apply(assembler);

    assembler.loadfile(option.getfilein());
    assembler.processfile();

    // Generate ouptut file.

    std::ofstream out(option.getfileout().c_str(),
        std::ios::out | std::ios::binary);
    if (! out.is_open() )
        throw runtime_error("Error creating object file");


    (assembler.* option.getemit() ) (out);

    out.close();

    // Generate symbol table and public symbol table if required.

    string filesymbol = option.getfilesymbol();
    if (! option.publiconly() && ! filesymbol.empty() )
    {
        std::ofstream sout;
        std::streambuf * cout_buf = 0;
        if (filesymbol != "-")
        {
            sout.open(filesymbol.c_str() );
            if (! sout.is_open() )
                throw runtime_error("Error creating symbols file");
            cout_buf = cout.rdbuf();
            cout.rdbuf(sout.rdbuf() );
        }
        assembler.dumpsymbol(cout);
        if (cout_buf)
        {
            cout.rdbuf(cout_buf);
            sout.close();
        }
    }

    const string filepublic = option.getfilepublic();
    if (! filepublic.empty() )
    {
        std::ofstream sout;
        std::streambuf * cout_buf = 0;
        if (filepublic != "-")
        {
            sout.open(filepublic.c_str() );
            if (! sout.is_open() )
                throw runtime_error("Error creating public symbols file");
            cout_buf = cout.rdbuf();
            cout.rdbuf(sout.rdbuf() );
        }
        assembler.dumppublic(cout);
        if (cout_buf)
        {
            cout.rdbuf(cout_buf);
            sout.close();
        }
    }

    return 0;
}


} // namespace

int main(int argc, char **argv)
{
    Asm assembler;

    // Calls 'doit' and handles possible errors
    try
    {
        return doit(assembler, argc, argv);
    }
    catch (AsmError &err)
    {
        // Handles specific AsmError
        assembler.showerrorinfo(*perr, err.getline(), err.message());
    }
    catch (std::logic_error &e)
    {
        // Handles logical errors
        *perr << "ERROR: " << e.what() << '\n'
              << "This error is unexpected, please send a bug report.\n";
    }
    catch (std::exception &e)
    {
        // Handles general std::exception
        *perr << "ERROR: " << e.what() << '\n';
    }
    catch (Usage &)
    {
        // Displays usage message
        cerr << "Pasmo v." << pasmoversion
             << " (C) 2004-2021 Julian Albo\n"
             << "Usage:\n"
             << "\tpasmo [options] source object [symbol]\n\n"
             << "For more details, use -h or --help.\n";
    }
    catch (ErrorAlreadyReported)
    {
        // Ignores the ErrorAlreadyReported exception
    }
    catch (...)
    {
        // Handles any unexpected exception
        cerr << "ERROR: Unexpected exception.\n"
             << "Please send a bug report.\n";
    }

    // Returns 1 to indicate failure
    return 1;
}

// End
