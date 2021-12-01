#include "encoder.h"
#include "heap.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
void Encoder::Print(int x, int y)
{
	if(y + LastLen < 8)
	{
		Last = (Last << y) + x;
		LastLen +=y;
	}
	else 
	{
		Last = (Last << 8 - LastLen) + (x >> LastLen);
		fwrite(&Last, 1, 1, OutFile);
		Last = x % (1 << 8 - LastLen);
		LastLen = y - 8 + LastLen;
	}
}
void Encoder::ForcePrint()
{
	Last <<= 8 - LastLen;
	fwrite(&Last, 1, 1, OutFile);
	Last = LastLen = 0;
}
bool Encoder::Encode(FILE *fin,FILE *fout){
	int x;
	OutFile = fout;
	memset(Cnt, 0, sizeof(Cnt));
	memset(Son, 0 ,sizeof(Son));
	while(1)
	{
		if(fread(&x, 1, 1, fin) > 0)
		{
			Cnt[x]++;	
			FileSize++;
		} else break;
	}
	Heap Hp;
	for(int i = 0; i < 256; i++)
	{
		if(Cnt[i] != 0) Hp.Push(Cnt[i], i);	
	}
	N = 256;
	while(Hp.Size() > 1)
	{
		HeapNode Tmp1, Tmp2;
		Hp.Pop(Tmp1); Hp.Pop(Tmp2);
		Son[N][0] = Tmp1.Id, Son[N][1] = Tmp2.Id;
		Hp.Push(Tmp1.Val + Tmp2.Val, N);
		++N;
	}
	
}