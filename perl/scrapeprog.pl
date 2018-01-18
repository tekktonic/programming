# A quick script I wrote back in Summer when I was a TA
# It was just meant to give me links to all of the programming
# assignments so that I could glance them over.
use strict;
use warnings;
use diagnostics;
use WWW::Mechanize;
use autodie;
use v5.22;

my $agent = WWW::Mechanize->new(cookie_jar => {});

$agent->get("http://asulearn.appstate.edu");

$agent->follow_link(text => "ASU log in");
say $agent->text();
$agent->form_id("login_form");

$agent->field("j_username", "wilkinsdl");
$agent->field("j_password", "pwd");

$agent->submit();
# Hoop because no js
$agent->submit();

$agent->follow_link(text => "C S1440101-10127201520(FIRST SUMMER 2015)");

say $agent->find_all_links(text_regex => qr/^Program\ [0-9]+.*/i);
