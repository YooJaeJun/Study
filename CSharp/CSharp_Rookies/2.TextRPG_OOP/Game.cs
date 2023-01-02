using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp
{
    public enum GameMode
    {
        none,
        lobby,
        town,
        field
    }
    class Game
    {
        private GameMode mode = GameMode.lobby;
        private Player player = null;
        private Monster monster = null;
        private Random rand = new Random();
        public void Process()
        {
            switch(mode)
            {
                case GameMode.lobby:
                    ProcessLobby();
                    break;
                case GameMode.town:
                    ProcessTown();
                    break;
                case GameMode.field:
                    ProcessField();
                    break;
            }
        }
        public void ProcessLobby()
        {
            Console.WriteLine("직업을 선택하세요");
            Console.WriteLine("[1] 기사");
            Console.WriteLine("[2] 궁수");
            Console.WriteLine("[3] 법사");

            string input = Console.ReadLine();
            switch(input)
            {
                case "1":
                    player = new Knight();
                    mode = GameMode.town;
                    Console.WriteLine("[1] 기사 선택");
                    break;
                case "2":
                    player = new Archer();
                    mode = GameMode.town;
                    Console.WriteLine("[2] 궁수 선택");
                    break;
                case "3":
                    player = new Mage();
                    mode = GameMode.town;
                    Console.WriteLine("[3] 법사 선택");
                    break;
            }
        }
        public void ProcessTown()
        {
            Console.WriteLine("마을에 입장했습니다.");
            Console.WriteLine("[1] 필드로 가기");
            Console.WriteLine("[2] 로비로 돌아가기");

            string input = Console.ReadLine();
            switch (input)
            {
                case "1":
                    mode = GameMode.field;
                    Console.WriteLine("[1] 필드로 이동합니다.");
                    break;
                case "2":
                    player = new Archer();
                    mode = GameMode.lobby;
                    Console.WriteLine("[2] 로비로 이동합니다.");
                    break;
            }
        }
        public void ProcessField()
        {
            Console.WriteLine("필드에 입장했습니다.");

            CreateRandomMonster();

            Console.WriteLine("[1] 싸우기");
            Console.WriteLine("[2] 일정 확률로 마을 돌아가기");

            string input = Console.ReadLine();
            switch (input)
            {
                case "1":
                    Console.WriteLine("[1] 싸움을 시작합니다.");
                    ProcessFight();
                    break;
                case "2":
                    TryEscape();
                    break;
            }
        }
        public void ProcessFight()
        {
            while(true)
            {
                int damage = player.GetAttack();
                monster.OnDamaged(damage);
                if (monster.IsDead())
                {
                    Console.WriteLine("승리!");
                    Console.WriteLine($"남은 체력 {player.GetHp()}");
                    break;
                }

                damage = monster.GetAttack();
                player.OnDamaged(damage);
                if (player.IsDead())
                {
                    Console.WriteLine("패배!");
                    Console.WriteLine("로비로 이동합니다");
                    mode = GameMode.lobby;
                    break;
                }
            }
        }
        private void CreateRandomMonster()
        {
            int randValue = rand.Next(0, 3);
            switch (randValue)
            {
                case 0:
                    monster = new Slime();
                    Console.WriteLine("슬라임이 나타났습니다.");
                    break;
                case 1:
                    monster = new Orc();
                    Console.WriteLine("오크가 나타났습니다.");
                    break;
                case 2:
                    monster = new Skeleton();
                    Console.WriteLine("스켈레톤 나타났습니다.");
                    break;
            }
        }
        private void TryEscape()
        {
            int randValue = rand.Next(0, 101);
            if (randValue < 33)
            {
                mode = GameMode.town;
                Console.WriteLine("도망 성공!");
            }
            else
            {
                Console.WriteLine("도망 실패! 싸움을 지속합니다.");
                ProcessFight();
            }
        }
    }
}
