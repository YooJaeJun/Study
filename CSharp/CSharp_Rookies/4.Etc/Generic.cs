using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp._4.Etc
{
    class Generic
    {
        // Monster 혹은 Monster 상속받은 클래스를 받아야 함을 의미.
        // class MyList<T> where T : Monster
        // 기본 생성자 있어야 함을 의미
        // class MyList<T, K> where T : new
        // 복사 형식
        // class MyList<T, K> where T : struct
        // 참조 형식
        // class MyList<T> where T : class
        class MyList<T>
        {
            T[] arr = new T[10];
            public T GetItem(int i)
            {
                return arr[i];
            }
        }
        class MyList2<T, K> where T : class
        {
            K[] arr = new K[10];
        }
        class Monster
        {
        }
        static void Test<T>(T input)
        {
        }

        static void Main(string[] args)
        {
            // var : 알아서 타입 캐스팅
            var obj3 = 3;
            var obj4 = "Hello World!";

            // object : object라는 타입
            // 참조 타입이라 힙 영역에 3에 할당
            // Boxing
            object obj = 3;
            object obj2 = "Hello World!";
            // 속도 느리다.
            // 힙에서 꺼내와 변수에 할당
            // Unboxing
            int num = (int)obj;
            string str = (string)obj2;


            MyList<int> myIntList = new MyList<int>();
            int item = myIntList.GetItem(0);
            MyList<float> myFloatList = new MyList<float>();
            MyList<Monster> myMonsterList = new MyList<Monster>();

            Test<int>(3);
            Test<float>(3.0f);
        }
    }
}
