struct Decoder
{
	int FileSize, N, Cnt[256];
    bool Decode(FILE *fin);
};