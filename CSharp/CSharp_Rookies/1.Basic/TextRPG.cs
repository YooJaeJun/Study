using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp
{
    class TextRPG
    {
        enum ClassType
        {
            none,
            warrior,
            archer,
            mage
        }
        struct Player
        {
            public int hp;
            public int attack;
            public ClassType classType;
        }
        enum MonsterType
        {
            none,
            slime,
            orc,
            skeleton
        }
        struct Monster
        {
            public int hp;
            public int attack;
        }
        static void AnnounceCharacter()
        {
            Console.WriteLine("직업을 선택하세요!");
            Console.WriteLine($"[{(int)ClassType.warrior}] 전사");
            Console.WriteLine($"[{(int)ClassType.archer}] 궁수");
            Console.WriteLine($"[{(int)ClassType.mage}] 법사");
        }
        static void ChoiceCharacter(ref Player player)
        {
            AnnounceCharacter();

            bool loopBreak = false;
            player.classType = ClassType.none;

            while (!loopBreak)
            {
                player.classType = (ClassType)Convert.ToInt32(Console.ReadLine());
                loopBreak = true;
                switch (player.classType)
                {
                    case ClassType.warrior:
                        Console.WriteLine("전사 선택");
                        break;
                    case ClassType.archer:
                        Console.WriteLine("궁수 선택");
                        break;
                    case ClassType.mage:
                        Console.WriteLine("법사 선택");
                        break;
                    default:
                        Console.WriteLine("잘못된 선택입니다. 다시 선택해주세요.");
                        loopBreak = false;
                        break;
                }
            }
        }
        static void CreatePlayer(ref Player player)
        {
            // 전사(100/10) 궁수(75/12) 법사(50/15)
            switch (player.classType)
            {
                case ClassType.warrior:
                    player.hp = 100;
                    player.attack = 10;
                    break;
                case ClassType.archer:
                    player.hp = 75;
                    player.attack = 12;
                    break;
                case ClassType.mage:
                    player.hp = 50;
                    player.attack = 15;
                    break;
                default:
                    player.hp = 0;
                    player.attack = 0;
                    break;
            }
            Console.WriteLine($"HP{player.hp} Attack{player.attack}");
        }
        static void CreateRandomMonster(out Monster monster)
        {
            Random rand = new Random();
            int randMonster = rand.Next(1, 4);    // 1~3
            switch (randMonster)
            {
                case (int)MonsterType.slime:
                    Console.WriteLine("슬라임이 스폰되었습니다.");
                    monster.hp = 20;
                    monster.attack = 2;
                    break;
                case (int)MonsterType.orc:
                    Console.WriteLine("오크가 스폰되었습니다.");
                    monster.hp = 40;
                    monster.attack = 4;
                    break;
                case (int)MonsterType.skeleton:
                    Console.WriteLine("스켈레톤이 스폰되었습니다.");
                    monster.hp = 30;
                    monster.attack = 3;
                    break;
                default:
                    monster.hp = 0;
                    monster.attack = 0;
                    break;
            }
        }
        static void Fight(ref Player player, ref Monster monster)
        {
            while (true)
            {
                monster.hp -= player.attack;
                if (monster.hp <= 0)
                {
                    Console.WriteLine("승리했습니다!");
                    Console.WriteLine($"남은 체력 {player.hp}");
                    break;
                }

                player.hp -= monster.attack;
                if (player.hp <= 0)
                {
                    Console.WriteLine("패배했습니다!");
                }
            }
        }
        static void EnterField(ref Player player)
        {
            while (true)
            {
                Console.WriteLine("필드에 입장했습니다!");

                Monster monster;
                CreateRandomMonster(out monster);

                Console.WriteLine("[1] 전투 모드로 돌입");
                Console.WriteLine("[2] 일정 확률로 마을로 도망");

                string input = Console.ReadLine();
                switch (input)
                {
                    case "1":
                        Fight(ref player, ref monster);
                        break;
                    case "2":
                        Random rand = new Random();
                        int randValue = rand.Next(1, 101);
                        if (randValue <= 33)
                        {
                            Console.WriteLine("도망치는 데 성공했습니다!");
                            return;
                        }
                        else
                        {
                            Console.WriteLine("도망치는 데 실패했습니다!");
                            Fight(ref player, ref monster);
                        }
                        break;
                }
            }


        }
        static void EnterGame(ref Player player)
        {
            while (true)
            {
                Console.WriteLine("마을에 입장했습니다!");
                Console.WriteLine("[1] 필드로 간다");
                Console.WriteLine("[2] 로비로 돌아가기");

                string input = Console.ReadLine();
                switch (input)
                {
                    case "1":
                        EnterField(ref player);
                        break;
                    case "2":
                        return;
                    default:
                        Console.WriteLine("잘못된 입력입니다. 다시 입력해주세요.");
                        break;
                }
            }
        }
        static void Main(string[] args)
        {
            while (true)
            {
                Player player;
                player.hp = 0;
                player.attack = 0;
                player.classType = ClassType.none;

                ChoiceCharacter(ref player);
                CreatePlayer(ref player);

                // 필드에서 몬스터와 싸움
                EnterGame(ref player);
            }
        }
    }
}
