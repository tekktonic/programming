use strict;
use warnings;
use Archive::Peek::Tar;

sub PreInst
{
    my $pkg = shift;
    my $peek = Archive::Peek::Tar->new(filename => ($pkg =~ s/\.tgz//) . ".tgz");
    system($peek->file("META/pre.sh"));
}

sub PostInst
{
    my $pkg = shift;
    system($pkg . "/META/post.sh");
}
