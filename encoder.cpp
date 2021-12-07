#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include "encoder.h"
#include "heap.h"
void Encoder::Init()
{
	memset(Cnt, 0, sizeof(Cnt));
	memset(Son, 0, sizeof(Son));
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
		if(OutputType == 0)fwrite(&Last, 1, 1, OutFile);
		else 
		{
			int Temp = Last;
			for(int i = 7 ; i >= 0; i--)fprintf(OutFile, "%d", (Temp >> i) % 2);
			fprintf(OutFile, " ");
		}
		Last = x % (1 << TmpLen);
		LastLen = TmpLen;
	}
}
void Encoder::ForcePrint()
{
	if(LastLen == 0) return;
	Last <<= 8 - LastLen;
	if(OutputType == 0)fwrite(&Last, 1, 1, OutFile);
	else
	{
		int Temp = Last;
		for(int i = 7 ; i >= 0; i--)fprintf(OutFile, "%d", (Temp >> i) % 2);
		fprintf(OutFile, " ");
	}
	Last = LastLen = 0;
}
void Encoder::GetCode(int x)
{
	int HasSon = Son[x][0] != 0;
	Print(HasSon, 1);
	if(HasSon)
	{
		CodeLen[Son[x][0]] = CodeLen[x] + 1;
		Code[Son[x][0]] = Code[x] << 1;
		GetCode(Son[x][0]);
		CodeLen[Son[x][1]] = CodeLen[x] + 1;
		Code[Son[x][1]] = (Code[x] << 1) + 1;
		GetCode(Son[x][1]);
	}
}
void Encoder::PrintVal(int x)
{
	int HasSon = Son[x][0] != 0;
	if(HasSon)
	{
		PrintVal(Son[x][0]);
		PrintVal(Son[x][1]);
	} else
	{
		Print(x, 8);
		//if(OutputType == 0)fwrite(&x, 1, 1, OutFile);
		//else 	
	}
}
bool Encoder::Encode(FILE *fin,FILE *fout, bool InTy, bool OuTy){
	OutFile = fout/*stderr*/;
	OutputType = OuTy;
	Init();
	while(!feof(fin))
	{
		unsigned char Cx;int Ix;
		if(InTy == 0)
			if(fread(&Cx, 1, 1, fin) > 0)
			{
				Cnt[Cx]++;
				FileSize++;
			} else break;
		else 
			if(fread(&Cx, 1, 1, fin) > 0)
			{
				Cnt[Cx]++;
				FileSize++;
			} else break;
	}
	if(OutputType == 0)
		fwrite(&FileSize, 8, 1, OutFile);
	else
	{
		long long Temp = FileSize;
		for(int i = 0; i < 8; i++)
		{
			for(int j = 7;j >= 0; j--)fprintf(OutFile, "%d", (Temp >> j) % 2);
			Temp >>= 8;
			fprintf(OutFile, " "); 
		}
	}		
	Heap Hp;
	int NodeCount = 0;
	for(int i = 0; i < 256; i++)
		if(Cnt[i] != 0)
		{
			Hp.Push(Cnt[i], i);
			NodeCount ++;
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
	
	int TreeSize = (2 * NodeCount - 1) / 8 + 1;
	if(OutputType == 0)
		fwrite(&TreeSize, 1, 1, OutFile);
	else 
	{
		for(int i = 7;i >= 0; i--)fprintf(OutFile, "%d", (TreeSize >> i) % 2);
		fprintf(OutFile, " ");
	}
		
	GetCode(N - 1);
	ForcePrint();
	PrintVal(N - 1);
/*	fprintf(OutFile,"\n");
	fprintf(OutFile,"begin:\n");
	for(int i=0;i<256;i++)if(Cnt[i])
	{
		fprintf(OutFile,"%c:",char(i));
		for(int j=CodeLen[i]-1;j>=0;j--)fprintf(OutFile, "%d",(Code[i]>>j)%2);
		fprintf(OutFile,"\n");
	}
	fprintf(OutFile,"end:\n");
*/	
	fseek(fin, 0, SEEK_SET);
	for(int i = 0; i < FileSize; i++)
	{
		unsigned char Cx;
		int Temp;
		if(InTy == 0)
		{
			fread(&Cx, 1, 1, fin);
			Temp = Cx;
		}
		else
		{
			fread(&Cx, 1, 1, fin);
			Temp = Cx;
		}
		if(CodeLen[Temp] > 8)
		{
			Print(Code[Temp] >> 8, CodeLen[Temp] - 8);
			Print(Code[Temp] % (1 << 8), 8);
		} else Print(Code[Temp], CodeLen[Temp]);
	}
	ForcePrint();
	fclose(fin);
	fclose(fout);
	return true;
}
