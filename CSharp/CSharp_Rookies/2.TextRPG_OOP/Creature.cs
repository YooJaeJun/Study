using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp
{
    public enum CreatureType
    {
        none,
        player,
        monster
    }

    class Creature
    {
        CreatureType type = CreatureType.none;
        protected int hp = 0;
        protected int attack = 0;
        protected Creature(CreatureType type)
        {
            this.type = type;
        }
        public void SetInfo(int hp, int attack)
        {
            this.hp = hp;
            this.attack = attack;
        }
        public CreatureType GetCreatureType() { return type; }
        public int GetHp() { return hp; }
        public int GetAttack() { return attack; }
        public bool IsDead() { return hp <= 0; }
        public void OnDamaged(int damage)
        {
            hp -= damage;
            if (hp < 0)
                hp = 0;
        }
    }
}
