#!/usr/bin/perl
use strict;
use warnings;
use IO::Socket::INET;
use threads;

my $sock = IO::Socket::Inet->new(Proto => "tcp", PeerAddr => "localhost:5200");

my $in = threads->create(\&listen)

sub listen {
    
