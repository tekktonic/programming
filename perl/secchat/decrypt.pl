use GPG;
use Carp;
use Data::Dumper;

my $msg = "-----BEGIN PGP MESSAGE-----

hQEMA2tp4rZXuAWSAQf/Q17c7fzh0MA0HA+lLveowxgnQiiu49wjY2nsWJNAUxXM
XssU+IKtwPXPOL1AD9MPydN0Vr/oGCRJNsvZ6bCk+AR27gSwSLO5ag7S1ZuXvyIy
ItVh+Wi95QT2EvIkjbeTdw4I8Vxl0vQJ581EzJDB+25x2Xgq9zL3lfARuB45ttyf
NZYKJ88Po/9PrVBr3enS7GSCUN9HwdxUH8p+1OwKV82IJg9n+FT5rfX02kFrvYbG
akhy5vsvKfgENIvQMpxJPD0Gs7pqPty+hTPeFzQHt8QDftcIQWOFjUonCQiLdFi4
P2TbRCmg2MrAIZRycB8JHPyyDtC98yFrsVpEwWybf9JKAYWAUjh+ngSdrdT7XZdq
J2uCsX2Yo60dVtAe0htyayPuGvYqd4I79+VjJLWxskF3+xTeJQFOAAWl7Q0LK7au
301dzhWp1msCQNU=
=qZDN
-----END PGP MESSAGE-----";
my $g = new GPG();

print Dumper($g->list_keys()) . "\n";
my $txt = $g->decrypt("naacpmonadouzelbella", $msg);

print $txt
