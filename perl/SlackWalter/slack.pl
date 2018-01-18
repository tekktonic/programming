use v5.20;

use Slack::RTM::Bot;
use Data::Dumper;
use IPC::Run 'run';
use File::Slurp 'slurp';
use autodie;

use strict;
use diagnostics;

my $bot = Slack::RTM::Bot->new(token => 'xoxb-159024056884-WXa74655dI2CiWg2q0ia9G8f');


$bot->on({
    channel => qr/.*/,
    text => qr/.*\.gifv/},
         sub {
             my ($response) = @_;
             print(Dumper($response));
             if ($response->{text} =~ /.*\<(.*)\>.*/) {
                 $bot->say(channel => $response->{channel},
                           text => ($1 =~ s/\.gifv/\.mp4/r))
             }
             print($response->{text} . "\n");
         });

$bot->on({
    channel => qr/.*/,
    text => qr/^!w/
         },
         sub {
             my ($response) = @_;
             
             my $input = (split(' ', $response->{text}, 2))[1];
             my $out;
             chomp(my $walter = `which walter`);
             
             $input =~ s/\;/\\\;/;
             $input =~ s/\$/\\\$/;
             $input =~ s/\`/\\\`/;
             $out = readpipe("$walter $input");
             
             
             $bot->say(channel => $response->{channel}, text => $out);
         });
$bot->start_RTM(sub {
    #    $bot->say(channel => 'takeitslow', text => "OI FUCKERS")
    
    while (1) { print"foo\n"; sleep(1);}
                });
