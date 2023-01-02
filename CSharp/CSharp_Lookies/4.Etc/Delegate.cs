using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp._4.Etc
{
    class Delegate
    {
        // UI
        // UI 로직과 게임 로직을 분리해야 한다..
        
        delegate int OnClicked();
        // delegate -> 형식은 형식인데, 함수 자체를 인자로 넘겨주는 형식
        // 반환 int, 입력 void
        // OnClicked 이 delegate 형식의 이름이다.

        static void ButtonPressed(OnClicked clickedFunction /*함수 자체를 인자로 넘겨주고*/)
        {
            // 함수를 호출();
            clickedFunction();
        }
        static int TestDelegate()
        {
            Console.WriteLine("Hello Delegate");
            return 0;
        }
        static int TestDelegate2()
        {
            Console.WriteLine("Hello Delegate 2");
            return 0;
        }
        static void Main(string[] args)
        {
            // delegate(대리자)
            // Call back 방식 - 나중에 연락주세요~
            // ButtonPressed(TestDelegate/*함수*/);

            // 객체 생성 - 체이닝 가능
            OnClicked clicked = new OnClicked(TestDelegate);
            clicked += TestDelegate2;
            ButtonPressed(clicked/*함수*/);
        }
    }
}
