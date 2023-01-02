using System;

namespace CSharp
{
    class Data
    {
        // 주석띠
        /*
         * ㅇㄴㄹ
         * ㅁㄴㅇㄹ
         */
        static void Main(string[] args)
        {
            // 데이터 + 로직
            // 체력 0

            // byte(1바이트, 0~255), short, int, long
            // sbyte(~128, 127), ushort(0~6만), uint(0~43억), ulong
            /*
            sbyte sby = 1;
            int hp;
            hp = 100;

            ushort level = 5;
            long id = 10000000000;
            byte attack = 0;
            attack--;

            Console.WriteLine("H\n");
            Console.WriteLine("Hello world! {0} !!\n", attack);


            // 10, 2, 16진수
            // 0b10001111 = 1000 1111 = 8f = 0x8F
            // 0x11


            float pi = 3.14f;
            string str = "asdf\n";
            Console.WriteLine(str);

            byte b = 255;
            sbyte sb = (sbyte)b;
            Console.WriteLine(sb);

            int a = 0x0fffffff;
            short s = (short)a;
            Console.WriteLine(s);

            float f = 3.1415f;
            float f2 = f;
            double d = f;

            Console.WriteLine('\n');
            */

            /*
            int hp = 2 * 100 + 1;
            Console.WriteLine(hp);
            hp /= 2;
            Console.WriteLine(hp++);
            Console.WriteLine(++hp);

            bool b = hp < 100;
            Console.WriteLine(b);

            int level = 50;

            bool isAlive = (hp > 0);
            bool isHighLevel = (level >= 40);
            b = isAlive && isHighLevel;
            Console.WriteLine(!b);
            */

            int num = 1;
            num <<= 1;
            Console.WriteLine(num);
            num <<= 2;
            Console.WriteLine(num);
            num >>= 11;
            Console.WriteLine(num);

            num = -2;
            num ^= 5;
            Console.WriteLine(num);
            Console.WriteLine(~num);
            Console.WriteLine(~~num);

            num = 1;
            num <<= 10;
            Console.WriteLine(num + "\n");

            num = 1;
            Console.WriteLine(num & 0);
            Console.WriteLine(num | 0);
            Console.WriteLine(num ^ 0);
            Console.WriteLine((num ^ 1) + "\n");


            int id = 123;
            int key = 401;  // 랜덤값

            int a = id ^ key;   // 암호화
            int b = a ^ key;

            Console.WriteLine(a);
            Console.WriteLine(b);


            // 1. ++ --
            // 2. * / %
            // 3. + -
            // 4. << >>
            // 5. < >
            // 6. == !=
            // 7. &
            // 8. ^
            // 9. |
            // ...


            var num1 = 3;
            var num2 = "Hello";
        }
    }
}
