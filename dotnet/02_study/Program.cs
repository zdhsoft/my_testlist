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
//            string s = Console.ReadLine();
//            Console.WriteLine("read line:" + s);

            Console.WriteLine("{0} + {1} = {2}",1,2,3);
            int m = 940;
            int j = 73;
            Console.WriteLine(" {0,4}\n+{1,4}\n-----\n {2,4}", m, j, m+j);
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