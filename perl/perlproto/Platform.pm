package Platform;
use Sprite;
use v5.18;
use Coin;
our @ISA = ("Sprite");

sub new
{
    my ($class, $args) = @_;

    my $self = $class->SUPER::new($args);

#    if (int(rand(10)) == 1)
    {
    push(@{$self->{obj_list}}, Coin->new({x => int(rand(1024)), y => $self->y - 18, w => 16, h => 16, dest_surf => $self->{dest_surf},
                                         running => $self->{running}, image => "coin1.png", obj_list => $self->{obj_list}, y_speed => $self->{y_speed}}));

    }

    return $self;
}

sub update
{
    my ($class, $obj_list) = @_;

    $class->SUPER::update();
    if ($class->y > 768)
    {
        my @objs = @{$obj_list};
        @objs = grep({$_ != $class} @objs);
    }
}

sub gen_pair
{
    my ($dest, $speed, $list) = @_;

    my $first = Platform->new({image => "platform.png", x => -int(rand(1024 + 128) ), y => 0, y_speed => $speed || 3, w => 1024, h => 16, dest_surf => $dest, obj_list => $list});
    my $second = Platform->new({image => "platform.png", x => $first->x + $first->w + int(rand(64) + 64), y => 0, y_speed => $speed || 3, w => 1024, h => 16, dest_surf => $dest, obj_list => $list});

    return [$first, $second];
}

1;
