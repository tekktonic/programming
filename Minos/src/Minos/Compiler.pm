class Minos::Compiler is HLL::Compiler;

INIT {
    Minos::Compiler.language('Minos');
    Minos::Compiler.parsegrammar(Minos::Grammar);
    Minos::Compiler.parseactions(Minos::Actions);

    Minos::Compiler.commandline_banner("Minos 0.0000000000001\n");
    Minos::Compiler.commandline_prompt("3:(:)");
}
