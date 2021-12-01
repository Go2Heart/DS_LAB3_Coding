#include "encoder.h"
#include "heap.h"
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
void Encoder::Init()
{
	memset(Cnt, 0, sizeof(Cnt));
	memset(Son, 0, sizeof(Son));
	Text.clear();
	Last = LastLen = N = FileSize = 0;
}
void Encoder::Print(int x, int y)
{
	if(y + LastLen < 8)
	{
		Last = (Last << y) + x;
		LastLen +=y;
	}
	else 
	{
		int TmpLen = y - (8 - LastLen);
		Last = (Last << 8 - LastLen) + (x >> TmpLen);
		fwrite(&Last, 1, 1, OutFile);
		Last = x % (1 << TmpLen);
		LastLen = TmpLen;
	}
}
void Encoder::ForcePrint()
{
	if(LastLen == 0) return;
	Last <<= 8 - LastLen;
	fwrite(&Last, 1, 1, OutFile);
	Last = LastLen = 0;
}
void Encoder::GetCode(int x)
{
	Print(Son[x][0] * 2 + Son[x][1], 2);
	if(Son[x][0])
	{
		CodeLen[Son[x][0]] = CodeLen[x] + 1;
		Code[Son[x][0]] = Code[Son[x][0]] << 1;
		GetCode(Son[x][0]);
	}
	if(Son[x][1])
	{
		CodeLen[Son[x][1]] = CodeLen[x] + 1;
		Code[Son[x][1]] = (Code[Son[x][1]] << 1) + 1;
		GetCode(Son[x][1]);
	}
}
bool Encoder::Encode(FILE *fin,FILE *fout){
	int x;
	OutFile = fout;
	Init();
	while(1)
	{
		if(fread(&x, 1, 1, fin) > 0)
		{
			Cnt[x]++;
			FileSize++;
			Text.push_back((char)x);
		} else break;
	}
	fwrite(&FileSize, 8, 1, OutFile);//?
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
	Code[N - 1] = CodeLen[N - 1] = 0;
	GetCode(N - 1);
	for(int i = 0; i < FileSize; i++)
	{
		int Temp = (int)Text[i];
		Print(Code[Temp], CodeLen[Temp]);
	}
	ForcePrint();
	return true;
}