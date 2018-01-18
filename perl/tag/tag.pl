use strict;
use warnings;
use autodie;
use v5.18;
use Data::Dumper;
use File::Copy;
use File::Basename;
use Cwd;

sub create_tags ($) {
    my $file = shift;
    say $file;
    my @tags;
    if (-e $file)
    {
	say "displaying $file";
	`qiv -z "$file"`;
	say "tag whatever you see";
	@tags = split(' ', <STDIN>);
    }

    my $filename = (fileparse($file))[0];
    say $filename;
    move($file, ".ttags/" . $filename);

    my $tagfile = ".ttags/" . $filename . ".tags";
   say("FILE  $tagfile");
    for my $tag (@tags)
    {
	if ($tag eq "delete")
	{
	    unlink(".ttags/$filename");
	    return;
	}
	if (! -d $tag)
	{
	    mkdir($tag);
	}
	if (! -e "$tag/$file")
	{
	    symlink(cwd() . "/.ttags/" . $file, "$tag/$file");
	}
    }
    open(my $h, ">", $tagfile,);
    print($h join(@tags, " "));
    close($h);
}


say Dumper(@ARGV);
if (shift @ARGV eq "tag")
{

    if (! -d "./.ttags")
    {
	mkdir("./.ttags");
    }

    foreach my $i (@ARGV)
    {
	say $i;
	create_tags($i);
    }
}
