#include "heap.h"
bool HeapNode::operator <(const HeapNode &x)
{
	return Val < x.Val;
}
HeapNode &HeapNode::operator =(const HeapNode &x)
{
	Val = x.Val; Id = x.Id;
	return *this;
}
bool Heap::Push(int x, int y)
{
	Obj[Sz].Val = x; Obj[Sz].Id = y;
	int Cur = Sz;
	++Sz;
	while(Cur > 0)
	{
		int Parent = (Cur - 1)/2;
		if(Obj[Cur] < Obj[Parent])
		{
			HeapNode Temp = Obj[Parent];
			Obj[Parent] = Obj[Cur];
			Obj[Cur] = Temp;
			Cur = Parent;
		} else break;
	}
	return true;
}
bool Heap::Pop(HeapNode &x)
{
	if(Sz < 0) return false;
	--Sz;
	Obj[0] = Obj[Sz];
	int Cur = 0;
	while(Cur < Sz)
	{
		int Left = 2 * Cur + 1, Right = 2 * Cur + 2;
		if(Left >= Sz) break;
		int Max = Left;
		if(Right < Sz && Obj[Right] < Obj[Left]) Max = Right;
		if(Obj[Max] < Obj[Cur])
		{
			HeapNode Temp = Obj[Max];
			Obj[Max] = Obj[Cur];
			Obj[Cur] = Temp;
		} else break;
	}
}
int Heap::Size()
{
	return Sz;
}