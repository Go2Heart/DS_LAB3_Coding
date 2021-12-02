#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include "decoder.h"
#include "heap.h"
void Decoder::Init()
{
	memset(Son, 0, sizeof(Son));
	LastLen = Last = N = 0;
}
int Decoder::Read()
{
	if(LastLen == 0)
	{
		if(InputType == 1)
		{
			unsigned char Temp; Last = 0;
			for(int i = 0; i < 8; i++)
			{
				fscanf(InFile, "%c", &Temp);
				Last = (Last << 1) + Temp - '0';	
			}
		}
		else fread(&Last, 1, 1, InFile);
		LastLen = 7;
	}else LastLen--;
	return (Last >> LastLen) % 2;
}
void Decoder::ForceRead()
{
	Last = LastLen = 0;
}
void Decoder::BuildTree(int &x)
{
	x = N; ++N;
	int HasSon = Read();
	if(HasSon)
	{
		BuildTree(Son[x][0]);
		BuildTree(Son[x][1]);
	}
}
void Decoder::InsertVal(int x)
{
	int HasSon = Son[x][0] != 0;
	if(HasSon)
	{
		InsertVal(Son[x][0]);
		InsertVal(Son[x][1]);
	} else 
	{
		unsigned char Temp;
		if(InputType == 1)
		{
			unsigned char Tmp;
			for(int i = 0; i < 8; i++)
			{
				fscanf(InFile, "%c", &Tmp);
				Temp = (Temp << 1) + Tmp - '0';	
			}
		}
		else fread(&Temp, 1, 1, InFile);
		Code[x] = Temp;
	}
}
void Decoder::Decoding(int x)
{
	if(Son[x][0] == 0)
	{
		if(OutputType == 0)
			fwrite(&Code[x], 1, 1, OutFile);
		else
			fprintf(OutFile, "%c", Code[x]);
		return;
	}
	int Temp = Read();
	if(Temp == 0)Decoding(Son[x][0]);
	else Decoding(Son[x][1]);
}
bool Decoder::Decode(FILE *fin,FILE *fout, bool InTy, bool OuTy){
	InFile = fin; OutFile = fout;
	InputType = InTy; OutputType = OuTy;
	Init();
	if(InputType == 1)
	{
		FileSize = 0;
		long long bit = 1;
		unsigned char Temp;
		for(int i = 0; i < 8; i++)
		{
			int Nownum = 0;
			for(int j = 0; j < 8; j++)
			{
				fscanf(fin, "%c", &Temp);
				Nownum = (Nownum << 1) + Temp - '0';
			}
			FileSize += bit * Nownum;
			bit = bit * 256;
		}
		for(int i = 0; i < 8; i++)fscanf(fin, "%c", &Temp);
	} else 
	{
		fread(&FileSize, 8, 1, fin);
		unsigned char Temp;
		fread(&Temp, 1, 1,fin);
	}
	BuildTree(Root);
	ForceRead();
	InsertVal(Root);
	for(int i = 0; i < FileSize; i++)
	{
		Decoding(Root);
	}
	fclose(fin);
	fclose(fout);
	return true;
}
