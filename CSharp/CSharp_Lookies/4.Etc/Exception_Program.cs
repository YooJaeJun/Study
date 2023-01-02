using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp._4.Etc
{
    class Exception_Program
    {
        class TestException : Exception
        {

        }
        static void Main(string[] args)
        {
            // 예외처리는 보통 크래시 되게 하고 고친다고 함
            // 심각한 상황이 아닌 특수한 경우 사용
            try
            {
                // 1. 0으로 나눌 때
                // 2. 잘못된 메모리를 참조 (null 접근, 캐스팅 잘못)
                // 3. 오버플로우
                
                // int a = 10;
                // int b = 0;
                // int result = a / b;

                throw new TestException();  // 커스텀. 사용 잘 안 함

                int c = 1;
            }
            catch (DivideByZeroException e)
            {
            }
            catch (Exception e)
            {
            }
            finally
            {
                // 파일 정리, DB 등등..
            }
        }
    }
}
