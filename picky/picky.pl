use strict;
use warnings;
do 'cgi-lib.pl';


#my %env = &read_input;
my %env;
$env{'page'} = "MainPage";
if (!$env{'page'}) {$env{'page'} = "MainPage";}

if (!$env{'edit'})
{
    open(page, "<", "pages/" . $env{'page'});
    if (!<page>)
    {
	edit();
    }
    else
    {
	close(page); # make sure we start from the beginning
	open(page, "<", "pages/" . $env{'page'});
	open(view, "<", "templates/view.htm");

	local $/; #read entire file
	my $content = <page>;
	my $title = $env{'page'};
	my $out = <view>;
	$content =~ s/([A-Z].*[A-Z].*)/<a href="picky.cgi?view=$1">$1<\/a>/;
	$out =~ s/\$\{title\}/$title/g;
	$out =~ s/\$\{body\}/$content/g;
	print($out);
    }
}

sub edit
{
}
