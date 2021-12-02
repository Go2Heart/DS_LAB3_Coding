#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "encoder.h"
#include "decoder.h"
#include "heap.h"
using namespace std;
int main()
{
	while(1)
	{
		int ty, Ty1, Ty2;char s[105], t[105];
		printf("please input mode: 0(encode) 1(decode) -1(exit):");
		scanf("%d", &ty);
		printf("please announce type and name of the file: 0(binary)/1(txt) filename\n");
		printf("input file:");
		scanf("%d%s", &Ty1, s);
		printf("output file:");
		scanf("%d%s", &Ty2, t);
		FILE *fin, *fout;
		if(ty == 0)
		{	
			if(Ty1) fin = fopen(s, "r");
			else fin = fopen(s, "rb");
			if(Ty2) fout = fopen(t, "w")/*stderr*/;
			else fout = fopen(t,"wb");
			Encoder EncodeSolver;
			EncodeSolver.Encode(fin, fout, Ty1, Ty2);
		} else if(ty == 1)
		{
			if(Ty1) fin = fopen(s, "r");
			else fin = fopen(s, "rb");
			if(Ty2) fout = fopen(t, "w")/*stderr*/;
			else fout = fopen(t,"wb");
			Decoder DecodeSolver;
			DecodeSolver.Decode(fin, fout, Ty1, Ty2);
		} else if (ty == -1) break;
	}
	
}
