use strict;
use warnings;
use Data::Dumper;
use Text::ParseWords;

use feature ":5.10";

my @stack;

my %lookup;

$lookup{"swap"} = 
    sub { my $a = pop(@stack); my $b = pop(@stack); push(@stack, $b); push(@stack, $a);};

$lookup{"+"} = 
    sub { my $a = pop(@stack); my $b = pop(@stack); push(@stack, $a + $b);};

$lookup{"-"} = 
    sub { my $a = pop(@stack); my $b = pop(@stack); push(@stack, $a - $b);};

$lookup{"*"} = 
    sub { my $a = pop(@stack); my $b = pop(@stack); push(@stack, $a * $b);};

$lookup{"/"} = 
    sub { my $a = pop(@stack); my $b = pop(@stack); push(@stack, $a / $b);};

$lookup{"print"} =
    sub { print(pop(@stack . "\n"))};

$lookup{"clear"} =
    sub { @stack = (); };

$lookup{"def"} =
    sub {
	my $name = pop(@stack);
	my $value = pop(@stack);
	$lookup{$name} = sub { push(@stack, $value) };
};

$lookup{"fn"} =
    sub {
	my $name = pop(@stack);
	my $value = pop(@stack);
	$lookup{$name} = sub { push(@stack, $value); $lookup{"eval"}->(); };
};

$lookup{"dump"} =
    sub {foreach my $obj (@stack) { print("$obj\n"); }};

$lookup{"eval"} =
    sub {my $code = $1 if (pop(@stack) =~ m/'(.*)'/);
	 langeval("$code\n")};

#$lookup{"ffi"} =
 #   sub {
#	my $perl = $1 if (pop(@stack) =~ m/"(.*)"/);
#	push(@stack, eval($perl));};


#$lookup{"pop"} =
#    sub {
#	push(@stack, eval($perl));};

#$lookup{"push"} =

sub tokenize
{
    my ($line) = @_;
    my @tokens = quotewords('\s+', 1, $line);
    my @ret;

    pop(@tokens); # quotewords appends an undef
    while (my $token = shift(@tokens))
    {
	if ($tokens[0] && ($tokens[0] eq "def" || $tokens[0] eq "fn")) # definition
	{
	    push(@ret, {$token => "def"});
	    push(@stack, $token);
	}
	elsif ($lookup{$token}) # variable or function
	{
	    push(@ret, {$token => "var"});
	    ($lookup{$token})->();
	}
	elsif ($token =~ /\d+|\d+\.\d+|".*"|'.*'/) #literal
	{
	    push(@ret, {$token => "lit"});
	    push(@stack, $token);
	}

	else
	{
	    print("Syntax error! $token invalid\n");
	    exit(1);
	}
    }

    return \@ret;
}

sub langeval
{
    my ($line) = @_;
    my @tokens = tokenize($line);

    for (my %token = %{pop(@tokens)}; %token;)
    {
	print(%token . "\n");
	my $name = shift(keys(%token));
	my $type = shift(values(%token));
	given ($type)
	{
	    when ("def")
	    {
		push(@stack, $name);
	    }
	    when ("var")
	    {
		$lookup{$name}->();
	    }
	    when ("lit")
	    {
		push(@stack, $name);
	    }
	}
    }
}

my $line;
do
{
    print("? ");
    $line = <>;
    langeval($line);
} while ($line ne "quit\n")
