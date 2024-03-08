#include <stdio.h>
#include <stdlib.h>
#include "PcapFile.h"

int main()
{
	char fname[256 + 1] = "";
	printf("PCAP file name : ");
	scanf_s("%s", fname, sizeof(fname));

	FILE* fp = 0;
	fopen_s(&fp, fname, "rb");
	if (fp == 0)
	{
		perror("Failed to open file");
		system("pause");
		return 0;
	}

	PFHeader pfh = { 0, };
	if (ParsePCapFile(fp, &pfh) == 0)
	{
		printf("This is not a PCAP file\n");
		fclose(fp);
		system("pause");
		return 0;
	}

	switch (pfh.linktype)
	{
	case LT_ETHER: ParseEthers(fp); break;
	default: printf("Not Support\n"); break;
	}
	fclose(fp);
	system("pause");
	return 0;
}
