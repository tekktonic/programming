use strict;
use diagnostics;
use v5.22;

use Wx;
use Wx::AUI;

package LocalWeb;
use base "Wx::App";

sub OnInit
{
    my $self = shift;

    my $frame = Wx::Frame->new(undef, -1, "LocalWeb", &Wx::wxDefaultPosition,
                               &Wx::wxDefaultSize,
                               &Wx::wxMAXIMIZE_BOX | &Wx::wxCLOSE_BOX);

    $frame->Show();
}

LocalWeb->new()->MainLoop();
