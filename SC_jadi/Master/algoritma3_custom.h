#include <stdbool.h>

struct Node{
  char *hostname;
  char *PEType;
  double PELoad;
  double alc;
  struct Node *next;
};

void printPEList(struct Node *n){
  while (n != NULL) {
       printf("%s, %.5f\n", n->hostname, n->alc);
       //printf("%s => %s, %.5f\n", n->PEType, n->hostname, n->alc);
       n = n->next;
   }
}

//swap nilai alc dan hostname untuk sorting
void swap(struct Node *a, struct Node *b){
  double tempAlc = a->alc;
  double tempPELoad = a->PELoad;
  char *tempHostname = a->hostname;
  char *tempPEType = a->PEType;
  a->alc = b->alc;
  a->PELoad = b->PELoad;
  a->hostname = b->hostname;
  a->PEType = b->PEType;
  b->alc = tempAlc;
  b->PELoad = tempPELoad;
  b->hostname = tempHostname;
  b->PEType = tempPEType;
}

void sortDescendingPEList(struct Node *start){
  int swapped;
  struct Node *j;
  struct Node *i = NULL;

  if(start ==  NULL)
    return;

  do{
    swapped = false;
    j = start;
    while(j->next != i){
      if(j->alc < j->next->alc){
        swap(j, j->next);
        swapped = true;
      }
      j = j->next;
    }
    i = j;
  } while(swapped);
}

void sortAscendingPEList(struct Node *start){
  int swapped;
  struct Node *j;
  struct Node *i = NULL;

  if(start ==  NULL)
    return;

  do{
    swapped = false;
    j = start;
    while(j->next != i){
      if(j->alc > j->next->alc){
        swap(j, j->next);
        swapped = true;
      }
      j = j->next;
    }
    i = j;
  } while(swapped);
}

struct Node *combinePEList(struct Node **PElist, int nhost){
  int i,j;
  struct Node *All= NULL;
  struct Node *buff;
  struct Node *buffAll;

  //awalan
  j=0;
  buff = PElist[0];
  while(buff == NULL){
    j++;
    buff = PElist[j];
  }
  buffAll = (struct Node*) malloc(sizeof(struct Node));
  buffAll->hostname = buff->hostname;
  buffAll->alc = buff->alc;
  buffAll->PELoad = buff->PELoad;
  buffAll->PEType = buff->PEType;
  buffAll->next = NULL;
  All = buffAll;
  buff = buff->next;

  for(i=1; i<nhost; i++){
    while(buff != NULL){
      buffAll = (struct Node*) malloc(sizeof(struct Node));
      buffAll->hostname = buff->hostname;
      buffAll->alc = buff->alc;
      buffAll->PELoad = buff->PELoad;
      buffAll->PEType = buff->PEType;
      buffAll->next = All;
      All = buffAll;
      buff = buff->next;
    }
    buff = PElist[i];
  }

  return All;
}

struct Node **getPEList(double threshold1, double *PELoad,double *alc, int nhost, char **hostname){
  int i;
  struct Node *buff;
  struct Node *OPEList = NULL;
  struct Node *NPEList = NULL;
  struct Node *ULPEList = NULL;
  struct Node *LPEList = NULL;

  //untuk OPEList, NPEList, ULPEList, LPEList, dan gabungannya
  struct Node **PEList = (struct Node**) malloc(5*sizeof(struct Node*));

  for(i=0; i<nhost; i++){
    buff = (struct Node*) malloc(sizeof(struct Node));
    buff->hostname = hostname[i];
    buff->alc = alc[i];
    buff->PELoad = PELoad[i];
    buff->next = NULL;

    //memasukkan PE pada NPEList (Normal)
    if(alc[i] <= threshold1*1.25 && alc[i] >= threshold1*0.75){
      buff->PEType = "NPELIST";
      if(NPEList == NULL)
        NPEList = buff;
      else{
        buff->next = NPEList;
        NPEList = buff;
      }
    }

    //memasukkan PE pada OPEList (Overhead)
    else if(alc[i] > threshold1*1.25){
      buff->PEType = "OPELIST";
      if(OPEList == NULL)
        OPEList = buff;
      else{
         buff->next = OPEList;
         OPEList = buff;
      }
    }

    //memasukkan PE pada ULPEList (Under Lightly)
    else if(alc[i] < 0.5*threshold1){
      buff->PEType = "ULPELIST";
      if(ULPEList == NULL)
        ULPEList = buff;
      else {
        buff->next = ULPEList;
        ULPEList = buff;
      }
    }

    //memasukkan PE pada LPEList (Light)
    else{
      buff->PEType = "LPELIST";
      if(LPEList == NULL)
        LPEList = buff;
      else {
        buff->next = LPEList;
        LPEList = buff;
      }
    }
  }

  sortDescendingPEList(OPEList);
  sortAscendingPEList(ULPEList);
  sortAscendingPEList(LPEList);

  PEList[0] = OPEList;
  PEList[1] = NPEList;
  PEList[2] = LPEList;
  PEList[3] = ULPEList;
  PEList[4] = combinePEList(PEList, 5);
  return PEList;
}
