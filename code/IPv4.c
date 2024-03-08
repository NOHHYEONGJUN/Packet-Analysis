#include "IPv4.h"
#include "TCP.h"

void PrintIPv4(uint addr)
{
    uchar* up = (uchar*)&addr;
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        printf("%d.", up[i]);
    }
    printf("%d", up[i]);

}
void ParseIPv4(uchar* base, uint len)
{
    IPv4Header* iph = (IPv4Header*)base;
    printf("★★★★★     IPv4 Header    ★★★★★\n");
    printf("\n\tversion : %d\n", iph->version);
    printf("\theader lenngth  : %d bytes\n", iph->hlen * 4);
    printf("\ttotal length : %d bytes\n", ntohs(iph->tlen));
    printf("\tid : %d\n", ntohs(iph->id));

    if (DONT_FRAG(iph->fl_off))
    {
        printf("\tDon't Fragment\n");
    }
    if (MORE_FRAG(iph->fl_off))
    {
        printf("\tMore Fragment\n");
    }
    printf("\toffset : %d bytes\n", FRAG_OFF(iph->fl_off));
    printf("\tTime To Live : %d\n", iph->ttl);
    printf("\tProtocol : %d\n", iph->protocol);
    printf("\tICMP : %d IGMP : %d TCP : %d UDP : %d OSPF : %d\n",
        PRO_ICMPv4, PRO_IGMP, PRO_TCP, PRO_UDP, PRO_OSPF);
    printf("\tsrc: ");
    PrintIPv4(iph->srcaddr);
    printf("   dst: ");
    PrintIPv4(iph->dstaddr);
    printf("\n");
    uchar* next = base + (iph->hlen * 4);
    len = len - (iph->hlen * 4);
    switch (iph->protocol)
    {
    case PRO_ICMPv4: printf("\t to be defined\n"); break;
    case PRO_TCP: ParseTCP(next, len);  break;
    default: printf("\t Not supported\n"); break;
    }
}
