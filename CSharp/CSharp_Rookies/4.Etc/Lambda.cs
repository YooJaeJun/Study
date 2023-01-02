using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp._4.Etc
{
    enum ItemType
    {
        Weapon,
        Armor,
        Amulet,
        Ring
    }
    enum Rarity
    {
        Normal,
        Uncommon,
        Rare,
    }
    class Item
    {
        public ItemType ItemType;
        public Rarity Rarity;
    }
    class Lambda
    {
        static List<Item> _items = new List<Item>();
        delegate Return MyFunc<Return>();
        delegate Return MyFunc<T, Return>(T item);
        delegate Return MyFunc<T1, T2, Return>(T1 t1, T2 t2);
        static Item FindItem(MyFunc<Item, bool> selector)
        {
            foreach (Item item in _items)
            {
                if (selector(item))
                    return item;
            }
            return null;
        }
        static void Main(string[] args)
        {
            // Lambda : 일회용 함수를 만드는 데 사용하는 문법.
            _items.Add(new Item() { ItemType = ItemType.Weapon, Rarity = Rarity.Normal });
            _items.Add(new Item() { ItemType = ItemType.Armor, Rarity = Rarity.Uncommon });
            _items.Add(new Item() { ItemType = ItemType.Ring, Rarity = Rarity.Rare });

            // Anonymous Function : 무명 함수 / 익명 함수
            Item item = FindItem(delegate (Item item) { return item.ItemType == ItemType.Weapon; });

            // 람다
            Item item2 = FindItem((Item item) => { return item.ItemType == ItemType.Weapon; });

            // delegate 객체로 만들기 + 람다
            // MyFunc selector = new MyFunc((Item item) => { return item.ItemType == ItemType.Weapon; });
            // new ~ 없어도 동작
            MyFunc<Item, bool> selector = (Item item) => { return item.ItemType == ItemType.Weapon; };
            Item item3 = FindItem(selector);

            // delegate를 직접 선언하지 않아도, 이미 만들어진 애들이 존재한다.
            // -> 반환 타입이 있으면 Func
            // -> 반환 타입이 없으면 Action

            Func<Item, bool> selector2 = (Item item) => { return item.ItemType == ItemType.Weapon; };
        }
    }
}
