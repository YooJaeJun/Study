using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp._4.Etc
{
    // Observer Pattern
    class Event_InputManager
    {
        public delegate void OnInputKey();
        public event OnInputKey InputKey;   // 외부에서 멋대로 호출하지 않게 함
        public void Update()
        {
            if (Console.KeyAvailable == false)
                return;

            ConsoleKeyInfo info = Console.ReadKey();
            if (info.Key == ConsoleKey.A)
            {
                InputKey();
            }
        }
    }
}
