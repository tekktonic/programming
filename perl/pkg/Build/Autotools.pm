use strict;
use diagnostics;
use warnings;
use Cwd;

use IPC::Run qw(run);

use autodie;

sub build {
	my %args = @_;
	my $dir = $args{"dir"} or die;
	my $current = getcwd;
	my @flags = @{$args{"flags"} or [""]};
	my $dest = $args{"dest"} or die;
	chdir($dir);

	run('./configure', @flags);
	run('make', "-j", "5");
	run('make', 'install', "DESTDIR=$dest");
}
1;
