struct Decoder
{
	long long FileSize;
	int N, Son[512][2], LastLen, Root;
	unsigned char Last;
	bool InputType, OutputType;
    FILE *InFile, *OutFile;
    unsigned char Code[512];
    void Init();
	int Read();
    void ForceRead();
    void BuildTree(int &x);
    void InsertVal(int x);
    void Decoding(int x);
    bool Decode(FILE *fin, FILE *fout, bool InTy, bool OuTy);
};
