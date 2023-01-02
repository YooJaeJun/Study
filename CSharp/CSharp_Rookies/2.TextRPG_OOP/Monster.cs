using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp
{
    public enum MonsterType
    {
        none,
        slime,
        orc,
        skeleton
    }
    class Monster : Creature
    {
        protected MonsterType type;
        protected Monster(MonsterType type) : base(CreatureType.monster)
        {
            this.type = type;
        }

        MonsterType GetMonsterType() { return type; }
    }

    class Slime : Monster
    {
        public Slime() : base(MonsterType.slime)
        {
            SetInfo(20, 1);
        }
    }
    class Orc : Monster
    {
        public Orc() : base(MonsterType.orc)
        {
            SetInfo(40, 2);
        }
    }
    class Skeleton : Monster
    {
        public Skeleton() : base(MonsterType.skeleton)
        {
            SetInfo(30, 5);
        }
    }
}
