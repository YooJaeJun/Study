using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp._4.Etc
{
    class Event_Program
    {
        static void OnInputTest()
        {
            Console.WriteLine("Input Received!");
        }
        static void Main(string[] args)
        {
            Event_InputManager inputManager = new Event_InputManager();

            inputManager.InputKey += OnInputTest;   // 구독 신청하는 개념으로 생각

            while (true)
            {
                inputManager.Update();
            }
        }
    }
}
