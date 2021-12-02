struct Encoder
{
	int N, Cnt[256], Son[512][2], Last, LastLen;
	long long FileSize;
	bool OutputType;
    FILE *OutFile;
    int Code[512], CodeLen[512];
    void Init();
    void Print(int x, int y);
    void ForcePrint();
    void GetCode(int x);
    void PrintVal(int x);
    bool Encode(FILE *fin, FILE *fout, bool InTy, bool OuTy);
};
