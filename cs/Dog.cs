using System;

public class Dog
{
    static public void Type()
    {
        Console.WriteLine("a Dog!");
    }
    public void Bark()
    {
        Console.WriteLine("bark!");
    }
    public void Bark(int times)
    {
        for (var i = 0; i < times; ++i )
            Console.WriteLine("bark!");
    }
}