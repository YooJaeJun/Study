using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp
{
    class Control
    {
        enum Choice
        {
            SCISSORS,
            ROCK,
            PAPER
        }

        // 메소드 함수
        // 한정자 반환형식 이름(매개변수 목록)
        static void HelloWorld()
        {
            Console.WriteLine("Hello World");
        }

        static int Add(int a, int b)
        {
            return a + b;
        }

        static void AddOne(ref int number)
        {
            number++;
        }

        static int Addon2(int number)
        {
            return number + 1;
        }

        static void Swap(ref int a, ref int b)
        {
            int temp = a;
            a = b;
            b = temp;
        }

        // out : 참조하고, 반드시 값 넣어주기
        static void Divide(int a, int b, out int result1, out int result2)
        {
            result1 = a / b;
            result2 = a % b;
        }

        static double Add(double a, double b)
        {
            return a + b;
        }
        static int Add(int a, int b, int c, int d = 0)
        {
            return a + b + c + d;
        }
        static void Main(string[] args)
        {
            HelloWorld();
            Console.WriteLine(Add(1, 2));

            int number = 2;
            Control.AddOne(ref number);
            Console.WriteLine(number);

            int num1 = 1, num2 = 2;
            Swap(ref num1, ref num2);
            Console.WriteLine("num1 = " + num1);
            Console.WriteLine("num2 = " + num2);

            num1 = 10;
            num2 = 3;
            int result1, result2;
            Divide(num1, num2, out result1, out result2);
            Console.WriteLine(result1);
            Console.WriteLine(result2);

            double d1 = 1.5;
            double d2 = 2.8;
            Console.WriteLine(Add(d1, d2));
            Console.WriteLine(Add((int)d1, (int)d2));

            int i1 = 1, i2 = 2, i3 = 3;
            Console.WriteLine(Add(i1, i2, i3));
            Console.WriteLine(Add(i1, i2, i3, 4));

            //int hp = 100;
            //hp -= 100;
            //bool isDead = (hp <= 0);

            //if (isDead)
            //{
            //    Console.WriteLine("Yoo are dead!");
            //}
            //else if (!isDead)
            //{
            //    Console.WriteLine("Yoo are alive!");
            //}
            //else
            //{
            //    Console.WriteLine("이런 경우는 없음");
            //}


            //int choice = 1;

            //switch(choice)
            //{
            //    case 0:
            //        Console.WriteLine("가위");
            //        break;
            //    case 1:
            //        Console.WriteLine("바위");
            //        break;
            //    case 2:
            //        Console.WriteLine("보");
            //        break;
            //    default:
            //        Console.WriteLine("잘못 입력함");
            //        break;
            //}

            //bool isPair = (choice % 2 == 0 ? true : false);

            //Random rand = new Random();
            //int aiChoice = rand.Next(0, 3); // 0~2 사이의 랜덤값

            //int choice = Convert.ToInt32(Console.ReadLine());

            //string[] rcp = { "가위 선택", "바위 선택", "보 선택" };

            //Console.WriteLine("당신의 선택은?");
            //Console.WriteLine(rcp[choice]);

            //Console.WriteLine("\n컴퓨터의 선택은?"); 
            //Console.WriteLine(rcp[aiChoice]);

            //string[,] result = { {"무승부", "당신의 패배", "당신의 승리"},
            //    {"당신의 승리", "무승부", "당신의 패배"},
            //    {"당신의 패배", "당신의 승리", "무승부"} };

            //Console.WriteLine("\n결과는?");
            //Console.WriteLine(result[choice,aiChoice]);



            //int num = 0;
            //// 상수 시 switch 문에서 ㄱㅊ
            ////const int SCISSORS = 0;
            ////const int ROCK = 1;
            ////const int PAPER = 2;

            //switch (num)
            //{
            //    case (int)Choice.SCISSORS:  
            //        break;
            //}

            //int count = 5;
            //while (count-- > 0)
            //{
            //    Console.WriteLine("Hello");
            //}
            //Console.WriteLine("\n");

            //count = 5;
            //string ans = Console.ReadLine();
            //do
            //{
            //    Console.WriteLine(ans);
            //} while (count-- > 0);


            //for (int i=0; i<5; i++)
            //{
            //    Console.WriteLine("Hello");
            //}


            //int num = 96;

            //bool isPrime = true;

            //for (int i=2; i<num; i++)
            //{
            //    if ((num % i) == 0)
            //    {
            //        isPrime = false;
            //        break;
            //    }
            //}

            //if (isPrime)
            //    Console.WriteLine("소수!");
            //else
            //    Console.WriteLine("소수 아닛느");
        }
    }
}
