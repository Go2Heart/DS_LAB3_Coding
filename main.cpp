#include "encoder.h"
#include "decoder.h"
#include "heap.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;
int main()
{
	int ty;char s[105], t[105];
	scanf("%d%s%s", &ty, s, t);
	FILE *fin = fopen(s, "rb"), *fout = fopen(t, "wb");
	if(ty == 0)
	{	
		Encoder EncodeSolver;
		EncoderSolver.Encode(fin, fout);
	} else 
	{
		Decoder DecodeSolver;
		DecoderSolver.Encode(fin, fout);
	}
}