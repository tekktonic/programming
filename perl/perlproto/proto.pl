use strict;
use warnings;
use diagnostics;
use v5.14; 
use SDL ':all';
use SDL::Video;
use SDL::Image;
use SDL::TTF;
use SDL::Rect;
use SDL::Events;
use SDL::Mixer;
use SDL::Mixer::Channels;
use SDL::Mixer::Music;

use Player;
use Platform;

my $running = 1;
sub end_game
{
    $running = 0;
}

SDL::init(SDL::SDL_INIT_EVERYTHING);
SDL::Mixer::init(SDL::Mixer::MIX_INIT_OGG);
SDL::TTF::init();

my $win = SDL::Video::set_video_mode(1024, 768, 32, SDL::Video::SDL_HWSURFACE);
SDL::Mixer::open_audio(44100, SDL::Mixer::MIX_DEFAULT_FORMAT, 2, 1024);
SDL::Mixer::Channels::allocate_channels(32);
my $mus = SDL::Mixer::Music::load_MUS("thrash.ogg");

my $bg = SDL::Image::load("bg.jpg");

my $plat_speed = 3;

my @objects = ();
my $objref = \@objects;
say $objref . " IS A REFERENCE";
push(@objects, Player->new({image => "dino_small.png", x => 32, y => 0, w => 32, h =>32, running => \$running,
                            dest_surf => $win, obj_list => $objref}));
push(@objects, Platform->new({image => "platform.png", x => 0, y=> 48, w => 1024, h => 16, dest_surf => $win, running => \$running,
                              y_speed => 3, obj_list => $objref}));


SDL::Mixer::Music::play_music($mus, -1);

my $ticks = 1;
while ($running)
{
    SDL::Events::pump_events();

    my $state = SDL::Events::get_key_state();
    if ($state->[SDL::Events::SDLK_ESCAPE])
    {
        $running = 0;
    }

    SDL::Video::blit_surface($bg,
                             SDL::Rect->new(0, 0, 1024, 768),
                             $win,
                             SDL::Rect->new(0, 0, 1024, 768));

    if ($ticks % 300 == 0)
    {
        $plat_speed++;
    }
    
    if ($ticks % 60 == 0)
    {
        push(@objects, @{Platform::gen_pair($win, $plat_speed, \@objects)});
    }

    foreach my $obj (@objects)
    {
        $obj->update($state, \@objects);
        $obj->draw();
    }

    SDL::Video::flip($win);
    SDL::delay(1000/30);
    $ticks++;
#    say(@objects);
}

