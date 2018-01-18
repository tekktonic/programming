sub step_towards
{
    my ($current, $target, $step) = @_;
    if ($current < $target)
    {
        $current += $step;
        if ($current > $target)
        {
            return $target;
        }
        else
        {
            return $current;
        }

    }
    elsif ($current > $target)
    {
        $current -= $step;
        if ($current < $target)
        {
            return $target;
        }
        else
        {
            return $current;
        }
    }
    else
    {
        return $target;
    }
}

1;
