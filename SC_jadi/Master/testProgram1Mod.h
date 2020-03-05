//untuk contoh program berat,
//bubbleSort dengan array[100000000]
int testMergeSortCustom(struct Node **PEList, int nhost){
  int dataSize, i, sisa, slice, *tid, **arr, cc, bound;
  char charSlice[9], charLowerBound[9], charUpperBound[9];
  char **args = (char**) malloc(4*sizeof(char*));
  tid = (int*) malloc((nhost+1)*sizeof(int));
  dataSize = 100000000;
  slice = dataSize/nhost;
  sisa = dataSize%nhost;
  args[3] = NULL;
  bound = 0;

  //job assignment
  struct Node *n;
  n = PEList[4];//PEList untuk semua PE yang terhubung
  printf("\nPembagian Task:\n");
  for(i=0; i<nhost; i++){
    char *workHostname;
    sprintf(charSlice,"%d",slice);
    args[0] = charSlice;
    sprintf(charLowerBound, "%d", bound);
    args[1] = charLowerBound;
    sprintf(charUpperBound, "%d", (bound+slice));
    args[2] = charUpperBound;
    bound += slice;
    if(n->PEType == "OPELIST"){
      workHostname = jobMigration(n, PEList[2], PEList[3], n->threshold1);
    }else{
      workHostname = n->hostname;
    }
    printf("yang mengerjakan adalah: %s\n", workHostname);
    cc = pvm_spawn("./mergeSortSlave", args, 1, workHostname, 1, &tid[i]);
    if(cc != 1){
      printf("can't start mergeSortSlave\n");
      return 0;
    }
    n = n->next;
  }

  if(sisa == 0){
    arr = (int**) malloc(nhost*sizeof(int*));
  }
  else{
    n = PEList[4];
    arr = (int**) malloc((nhost+1)*sizeof(int*));
    arr[nhost] = (int*) malloc(sisa*sizeof(int));
    sprintf(charSlice,"%d", sisa);
    args[0] = charSlice;
    sprintf(charLowerBound, "%d", (dataSize-sisa));
    args[1] =  charLowerBound;
    sprintf(charUpperBound, "%d", dataSize);
    args[2] =  charUpperBound;
    printf("Yang mengerjakan adalah: %s\n", n->hostname);
    cc = pvm_spawn("./mergeSortSlave", args, 1, n->hostname, 1, &tid[nhost]);
    if(cc != 1){
      printf("can't start mergeSortSlave\n");
      return 0;
    } else{
      cc = pvm_recv(tid[nhost], 1);
      pvm_bufinfo(cc, (int*)0, (int*)0, &tid[nhost]);
      pvm_upkint(arr[nhost], sisa, 1);
    }
  }

  for(i=0; i<nhost; i++){
    arr[i] = (int*) malloc(slice*sizeof(int));
    cc = pvm_recv(tid[i], 1);
    pvm_bufinfo(cc, (int*)0, (int*)0, &tid[i]);
    pvm_upkint(arr[i], slice, 1);
  }

  return 0;
}
