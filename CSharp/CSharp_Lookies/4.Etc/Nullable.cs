using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp._4.Etc
{
    class Nullable
    {
        class Monster
        {
            public int id { get; set; }
        }
        static int Find()
        {
            return 0;
        }
        static void Main(string[] args)
        {
            // Nullable

            int? number = null;
            
            // number = 3;

            // int a = number; (x)
            if (number.HasValue)
            {
                int a = number.Value;
                Console.WriteLine(a);
            }

            // number = 3;
            int b = number ?? 0;
            // 같은 말
            // int b = (number != null) ? number.Value : 0;

            Console.WriteLine(b);



            Monster monster = null;

            int? id = monster?.id;
            // 같은 말
            //if (monster == null)
            //{
            //    id = null;
            //}
            //else
            //{
            //    id = monster.id;
            //}

            // null이라는 타입
            // ??
            // int? id = monster?.id;
        }
    }
}
