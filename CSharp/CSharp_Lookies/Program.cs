using System;

namespace Csharp
{
    class GameObject
    {
        public int id;
    }
    class Knight : GameObject
    {

    }
    class Orc : GameObject
    {

    }
    class Program
    {
        static void TestObject<T>(T obj) where T : GameObject
        {
            int id = obj.id;
        }
        static void Main(string[] args)
        {
            TestObject<Knight>(new Knight());
            // TestObject<int>(3);
        }
    }
}