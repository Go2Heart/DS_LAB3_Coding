struct HeapNode
{
	int Val,Id;
	bool operator <(const HeapNode &x);
    HeapNode &operator =(const HeapNode &x);
};
struct Heap
{
	HeapNode Obj[256];
    int Sz = 0;
    bool Push(int x, int y);
    bool Pop(HeapNode &x);
    int Size();
};