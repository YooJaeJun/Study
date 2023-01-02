using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp
{
    class TextRPG_OOP
    {
        static void Main(string[] args)
        {
            Game game = new Game();

            while (true)
            {
                game.Process();
            }
        }
    }
}
