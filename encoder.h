struct Encoder
{
	int FileSize, N, Cnt[256], Son[512][2], Last = 0, LastLen = 0;
    FILE *OutFile;
    int Code[256];
    void Print(int x, int y);
    void ForcePrint();
    bool Encode(FILE *fin, FILE *fout);
};