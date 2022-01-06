// See https://aka.ms/new-console-template for more information
// Console.WriteLine("Hello, World!");

namespace com.zdhsoft.test
{
    class Test
    {
        public static int Main(string[] args)
        {
            Console.WriteLine("hello world!" + MathMM.add(1,2));

            Console.WriteLine("args length:" + args.Length);

            for (int i = 0; i < args.Length; i++)
            {
                Console.WriteLine("[" + i + "]=" + args[i]);
            }
            string s = Console.ReadLine();
            Console.WriteLine("read line:" + s);
            return 0;
        }

        class MathMM
        {
            public static int add(int x, int y)
            {
                return x + y;
            }
        }
    }
}