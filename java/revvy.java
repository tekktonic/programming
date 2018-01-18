import java.util.ArrayList;
import java.util.Arrays;


class Eff {
    public int[] f(int[] input)
    {
	ArrayList<Integer> a, b, c;
	int[] out = new int[input.length];

	a = new ArrayList<Integer>();
	a.add(1);
	for(int i = 0; i < input.length - 1; i++)
	{

	    a.add(input[i] * a.get(i));
	}


	b = new ArrayList<Integer>(); // b is purely temporary

	b.add(1);
	for(int i = 1; i < input.length; i++)
	{

	    b.add(input[i] * b.get(i));
	}

	c = new ArrayList<Integer>();
	for(int i = b.size() - 1; i > -1; --i)
	{
	    c.add(b.get(i));
	}

	System.out.println(Arrays.toString(input));
	System.out.println(a);
	System.out.println(c);
	for(int i = 0; i < out.length; i++)
	{
	    out[i] = a.get(i) * c.get(i);
	}
	return out;
    }
}

class Revvy {

    public static void main(String[] args)
    {
	int[] test = new int[] {1, 2, 3, 4};
	Eff eff = new Eff();
	int[] ret = eff.f(test);

	System.out.println(Arrays.toString(ret));

    }
}
