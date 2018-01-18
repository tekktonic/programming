use strict;
use warnings;
use diagnostics;
use autodie;
use v5.10;

use IO::Zlib;
use Archive::Tar;
use JSON;
use Data::Dumper;
use File::Slurp qw(slurp);

if ($> != 0) {
	say("This must be run as root!");
	exit(1);
}
my $command = shift;
if ($command eq "extract") {
	my @pkgs = @ARGV;
	foreach my $i (@pkgs) {
		my $pkgh = Archive::Tar->new($i);
		my %pkginf = json_decode($pkgh->get_content("info/pkg.json"));
		chdir("/");
		$pkgh->extract_files($pkginf{"files"});
		File::Slurp->write_file("/var/db/equator/" . $pkginf{"name"} . "-" . $pkginf{"version"} . "-" . $pkginf{"flavor"}, json_encode(%pkginf));
	}
}
elsif ($command eq "remove") {
	my @pkgs = @ARGV;
	foreach my $pkg (@pkgs) {
		my @possibilities = glob("/var/db/equator/" . $pkg . "*");
		say "$pkg " . (scalar @possibilities);
		if (scalar @possibilities < 1) {
			say("no packages listed");
		}
		elsif (scalar @possibilities > 1) {
			say("Ambiguous entry, it's one of:", @possibilities);
		} else {
			print slurp($possibilities[0]);
			my %json = %{from_json(slurp($possibilities[0]))};
			my @files = @{$json{"files"}};
			say @files;
		}
	}
}
