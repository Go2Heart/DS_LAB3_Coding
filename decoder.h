struct Decoder
{
	long long FileSize;
	int N, Son[512][2], LastLen, Root;
	unsigned char Last;
	bool InputType, OutputType;
    FILE *InFile, *OutFile;
    unsigned char Code[512];
    void Init();
	bool Read(int &x);
    void ForceRead();
    bool BuildTree(int &x);
    bool InsertVal(int x);
    bool Decoding(int x);
    bool Decode(FILE *fin, FILE *fout, bool InTy, bool OuTy);
};
