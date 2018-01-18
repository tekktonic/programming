use strict;
use warnings;
use IO::Socket::INET;
use GPG;

my $s = IO::Socket::INET->new(LocalAddr => "localhost:2049", Listen => 5, Proto => "tcp");
my $gpg = new GPG();


my $conn = $s->accept();
while (<$conn>)
{
    print $_;
    print $gpg->encrypt($_, "tekk\@parlementum.net");
}

$conn->close();
$s->shutdown(0);
