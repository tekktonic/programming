use warnings;
use strict;
use autodie;
use WWW::Mechanize;
use HTTP::Cookies;

my $subreddit = "gonewildaudio";
my $initial = "http://www.reddit.com/over18?dest=http%3A%2F%2Fwww.reddit.com%2Fr%2F$subreddit";

my $mech = WWW::Mechanize->new(cookie_jar => HTTP::Cookies->new());

$mech->get($initial);
$mech->form_number(3);
$mech->click_button(value => "yes");

while (1)
{
    foreach my $i ($mech->find_all_links(url_regex => qr#http\://soundgasm\.net.*#))
    {print $i->url() . "\n";}
    my @links = $mech->find_all_links();
    $mech->follow_link(url => (($links[$#links - 29])->url()));
}
