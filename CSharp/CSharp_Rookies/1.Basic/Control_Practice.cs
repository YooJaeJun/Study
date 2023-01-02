using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp
{
    class Control_Practice
    {
        static void MultiplicationTables()
        {
            for (int i = 2; i <= 9; i++)
            {
                for (int j = 1; j <= 9; j++)
                {
                    // Console.WriteLine("{0} * {1} = {2}", i, j, i * j);
                    Console.WriteLine($"{i} * {j} = {i * j}");
                }
            }
        }

        static void Star(int n)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j <= i; j++)
                {
                    Console.Write('*');
                }
                Console.WriteLine();
            }
        }

        static int Factorial(int n)
        {
            //int ret = 1;
            //for (int i=n; i>1; i--)
            //{
            //    ret *= i;
            //}
            //return ret;

            if (n == 1) return 1;
            return n * Factorial(n - 1);
        }

        static void Main(string[] args)
        {
            // MultiplicationTables();
            // Star(5);
            Console.WriteLine(Factorial(5));
        }
    }
}
