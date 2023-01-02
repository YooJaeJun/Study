using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp._4.Etc
{
    class Interface
    {
        // 추상 클래스
        abstract class Monster
        {
            // 이 함수를 반드시 사용하라는 강요. 인터페이스
            public abstract void Shout();
        }
        // 인터페이스
        interface IFlyable
        {
            void Fly();
        }

        class Orc : Monster
        {
            public override void Shout()
            {
                Console.WriteLine("록타르 오가르!");
            }
        }
        // C# 다중상속 불가
        // class FlyableOrc : Orc, Flyable
        // 죽음의 다이아몬드
        class FlyableOrc : Orc, IFlyable
        {
            public void Fly()
            {
                Console.WriteLine("날아다닌다.");
            }
        }
        class Skeleton : Monster
        {
            public override void Shout()
            {
                Console.WriteLine("끼이익");
            }
        }
        // class SkeletonOrc : Orc, Skeleton

        static void DoFly(IFlyable flyable)
        {
        }
        static void Main(string[] args)
        {
            // IFlyable flyable = new FlyableOrc();
            // DoFly(flyable);
            FlyableOrc orc = new FlyableOrc();
            DoFly(orc);
        }
    }
}
