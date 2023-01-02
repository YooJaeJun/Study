using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp
{
    public enum PlayerType
    {
        none,
        knight,
        archer,
        mage
    }
    class Player : Creature
    {
        protected PlayerType type = PlayerType.none;

        protected Player(PlayerType type) : base(CreatureType.player)
        {
            this.type = type;
        }
        public PlayerType GetPlayerType() { return type; }
    }
    class Knight : Player
    {
        public Knight() : base(PlayerType.knight)
        {
            SetInfo(100, 10);
        }
    }
    class Archer : Player
    {
        public Archer() : base(PlayerType.archer)
        {
            SetInfo(75, 12);
        }
    }
    class Mage : Player
    {
        public Mage() : base(PlayerType.mage)
        {
            SetInfo(50, 15);
        }
    }
}
