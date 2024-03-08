#include "PcapFile.h"
#include "EHEther.h"
char buffer[0x100000];
void ViewPCapFile(PFHeader* pfh);
void ViewPacketHeaderInfo(PackHeader* ph, int pno);

void ParseEthers(FILE* fp)
{
    PackHeader ph = { 0 };
    int pno = 0;
    while (fread(&ph, sizeof(PackHeader), 1, fp) == 1)
    {
        pno++;
        ViewPacketHeaderInfo(&ph, pno);
        fread(buffer, sizeof(uchar), ph.caplen, fp);
        ParseEther(buffer, ph.caplen);
    }
}

int ParsePCapFile(FILE* fp, PFHeader* pfh)
{
    fread(pfh, sizeof(PFHeader), 1, fp);
    if (pfh->magic != PF_MAGIC)
    {
        return 0;
    }
    ViewPCapFile(pfh);
    return 1;
}
void ViewPCapFile(PFHeader* pfh)
{
    printf("=========== PCAP File header information ============\n");
    printf("\n\tversion:%d.%d\n", pfh->major, pfh->minor);
    printf("\tMaximum Capture Length:%d bytes\n", pfh->max_caplen);
}
void ViewPacketHeaderInfo(PackHeader* ph, int pno)
{
    printf("\n\n=========== <%4dth> Frame ===========n", pno);
    printf("\nPacket:%6d bytes  ,  Capture:%6d\n", ph->packlen, ph->caplen);
}
