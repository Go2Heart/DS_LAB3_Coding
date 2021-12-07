#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "encoder.h"
#include "decoder.h"
#include "heap.h"
using namespace std;
int main(int argc,char *argv[])
{
	int ty;
	ty=argv[1][0]-'0';
	//ty=1;
	FILE *fin, *fout;
	fin = fopen("in.txt","r");
	fout = fopen("out.txt","w");
	if(ty == 0)
	{	
		Encoder EncodeSolver;
		EncodeSolver.Encode(fin, fout,1,1);
	} else if(ty == 1)
	{
		Decoder DecodeSolver;
		DecodeSolver.Decode(fin, fout,1,1);
	}
	return 0;
}
