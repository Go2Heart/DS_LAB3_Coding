#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "encoder.h"
//#include "decoder.h"
#include "heap.h"
using namespace std;
int main()
{
	int ty, Ty1, Ty2;char s[105], t[105];
	scanf("%d%d%d%s%s", &ty, &Ty1, &Ty2, s, t);
	FILE *fin, *fout;
	if(Ty1) fin = fopen("hi.in", "r");
	else fin = fopen("test.zip", "rb");
	if(Ty2) fout = /*fopen("out1.out", "w")*/stderr;
	else fout = fopen("out1","wb");
	if(ty == 0)
	{	
		Encoder EncodeSolver;
		EncodeSolver.Encode(fin, fout, Ty1, Ty2);
	}/* else 
	{
		Decoder DecodeSolver;
		DecodeSolver.Encode(fin, fout);
	}*/
}
