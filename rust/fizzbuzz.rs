fn main() {
    for int::range(1, 101) |num| {
        if((num % 3) == 0) || ((num % 5) == 0)
        {
            if (is_three) { print("Fizz")}
            if (is_five) { print("Buzz")}
            print("\n");
        }
    }
}