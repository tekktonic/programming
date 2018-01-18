use strict;
use warnings;
use Digest::MD5;
use LWP::Simple;

sub CheckSum
{
    my $pkg = shift;
    print("fetching md5sum for " . $pkg . "\n");
    getstore("http://tekk.com.ar/owl2/" . $pkg . ".md5", $pkg . ".md5");
    open("knowngood", $pkg . ".md5");
    my $goodsum = <knowngood>;
    chomp($goodsum);
    print("known good: " . $goodsum . "\n");
    close("knowngood");

    open("pack", $pkg);
    binmode("pack");
    my $ctx = Digest::MD5->new;

    $ctx->addfile(*pack);
    my $sum = $ctx->hexdigest;

    print("retrieved sum: " . $sum . "\n");
    die("Checksum failed!\n") unless ($goodsum eq $sum);

}

CheckSum(${ARGV}[0]);
