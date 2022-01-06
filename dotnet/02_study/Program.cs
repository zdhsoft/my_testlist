// See https://aka.ms/new-console-template for more information
// Console.WriteLine("Hello, World!");

namespace com._02_study
{
    class Test
    {
        public static int Main(string[] args)
        {
            Console.WriteLine("hello world!" + MathMM.Add(1,2));

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
#if DEBUG
            Console.WriteLine("this is debug" + MathMM.IsPositive(1999));
#else
            Console.WriteLine("this is not debug");
#endif

            MathMM.Swap(ref m, ref j);
            Console.WriteLine("m={0}, j={1}",m, j);

            int mmm = 0;
            MathMM.SF(out mmm);
            Console.WriteLine("mmm=" + mmm);

            return 0;
        }

        class MathMM
        {
            public MathMM()
            {

            }
            public static int Add(int x, int y)
            {
                return x + y;
            }

            public static void SF(out int i)
            {
                i = 100;
            }

            public static void Swap(ref int x, ref int y)
            {
                int m = x;
                x = y;
                y = m;
            }

            public static bool IsPositive(int value)
            {
                if (value < 0) {
                    return false;
                } else {
                    return true;
                }
            }
        }
    }
}