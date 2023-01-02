using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace CSharp._4.Etc
{
    // Important 컴퓨터가 런타임에 체크
    class Important : System.Attribute
    {
        string message;
        public Important(string message) { this.message = message; }
    }
    class Monster
    {
        // hp 입니다. 중요한 정보입니다.
        [Important("Very Important")]
        public int hp;

        protected int attack;
        private float speed;

        void Attack() { }
    }
    class Reflection
    {
        static void Main(string[] args)
        {
            // Reflection : X-Ray. 런 타임에 뜯고 분석 가능
            Monster monster = new Monster();
            Type type = monster.GetType();

            var fields = type.GetFields(System.Reflection.BindingFlags.Public
                | System.Reflection.BindingFlags.NonPublic
                | System.Reflection.BindingFlags.Static
                | System.Reflection.BindingFlags.Instance);

            foreach(FieldInfo field in fields)
            {
                string access = "protected";
                if (field.IsPublic)
                    access = "public";
                else if (field.IsPrivate)
                    access = "private";

                var attributes = field.GetCustomAttributes();

                Console.WriteLine($"{access} {field.FieldType.Name} {field.Name}");
            }
        }
    }
}
