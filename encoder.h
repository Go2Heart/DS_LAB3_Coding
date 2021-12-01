struct Encoder
{
	int FileSize, N, Cnt[256], Son[512][2], Last, LastLen;
    FILE *OutFile;
    int Code[512], CodeLen[512];
    String Text;
    void Init();
    void Print(int x, int y);
    void ForcePrint();
    void GetCode(int x);
    bool Encode(FILE *fin, FILE *fout);
};