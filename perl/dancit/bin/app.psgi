#!/usr/bin/env perl

use strict;
use warnings;
use diagnostics;
use FindBin;
use Dancer2;
use lib "$FindBin::Bin/../lib";

use dancit;

get('/d/:subreddit',  sub {
    return "meh".param('subreddit');
    });

start;
