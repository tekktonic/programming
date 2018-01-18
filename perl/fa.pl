# A basic-as-possible example for a friend
use strict;
use warnings;
use autodie;
use WWW::Mechanize;
use HTTP::Cookies;

my $username = "a username";
my $password = "something, I dunno. Probably not this long though";

my $mech = WWW::Mechanize->new(cookie_jar => HTTP::Cookies->new());

$mech->get("http://www.furaffinity.net/login");

$mech->submit_form(
    fields => {
	"name" => $username,
	"pass" => $password
    });

$mech->get("/controls/messages");
print($mech->content());
print(($mech->cookie_jar())->as_string());
<>;
#print($mech->content());

