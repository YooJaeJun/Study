using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp._3.DataStructure
{
    class ArrayListDic
    {
        static int GetHighestScore(int[] scores)
        {
            int ret = scores[0];
            foreach(int elem in scores)
            {
                if (ret < elem)
                {
                    ret = elem;
                }
            }
            return ret;
        }
        static int GetAverageScore(int[] scores)
        {
            int sum = 0;
            foreach(int elem in scores)
            {
                sum += elem;
            }
            return scores.Length == 0 ? 0 : sum / scores.Length;
        }
        static int GetIndexOf(int[] scores, int value)
        {
            for (int i=0; i<scores.Length; i++)
            {
                if (value == scores[i])
                {
                    return i;
                }
            }
            return -1;
        }

        static void Swap(ref int a, ref int b)
        {
            int temp = a;
            a = b;
            b = temp;
        }
        static void Sort(int[] scores)
        {
            // 선택정렬
            //for (int i = 0; i < scores.Length - 1; i++)
            //{
            //    int minn = scores[i];
            //    int minIdx = i;
            //    for (int j = i + 1; j < scores.Length; j++)
            //    {
            //        if (minn > scores[j])
            //        {
            //            minn = scores[j];
            //            minIdx = j;
            //        }
            //    }
            //    Swap(ref scores[i], ref scores[minIdx]);
            //}

            // 버블정렬
            for (int i = 0; i < scores.Length - 1; i++)
            {
                for (int j = i; j < scores.Length - 1; j++)
                {
                    if (scores[j] > scores[j + 1])
                    {
                        Swap(ref scores[j], ref scores[j + 1]);
                    }
                }
            }
        }

        class Map
        {
            int[,] tiles = { 
                {1,1,1,1,1}, 
                {1,0,0,0,1},
                {1,0,0,0,1},
                {1,0,0,0,1},
                {1,1,1,1,1},
            };

            public void Render()
            {
                var defaultColor = Console.ForegroundColor;
                for (int y =0; y<tiles.GetLength(1); y++)
                {
                    for (int x = 0; x<tiles.GetLength(0); x++)
                    {
                        if (tiles[y,x] == 1)
                            Console.ForegroundColor = ConsoleColor.Red;
                        else 
                            Console.ForegroundColor = ConsoleColor.Green;
                        Console.Write('\u25cf');
                    }
                    Console.WriteLine();
                }
                Console.ForegroundColor = defaultColor;
            }
        }
        class Monster
        {
            public int id;
            public Monster(int id) { this.id = id; }
        }

        static void Main(string[] args)
        {
            //int[] scores = new int[5];
            //scores[1] = (int)1.5;

            //for (int i=0; i<scores.Length; i++)
            //{
            //    Console.WriteLine(scores[i]);
            //}

            //foreach(int score in scores)
            //{
            //    Console.WriteLine(score);
            //}

            //int[] scores2 = new int[5] { 10, 20, 30, 40, 50 };
            //int[] scores3 = new int[] { 10, 20, 30, 40, 50 };
            //int[] scores4 = { 70, 80, 90, 100, 110 };

            //scores2 = scores4;  // 참조
            //scores4[0] = 1111;


            //int[] scores = new int[7] { 10, 30, 40, 20, 50, 90, 70 };
            //Console.WriteLine(GetHighestScore(scores));
            //Console.WriteLine(GetAverageScore(scores));
            //Console.WriteLine(GetIndexOf(scores, 40));
            //Sort(scores);
            //foreach(int elem in scores)
            //{
            //    Console.WriteLine(elem);
            //}


            //int[] scores = new int[7] { 10, 30, 40, 20, 50, 90, 70 };

            //// int[,] arr = new int[2, 3] { { 1, 2, 3 }, { 4, 5, 6 } };
            //int[,] arr = { { 1, 2, 3 }, { 4, 5, 6 } };

            //arr[0, 0] = 1;
            //arr[1, 0] = 1;


            //Map map = new Map();
            //map.Render();


            //// 1차원만 가변배열
            //int[][] dynamicArray = new int[2][];
            //dynamicArray[0] = new int[5];
            //dynamicArray[1] = new int[2];
            //dynamicArray[1][1] = 99;


            // List
            //List<int> list = new List<int>();
            //list.Add(1);
            //list.Add(1);
            //list.Add(5);
            //// Console.WriteLine(list[0]);

            //// 삽입 삭제
            //list.Insert(2, 999);
            //list.Remove(1);
            //list.RemoveAt(0);
            //// list.Clear();

            //// foreach (int elem in list)
            ////     Console.WriteLine(elem);
            //for (int i = 0; i < list.Count; i++)
            //    Console.WriteLine(list[i]);


            // Dictionary
            // Hashtable
            Dictionary<int, Monster> dic = new Dictionary<int, Monster>();
            // dic.Add(1, new Monster(1));
            // dic[5] = new Monster(5);

            for (int i=0; i<10000; i++)
            {
                dic.Add(i, new Monster(i));
            }
            Monster mon = dic[5000];

            bool found = dic.TryGetValue(25000, out mon);

            dic.Remove(2);
        }
    }
}
