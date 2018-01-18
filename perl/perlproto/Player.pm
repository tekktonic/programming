package Player;
use strict;
use diagnostics;
use v5.18;

use SDL ':all';
use SDL::Video;
use SDL::Image;
use SDL::Color;
use SDL::TTF;
use SDL::Rect;
use SDL::Events;

use Sprite;

use Util;

our @ISA = ("Sprite");

sub new {
    my ($class, $args) = @_;

    my $self = $class->SUPER::new($args);

    $self->{g} = 0;
    $self->{score} = 0;
    $self->{font} = SDL::TTF::open_font("DejaVuSans.ttf", 12);
    
    return $self;
}

sub draw {
    my ($class) = @_;
    $class->SUPER::draw();
    my $fontsurf = SDL::TTF::render_text_blended($class->{font}, $class->{score}, SDL::Color->new(255, 255, 0));
    
    SDL::Video::blit_surface($fontsurf, SDL::Rect->new(0,
                                                       0, $fontsurf->w, $fontsurf->h), $class->{dest_surf},
                             SDL::Rect->new(0, 0, 1024, 768));
}
sub update {
    my ($class, $keystate, $objs) = @_;

    $class->SUPER::update();

    $class->{x_speed} = step_towards($class->{x_speed}, 0, 10);

    if (($class->y + $class->h) > 768)
    {
        ${$class->{running}} = 0;
    }
    
    my @obj_list = @{$objs};
    
    if ($keystate->[SDL::Events::SDLK_LEFT])
    {
        $class->{x_speed} = -15;
    }
    if ($keystate->[SDL::Events::SDLK_RIGHT])
    {
        $class->{x_speed} = 15;
    }

    if ($keystate->[SDL::Events::SDLK_UP])
    {
        if ($class->{g})
        {
            $class->{y_speed} = -40;
            $class->{y} -= 1;
            $class->{g} = 0;
        }
    }

    my @platforms = grep({$_->isa("Platform")} @obj_list);

    if (grep({$_->contains_rect($class->x - 1, $class->y + 1, 
                                $class->w + 2, $class->h - 4)} @platforms))
    {
        $class->{x_speed} = 0;
    }
    
    if (my @plat = grep({$_->contains_rect($class->{x}, $class->{y} + 30, 
                             $class->{w}, 2)} @platforms))
    {
        $class->{y_speed} = ($plat[0])->{y_speed};
        $class->{y} = ($plat[0])->y - $class->h - 1;
        $class->{g} = 1;
    }
    elsif (grep({$_->contains_rect($class->{x}, $class->{y} - 1, 
                             $class->{w}, 1)} @platforms))
    {
        $class->{y} = ($_[0])->y + ($_[0])->h + 1;
        $class->{y_speed} = ($_)->{y_speed};
    }

    else
    {
        $class->{y_speed} += 3 unless $class->{y_speed} > 15;
    }

    my @coins = grep($_->isa("Coin"), @obj_list);
    if (my @c = grep($_->contains_rect($class->{x}, $class->{y},
                                          $class->{w}, $class->{h}), @coins))
    {
        say "COINS: " . @c;
        my @objs = @{$objs};
        @objs = grep({$_ != $coins[0]} @objs); # Coins can only be one per platform
        $class->{score} += 100;
    }

    $class->{score}++;
}

1;

