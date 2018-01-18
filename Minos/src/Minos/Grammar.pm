#=begin overview

This is the grammar for Minos in Perl 6 rules.

#=end overview

grammar Minos::Grammar is HLL::Grammar;

token TOP {
    <statement_list>
    [ $ || <.panic: "Syntax error"> ]
}

## Lexer items

# This <ws> rule treats # as "comment to eol".
token ws {
    <!ww>
    [ '#' \N* \n? | \s+ ]*
}

## Statements

rule statement
{
    <assignment>
}

rule statement_list
{
    <stat_or_def>*
}

rule stat_or_def
{
    <statement>
}

rule assignment
{
    <primary> 'is' <EXPR>
}

rule primary
{
    <identifier>
}


## Terms

token identifier
{
    <!keyword> <ident>
}

token keyword
{
    ['&' | '?' | 'for' | 'or' | '!' | 'fn' | 'let' | '{' | '}' ]
token term:sym<int> { <int> }
token term:sym<string> { <string> }

#proto token quote { <...> }
#token quote:sym<'> { <?[']> <quote_EXPR: ':q'> }
#token quote:sym<"> { <?["]> <quote_EXPR: ':qq'> }

## Operators

INIT {
    Minos::Grammar.O(':prec<u>, :assoc<left>',  '%multiplicative');
    Minos::Grammar.O(':prec<t>, :assoc<left>',  '%additive');
}

token circumfix:sym<( )> { '(' <.ws> <EXPR> ')' }

token infix:sym<*>  { <sym> <O('%multiplicative, :pirop<mul>')> }
token infix:sym</>  { <sym> <O('%multiplicative, :pirop<div>')> }

token infix:sym<+>  { <sym> <O('%additive, :pirop<add>')> }
token infix:sym<->  { <sym> <O('%additive, :pirop<sub>')> }
