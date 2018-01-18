use Bot::BasicBot::Op;


my @banned = qw(rme nagl idgi mte ia ita nhft nbd smh nhf jsyk);

sub said {
    my $self, $msg = @_;

    foreach i @banned
    {
	if (m/[(^|\s)${i}(\s|$)/)
	{
	}
    }
}
	    
