module MPD;


class MPDSong
{
    has Str $.file is rw = "";
    has Str $.artist is rw = "";
    has Str $.albumartist is rw = "";
    has Str $.title is rw = "";
    has Str $.album is rw = "";
    has Str $.track is rw = "";
    has Str $.id is rw = "";
    has Str $.time is rw = "";
    has Str $.pos is rw = "";

    method parse (Str $to-parse)
    {
	my @lines = $to-parse.lines;

	for @lines -> $line
	{
	    if $line ~~ /^^file\: (.*)$$/ {$.file = $0.Str;}
	    if $line ~~ /^^Title\:\s+(.*)$/ {$.title = $0.Str;}
	    if $line ~~ /^^Artist\:\s+(.*)$$/ {$.artist = $0.Str;}
	    if $line ~~ /^^Album\:\s+(.*)$$/ {$.album = $0.Str;}
	    if $line ~~ /^^AlbumArtist\:\s+(.*)$$/ {$.albumartist = $0.Str;}
	    if $line ~~ /^^Track\:\s+(.*)$$/ {$.track = $0.Str;}
	    if $line ~~ /^^Id\:\s+(.*)$$/ {$.id = $0.Str;}
	    if $line ~~ /^^Time\:\s+(.*)$$/ {$.time = $0.Str;}
	}
    }

    method gist()
    {
	($.file, $.title, $.artist, $.album, $.albumartist, $.track, $.time).join(",");
    }	
}

class MPDClient
{
    has $.host; # We keep these in case we need to reconnect
    has $.port;
    has $.version is rw;
    has $.sock is rw;
    method new(Str :$host is copy, Int :$port is copy)
    {
	$host = "localhost" unless $host;
	$port = 6600 unless $port;
	$.bless(:$host, :$port);
    }

    method connect()
    {
	$.sock = IO::Socket::INET.new(host => $.host, port => $.port);
	my $s = $.sock.recv;
	$.version = $0.Str if ($s ~~ m/OK\sMPD\s(.*)/);
    }

    method msg(Str $msg)
    {
	self.connect();
	$.sock.write(($msg ~ "\n").encode('UTF-8'));
	
	my $song = MPDSong.new;
	$song.parse($.sock.recv);
	$.sock.close();
	$song;
    }


    method current() {$.msg("currentsong\n");}

    method pause() {$.msg("pause\n"); $.current;}
    
    method play() {$.msg("play\n");$.current;}

    method setvol(Int: $num) { $.msg("setvol $num\n"); $.current}
    method crossfade(Int: $num) { $.msg("crossfade $num\n"); $.current}
    method nextSong() {$.msg("next\n"); $.current;} # next is a reserved word
    method prevSong() {$.msg("prev\n"); $.current;}

    method idle() {$.msg("idle player\n"); $.current;}
}
