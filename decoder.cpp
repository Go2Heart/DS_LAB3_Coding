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
bool Decoder::Read(int &x)
{
	// if(feof(InFile)) return false;
	if(LastLen == 0)
	{
		if(InputType == 1)
		{
			unsigned char Temp; Last = 0;
			for(int i = 0; i < 8; i++)
			{
				if(feof(InFile)) return false;
				fscanf(InFile, "%c", &Temp);
				Last = (Last << 1) + Temp - '0';
			}
			// if(feof(InFile)) return false;
			fscanf(InFile, "%c", &Temp);
		}
		else
		{
			if(feof(InFile)) return false;
			fread(&Last, 1, 1, InFile);
		}
		LastLen = 7;
	}else LastLen--;
	x =  (Last >> LastLen) % 2;
	return true;
}
void Decoder::ForceRead()
{
	Last = LastLen = 0;
}
bool Decoder::BuildTree(int &x)
{
	x = N; ++N;
	int HasSon;
	if(!Read(HasSon))
		return false;
	if(HasSon)
	{
		if(!BuildTree(Son[x][0]))
			return false;
		if(!BuildTree(Son[x][1]))
			return false;
	}
	return true;
}
bool Decoder::InsertVal(int x)
{
	int HasSon = Son[x][0] != 0;
	if(HasSon)
	{
		if(!InsertVal(Son[x][0]))
			return false;
		if(!InsertVal(Son[x][1]))
			return false;
	} else
	{
		unsigned char Temp;
		if(InputType == 1)
		{
			unsigned char Tmp;
			for(int i = 0; i < 8; i++)
			{
				if(feof(InFile)) return false;
				fscanf(InFile, "%c", &Tmp);
				Temp = (Temp << 1) + Tmp - '0';
			}
			if(feof(InFile)) return false;
			fscanf(InFile, "%c", &Tmp);
		}
		else
		{
			if(feof(InFile)) return false;
			fread(&Temp, 1, 1, InFile);
		}
		Code[x] = Temp;
	}
	return true;
}
bool Decoder::Decoding(int x)
{
	if(Son[x][0] == 0)
	{
		if(OutputType == 0)
			fwrite(&Code[x], 1, 1, OutFile);
		else
			fprintf(OutFile, "%c", Code[x]);
		return true;
	}
	int Temp;
	if(!Read(Temp))
		return false;
	bool Flag = true;
	if(Temp == 0) Flag &= Decoding(Son[x][0]);
	else Flag &= Decoding(Son[x][1]);
	return Flag;
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
				if(feof(InFile)) return false;
				fscanf(fin, "%c", &Temp);
				Nownum = (Nownum << 1) + Temp - '0';
			}
			if(feof(InFile)) return false;
			fscanf(fin, "%c", &Temp);
			FileSize += bit * Nownum;
			bit = bit * 256;
		}
		for(int i = 0; i < 8; i++)
		{
			if(feof(InFile)) return false;
			fscanf(fin, "%c", &Temp);
		}
		if(feof(InFile)) return false;
		fscanf(fin, "%c", &Temp);
	} else 
	{
		if(feof(InFile)) return false;
		fread(&FileSize, 8, 1, fin);
		unsigned char Temp;
		if(feof(InFile)) return false;
		fread(&Temp, 1, 1,fin);
	}
	if(!BuildTree(Root))
		return false;
	ForceRead();
	if(!InsertVal(Root))
		return false;
	for(int i = 0; i < FileSize; i++)
	{
		if(!Decoding(Root))
			return false;
	}
	fclose(fin);
	fclose(fout);
	return true;
}
