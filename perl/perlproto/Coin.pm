package Coin;
use strict;
use diagnostics;
use v5.18;

use SDL ':all';
use SDL::Video;
use SDL::Image;
use SDL::Rect;
use SDL::Events;

use Sprite;

our @ISA = ("Sprite");

sub new {
    my ($class, $args) = @_;

    my $self = $class->SUPER::new($args);
    
    $self->{images} = [];
    $self->{frame} = 1;
    my $i = 0;
    my @images = qw(coin1.png coin2.png coin3 coin2.png coin1.png);
    foreach my $im (@images)
    {
        $self->{images}[$i++] = SDL::Image::load($im);
    }

    say("coin " . $self->x . " " . $self->y);
    return $self;
}

sub update {
    my ($class) = @_;
    say("coin " . $class->x . " " . $class->y);
    $class->SUPER::update();
    $class->{image} = $class->{images}[($class->{frame})++ % 4];
}


1;
