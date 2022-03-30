#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <windows.h>

using namespace std;

void ColorSet(int backColor, int textColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (backColor << 4) + textColor);
}

struct Int2D
{
	int X, Y;

	bool operator==(const Int2D& rhs) const {
		return this->X == rhs.X && this->Y == rhs.Y;
	}
};

const Int2D InvalidCoordinate = Int2D{ -1, -1 };
const Int2D ZeroCoordinate = Int2D{ 0, 0 };

class InvenItem
{
public:
	int GetItemID() { return ItemID; }
	char GetDisplayID() { return 'a' + ItemID - 1; }
	Int2D GetItemSize() { return ItemSize; }
private:
	int ItemID;
	Int2D ItemSize = ZeroCoordinate;

private:
	InvenItem() {}
public:
	InvenItem(int id, Int2D size) : ItemID(id), ItemSize(size) {}
};

class InvenSlot
{
public:
	InvenItem* ItemPtr = nullptr;
	InvenSlot* LTSlot = nullptr;
	Int2D SlotCoord;
};


class Inventory
{
public:
	Inventory()
	{
		for (int x = 0; x < InvenSize.X; ++x)
		{
			vector<InvenSlot*> v;
			for (int y = 0; y < InvenSize.Y; ++y)
			{
				auto Slot = new InvenSlot();
				Slot->SlotCoord = Int2D{ x, y };
				v.push_back(Slot);
			}

			InventorySlotDatas.push_back(v);
		}
	}
	~Inventory()
	{

		for (int x = 0; x < InvenSize.X; ++x)
		{
			for (int y = 0; y < InvenSize.Y; ++y)
			{
				delete InventorySlotDatas[x][y];
			}
			InventorySlotDatas[x].clear();
		}
		InventorySlotDatas.clear();
	}

	void DisplayInventory()
	{
		for (int y = 0; y < InvenSize.Y; ++y)
		{
			for (int x = 0; x < InvenSize.X; ++x)
			{
				if (auto pItem = InventorySlotDatas[x][y]->ItemPtr)
				{
					ColorSet(pItem->GetItemID(), 0);
					cout << "" << pItem->GetDisplayID() << " ";
					ColorSet(0, 7);
				}
				else
				{
					ColorSet(0, 7);
					cout << "" << "0" << " ";
				}
			}
			cout << endl;
		}

		if (PickupItem)
		{
			ColorSet(0, PickupItem->GetItemID());
			cout << "Your PickUped Item " << PickupItem->GetDisplayID() << " " << endl;
			ColorSet(0, 7);
		}
		cout << endl;

	}


	void AddItem(InvenItem* Item)
	{
		Int2D FirstSlotCoord = FirstEmptySpaceSlotCoord(Item->GetItemSize());
		if (FirstSlotCoord == InvalidCoordinate)
		{
			printf("Fail Add Item (id = %c Size= %dx%d)\n", Item->GetDisplayID(), Item->GetItemSize().X, Item->GetItemSize().Y);
		}
		else
		{
			printf("Success Add Item (id = %c Size= %dx%d)\n", Item->GetDisplayID(), Item->GetItemSize().X, Item->GetItemSize().Y);
			SetSlotItem(FirstSlotCoord, Item->GetItemSize(), Item);
		}
		DisplayInventory();
	}
	void RemoveItem(InvenItem* Item)
	{
		printf("Success Remove Item (id = %c Size= %dx%d)\n", Item->GetDisplayID(), Item->GetItemSize().X, Item->GetItemSize().Y);
		SetSlotItem(GetLTSlot(Item)->SlotCoord, Item->GetItemSize(), nullptr);
		RemoveIndexingItem(Item);
		DisplayInventory();
	}
	void RemoveItem(int id)
	{
		InvenItem* Item = nullptr;
		for (auto iter : ItemIndexingDatas)
		{
			if (iter.first->GetItemID() == id)
			{
				Item = iter.first;
			}
		}

		if (Item)
		{
			RemoveItem(Item);
		}
	}


	void PickSlot(Int2D PickSlotCoord)
	{
		if (PickSlotCoord.X < 0 || PickSlotCoord.X > InvenSize.X - 1)
			return;

		if (PickSlotCoord.Y < 0 || PickSlotCoord.Y > InvenSize.Y - 1)
			return;


		if (PickupItem)
		{
			vector<InvenItem*> OverlappedItems;
			CheckSpace(PickSlotCoord, PickupItem->GetItemSize(), OverlappedItems);

			if (OverlappedItems.size() > 1)
			{
				return;
			}
			else if (OverlappedItems.size() == 1)
			{
				printf("------------ Begin Swap// id = %c , id = %c ------------ \n", PickupItem->GetDisplayID(), OverlappedItems[0]->GetDisplayID());
				RemoveItem(OverlappedItems[0]);
				printf("Setted Item (id = %c Size= %dx%d)\n", PickupItem->GetDisplayID(), PickupItem->GetItemSize().X, PickupItem->GetItemSize().Y);
				SetSlotItem(PickSlotCoord, PickupItem->GetItemSize(), PickupItem);
				PickupItem = OverlappedItems[0];
				printf("Pickup Item (id = %c Size= %dx%d)\n", PickupItem->GetDisplayID(), PickupItem->GetItemSize().X, PickupItem->GetItemSize().Y);
				DisplayInventory();
				printf("------------- End Swap// id = %c , id = %c ------------- \n", PickupItem->GetDisplayID(), OverlappedItems[0]->GetDisplayID());
			}
			else
			{
				printf("Setted Item (id = %c Size= %dx%d)\n", PickupItem->GetDisplayID(), PickupItem->GetItemSize().X, PickupItem->GetItemSize().Y);
				SetSlotItem(PickSlotCoord, PickupItem->GetItemSize(), PickupItem);
				PickupItem = nullptr;
				DisplayInventory();
			}
		}
		else
		{
			auto Slot = InventorySlotDatas[PickSlotCoord.X][PickSlotCoord.Y];

			if (Slot->ItemPtr)
			{
				printf("Pickup Item (id = %c Size= %dx%d)\n", Slot->ItemPtr->GetDisplayID(), Slot->ItemPtr->GetItemSize().X, Slot->ItemPtr->GetItemSize().Y);
				PickupItem = Slot->ItemPtr;
				RemoveItem(Slot->ItemPtr);

			}
		}
	}
private:
	bool CheckSpace(Int2D StartCoord, Int2D CheckSize, vector<InvenItem*>& OverlappedItems)
	{
		bool EnoughSpace = true;
		for (int y = 0; y < CheckSize.Y; ++y)
		{
			if (StartCoord.Y + y >= InvenSize.Y)
			{
				EnoughSpace = false;
				continue;
			}

			for (int x = 0; x < CheckSize.X; ++x)
			{
				if (StartCoord.X + x >= InvenSize.X)
				{
					EnoughSpace = false;
					continue;
				}

				if (InvenItem* Item = InventorySlotDatas[StartCoord.X + x][StartCoord.Y + y]->ItemPtr)
				{
					EnoughSpace = false;
					auto it = find(OverlappedItems.begin(), OverlappedItems.end(), Item);
					if (it == OverlappedItems.end()) {
						OverlappedItems.push_back(Item);
					}
				}
			}
		}

		return EnoughSpace;
	}

	Int2D FirstEmptySpaceSlotCoord(Int2D CheckSize)
	{
		for (int y = 0; y < InvenSize.Y; ++y)
		{
			for (int x = 0; x < InvenSize.X; ++x)
			{
				vector<InvenItem*> OverlappedItems;
				if (CheckSpace(Int2D{ x, y }, CheckSize, OverlappedItems))
				{
					return Int2D{ x, y };
				}
			}
		}
		return InvalidCoordinate;
	}

	void SetSlotItem(Int2D FirstSlotCoord, Int2D Size, InvenItem* Item)
	{
		for (int y = 0; y < Size.Y; ++y)
		{
			for (int x = 0; x < Size.X; ++x)
			{
				auto Slot = InventorySlotDatas[FirstSlotCoord.X + x][FirstSlotCoord.Y + y];
				Slot->ItemPtr = Item;
				Slot->LTSlot = Item ? InventorySlotDatas[FirstSlotCoord.X][FirstSlotCoord.Y] : nullptr;

				AddIndexingItem(Item, Slot);
			}
		}
	}

	void AddIndexingItem(InvenItem* Item, InvenSlot* Slot)
	{
		if (Item == nullptr)
			return;

		if (ItemIndexingDatas.find(Item) != ItemIndexingDatas.end())
		{
			ItemIndexingDatas[Item].push_back(Slot);
		}
		else
		{
			vector<InvenSlot*> v;
			v.push_back(Slot);
			ItemIndexingDatas.insert(pair<InvenItem*, vector<InvenSlot*>>(Item, v));
		}
	}
	void RemoveIndexingItem(InvenItem* Item)
	{
		if (ItemIndexingDatas.find(Item) != ItemIndexingDatas.end())
		{
			for (auto Slot : ItemIndexingDatas[Item])
			{
				Slot->ItemPtr = nullptr;
			}

			ItemIndexingDatas.erase(Item);
		}
	}

	InvenSlot* GetLTSlot(InvenItem* Item)
	{
		if (ItemIndexingDatas.find(Item) != ItemIndexingDatas.end() && ItemIndexingDatas[Item].size())
		{
			return ItemIndexingDatas[Item][0]->LTSlot;
		}
	}

private:
	InvenItem* PickupItem;
	Int2D InvenSize{ 10,4 };
	vector<vector<InvenSlot*>> InventorySlotDatas;
	map<InvenItem*, vector<InvenSlot*>> ItemIndexingDatas;
};


class LocalDB
{
public:
	InvenItem* CreateItem(int id, Int2D size)
	{
		InvenItem* newItem = new InvenItem(id, size);
		ItemDB.push_back(newItem);
		return newItem;
	}

	~LocalDB()
	{
		for (auto item : ItemDB)
		{
			delete item;
		}
		ItemDB.clear();
	}
private:
	vector<InvenItem*> ItemDB;
};

int main()
{
	LocalDB DB;
	Inventory inven;

	inven.AddItem(DB.CreateItem(1, Int2D{ 3,3 }));
	inven.AddItem(DB.CreateItem(2, Int2D{ 1,1 }));
	inven.AddItem(DB.CreateItem(3, Int2D{ 1,1 }));
	inven.AddItem(DB.CreateItem(4, Int2D{ 3,3 }));
	inven.AddItem(DB.CreateItem(5, Int2D{ 1,4 }));
	inven.AddItem(DB.CreateItem(6, Int2D{ 1,3 }));
	inven.AddItem(DB.CreateItem(7, Int2D{ 2,2 }));
	inven.AddItem(DB.CreateItem(8, Int2D{ 2,2 }));
	inven.RemoveItem(4);
	inven.AddItem(DB.CreateItem(9, Int2D{ 3,2 }));
	inven.AddItem(DB.CreateItem(10, Int2D{ 2,2 }));
	inven.AddItem(DB.CreateItem(11, Int2D{ 2,1 }));
	inven.AddItem(DB.CreateItem(12, Int2D{ 2,3 }));
	inven.AddItem(DB.CreateItem(13, Int2D{ 3,1 }));

	return 0;
}