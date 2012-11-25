#include <stdio.h>
#include <string.h>
#define INFINITY 99
#define NODE3 3
#define TRUE 1
#define FALSE 0

int isNeighbor3(int);
int sendToNeighbors3(int,int[]);

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };

extern int TRACE;
extern int YES;
extern int NO;
extern float clocktime;

struct distance_table 
{
  int costs[4][4];
} dt3;

int minCost3[4];		/*The distance vector between current node and other nodes*/
int linkCost3[4];  /* link cost from the node to other nodes */
/* students to write the following two routines, and maybe some others */
int sendDV3;

void rtinit3() 
{
    linkCost3[0] = 7;
    linkCost3[1] = INFINITY;
    linkCost3[2] = 2;
    linkCost3[3] = 0;

    memcpy(dt3.costs[NODE3],linkCost3,sizeof(int[4]));
    memcpy(minCost3,linkCost3,sizeof(int[4]));
    sendDV3 = FALSE;

    printdt3();
    sendToNeighbors3(NODE3,minCost3);

}


void rtupdate3(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
    if(isNeighbor3(rcvdpkt->sourceid)){
        int i;
        for(i = 0; i < 4; i++){
            if(minCost3[i] > rcvdpkt->mincost[i]){
                int possibleRoute = minCost3[rcvdpkt->sourceid]+rcvdpkt->mincost[i];
                if(possibleRoute < minCost3[i]){
                    minCost3[i] = possibleRoute;
                    sendDV3 = TRUE;
                }
            }
        }
        memcpy(dt3.costs[NODE3],minCost3,sizeof(int[4]));
        memcpy(dt3.costs[rcvdpkt->sourceid],rcvdpkt->mincost,sizeof(int[4]));
        printdt3();
    }
    if(sendDV3){
        sendToNeighbors3(NODE3,minCost3);
        sendDV3 = FALSE;
    }

}

int isNeighbor3(int sourceid){
    return linkCost3[sourceid] != INFINITY;
}
int sendToNeighbors3(int sourceid, int mincost[]){
    int i;
    for(i = 0; i < 4; i++){
       if(isNeighbor3(i) && i != sourceid) sendrtpkt(sourceid, i, mincost);
    }
}


printdt3()
{
  printf("              cost to   \n");
  printf("   D3 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n",dt3.costs[0][0], dt3.costs[0][1], dt3.costs[0][2],dt3.costs[0][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n",dt3.costs[2][0], dt3.costs[2][1], dt3.costs[2][2],dt3.costs[2][3]);
  printf("     3|  %3d   %3d   %3d  %3d\n",dt3.costs[3][0], dt3.costs[3][1], dt3.costs[3][2],dt3.costs[3][3]);
}



linkhandler3(linkid, newcost)   
  int linkid, newcost;
{
}




