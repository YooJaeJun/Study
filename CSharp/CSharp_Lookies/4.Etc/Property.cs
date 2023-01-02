using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp._4.Etc
{
    // 객체지향 -> 은닉성
    class Knight
    {
        //protected int hp = 100;

        ////public int GetHp() { return hp; }
        ////public void SetHp(int hp) { this.hp = hp; }
        //public int Hp
        //{
        //    get { return hp; }
        //    set { hp = value; }
        //}

        // 자동완성 프로퍼티
        public int Hp { get; set; } = 100;
    }
    class Property
    {
        static void Main(string[] args)
        {
            Knight knight = new Knight();
            knight.Hp = 50;
        }
    }
}
