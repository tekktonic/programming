use v5.14;
use diagnostics;
use JSON qw(from_json);
use File::Basename;

foreach my $map (@ARGV)
{
#    my %jmap = %{from_json($map)};
    say (basename($map, ".json") . ".cmap");
#    open(my $outf, fileparse($map)[0] . ".cmap");
}
