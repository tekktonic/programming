extern mod std;
use std::rope;
use std::comm;

fn main(args: ~[str])
{
    for args.each |arg| { print(arg); }
    return 0;
}
