using System;
using System.Collections;

namespace Simple
{
    class Empty
    {
        public override string ToString()
        {
            return "hello MyName is Empty";

        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("This is C#");
            var data = new ArrayList(10)
            {
                "Visual Basic",
                344,
                55,
                new Empty()
            };
            data.Remove(55);

            foreach (object el in data)
            {
                Console.WriteLine(el);
            }
        }

}
}