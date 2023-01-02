using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp
{
    // 자동차
    // 핸들, 페달, 차문
    // 전기장치 엔진 기름 <-> 외부 노출

    class Player
    {
        protected int hp;
        protected int attack;

        // 오버로딩: 함수의 재사용
        // 오버라이딩: 상속 관계에서 부모 클래스의 함수 재정의
        public virtual void Move()
        {
            Console.WriteLine("Player 이동");
        }
    }
    class Knight : Player
    {
        // 접근 한정자
        // 3대장, internal, protected internal
        // 생략 시 private
        public void SetHp(int hp)   // 디버깅 유리
        {
            this.hp = hp;
        }
        public override void Move()
        {
            base.Move();
            Console.WriteLine("Knight 뚜벅이 이동");
        }
    }
    class SuperKnight : Knight
    {
        // sealed : c++ final
        public sealed override void Move()
        {
            Console.WriteLine("SuperKnight 뚜벅이 이동");
        }
    }
    class Mage : Player
    {
        public int mp;
        public override void Move()
        {
            Console.WriteLine("Mage 날기 이동");
        }
    }

    //class SuperKnight : Knight
    //{
    //    void Test()
    //    {
    //        attack = 2;
    //        SetHp(10);
    //    }
    //}

    class OOP2
    {
        static Player FindPlayerById(int id)
        {
            // id에 해당하는 플레이어를 탐색
            // 못찾았으면 
            return null;
        }
        static void EnterGame(Player player)
        {
            // Mage mage = (Mage)player;    // 위험

            // 방법 1
            //bool isMage = (player is Mage);
            //if (isMage)
            //{
            //    Mage mage = (Mage)player;
            //    mage.mp = 10;
            //}

            // 방법 2 - 더 깔끔
            Mage mage = (player as Mage);
            if (mage != null)
            {
                mage.mp = 10;
            }

            player.Move();  // 오버라이딩됨
        }
        static void Main(string[] args)
        {
            //Knight knight = new Knight();
            //Mage mage = new Mage();

            //// Mage 타입 -> Player 타입
            //// Player 타입 -> Mage 타입 (?)
            ////Player magePlayer = mage;
            ////Mage mage2 = (Mage)magePlayer;

            ////EnterGame(knight);
            ////EnterGame(mage);

            ////knight.Move();
            ////mage.Move();

            //EnterGame(knight);
            //EnterGame(mage);



            // string

            string name = "Harry Potter";

            // 1. 찾기
            bool found = name.Contains("Hary");
            int index = name.IndexOf('P');
            int index2 = name.IndexOf('z');

            // 2. 변형
            name = name + " Junior";
            string lowerCaseName = name.ToLower();
            string upperCaseName = name.ToUpper();
            string replacedName = name.Replace('r', 'l');

            // 3. 분할
            string[] names = name.Split(new char[] { ' ' });

            string substringName = name.Substring(5);
            string substringName2 = name.Substring(2, 3);
        }
    }
}
