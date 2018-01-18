package Sprite;
use strict;
use diagnostics;

our @ISA = ("UNIVERSAL");

sub new {
    my ($class, $args) = @_;
    
    my $self = bless({image => SDL::Image::load($args->{image}),
                      x => $args->{x},
                      y => $args->{y},
                      w => $args->{w},
                      h => $args->{h},
                      running => $args->{running},
                      x_speed => $args->{x_speed} || 0,
                      y_speed => $args->{y_speed} || 0,
                      obj_list => $args->{obj_list}, # A reference to the list of objects, nice for some things
                      dest_surf => $args->{dest_surf}}, $class);

    return $self;
}

sub draw {
    my ($class) = @_;

    SDL::Video::blit_surface($class->{"image"}, SDL::Rect->new(0,
                                                         0, $class->{"w"}, $class->{"h"}), $class->{"dest_surf"},
                         SDL::Rect->new($class->{"x"}, $class->{"y"}, 1024, 768));
}

sub x {
    my $class = shift;
    if (@_)
    {
        $class->{x} = shift;
    }
    return $class->{x};
}


sub y {
    my $class = shift;
    if (@_)
    {
        $class->{y} = shift;
    }
    return $class->{y};
}

sub w {
    my $class = shift;
    if (@_)
    {
        $class->{w} = shift;
    }
    return $class->{w};
}

sub h {
    my $class = shift;
    if (@_)
    {
        $class->{h} = shift;
    }
    return $class->{h};
}

sub contains_point
{
    my ($class, $x, $y) = @_;
    my $ox = $class->{x};
    my $oy = $class->{y};
    my $ox2 =  $ox + $class->{w};
    my $oy2 = $oy + $class->{h};
    
    return ($x >= $ox && $x <= $ox2) && ($y >= $oy && $y <= $oy2);
}

sub contains_rect
{
    my ($class, $x, $y, $w, $h) = @_;
    my $ox = $class->{x};
    my $oy = $class->{y};
    my $ox2 =  $ox + $class->{w};
    my $oy2 = $oy + $class->{h};
    if (($x <= $ox2 && $x + $w >= $ox) || ($ox <= $x + $w && $ox2 >= $x))
    {
        if (($y <= $oy2 && $y + $h >= $oy) || ($oy <= $y + $h && $oy2 >= $y))
        {
            return 1;
        }
    }
    return 0;

}

sub update
{
    my ($class) = @_;
    $class->{x} += $class->{x_speed};
    $class->{y} += $class->{y_speed};
}
1;
