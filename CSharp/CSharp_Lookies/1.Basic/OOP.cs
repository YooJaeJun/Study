using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp
{
    Knight
    속성: hp, attack, pos
    기능: Move, Attack, Die

    Ref 참조

    class Character
    {
        static public int counter = 1;
        public int id;
        public int hp;
        public int attack;
        public Character()
        {
            Console.WriteLine("Player 생성자 호출!");
        }
        public Character(int hp)
        {
            this.hp = hp;
            Console.WriteLine("Player hp 생성자 호출!");
        }
        public void Move()
        {
            Console.WriteLine("Player Move");
        }
        public void Attack()
        {
            Console.WriteLine("Player Attack");
        }
    }
    class Mage : Character
    {

    }
    class Archer : Character
    {

    }
    class Knight : Character
    {
        int c;
        public Knight() : base(100)
        {
            this.c = 10;
            base.hp = 100;
            Console.WriteLine("Knight 생성자 호출!");
        }
        static public Knight CreateKnight()
        {
            Knight knight = new Knight();
            knight.hp = 100;
            knight.attack = 1;
            return knight;
        }
    }

    class Knight
    {
        static public int counter = 1;
        public int id;
        public int hp;
        public int attack;
        static public void Count()   // static 함수에서 비 static 멤버 접근 불가
        {
            counter++;
        }
        static public Knight CreateKnight()
        {
            Knight knight = new Knight();
            knight.hp = 100;
            knight.attack = 1;
            return knight;
        }
        public Knight()
        {
            id = counter;
            Count();

            hp = 100;
            attack = 10;
            Console.WriteLine("생성자 호출");
        }
        public Knight(int hp) : this()  // 기본 생성자 먼저 호출
        {
            this.hp = hp;
            Console.WriteLine("(int) 오버로딩한 생성자 호출");
        }
        public Knight(int hp, int attack) : this(hp)
        {
            this.attack = attack;
            Console.WriteLine("(int, int) 오버로딩한 생성자 호출");
        }
        public Knight Clone()
        {
            Knight knight = new Knight();
            knight.hp = hp;
            knight.attack = attack;
            return knight;
        }
        public void Move()
        {
            Console.WriteLine("Knight Move");
        }
        public void Attack()
        {
            Console.WriteLine("Knight Attack");
        }
    }

    복사
    struct Mage
    {
        public int hp;
        public int attack;
    }



    class OOP
    {
        static void KillKnight(Knight knight)
        {
            knight.hp = 0;
        }
        static void KillMage(Mage mage)
        {
            mage.hp = 0;
        }
        static void Main(string[] args)
        {
            // Knight knight = Knight.CreateKnight();
            Knight knight = new Knight();
            knight.Move();


            Mage mage;
            mage.hp = 100;
            mage.attack = 50;
            KillMage(mage);

            Knight knight = new Knight();
            knight.hp = 100;
            knight.attack = 10;
            knight.Move();
            knight.Attack();
            KillKnight(knight);

            Mage mage2 = mage;
            mage.hp = 0;
            Knight knight2 = knight;    // 얕은 복사. knight2가 knight를 가리킴
            knight.hp = 0;

            Knight knight2 = new Knight();
            knight2.hp = knight.hp;
            knight2.attack = knight.attack;
            knight.hp = 0;                  // 깊은 복사

            Knight knight = new Knight(200, 20);
            Knight knight2 = knight.Clone();
            knight2.hp = 0;

            static 테스트
           Knight knight = new Knight();
            Knight knight2 = new Knight();
            knight2.hp = 80;
            Knight knight3 = new Knight();
            knight3.hp = 200;

            Knight knight = Knight.CreateKnight();  // static
            knight.Move();  // 일반

            Console.WriteLine();    // static

            Random rand = new Random();
            rand.Next();    // 비 static

            static 함수는 인스턴스화 된 객체 없이 함수 호출 가능
        }
    }
}
