int testFibonacciCustom(struct Node **PEList, double threshold1, int nproses){
  int dataSize, i, *tid, cc;
  char charDataSize[9];
  char **args = (char**) malloc(2*sizeof(char*));
  tid = (int*) malloc((nproses)*sizeof(int));
  dataSize = 10000;
  args[1] = NULL;
  unsigned long *arrBuff = malloc(dataSize*sizeof(unsigned long));

  //job assignment
  struct Node *n;
  n = PEList[4];//PEList untuk semua PE yang terhubung
  printf("\nPembagian Task:\n");
  for(i=0; i<nproses; i++){
    if(n == NULL){//reset Linked List
      n = PEList[4];
    }

    char *workHostname;
    sprintf(charDataSize,"%d", dataSize);
    args[0] = charDataSize;
    if(n->PEType == "OPELIST"){
      workHostname = jobMigration(n, PEList[2], PEList[3], threshold1);
    }else{
      workHostname = n->hostname;
    }
    printf("yang mengerjakan adalah: %s\n", workHostname);
    cc = pvm_spawn("./fibonacciSlave", args, 1, workHostname, 1, &tid[i]);
    if(cc != 1){
      printf("can't start fibonacciSlave\n");
      return 0;
    }
    n = n->next;
  }

  for(i=0; i<nproses; i++){
    cc = pvm_recv(tid[i], 1);
    pvm_bufinfo(cc, (int*)0, (int*)0, &tid[i]);
    pvm_upkulong(arrBuff, dataSize, 1);
  }

  // for(i=0; i<dataSize; i++){
  //   printf("%lu ", arrBuff[i]);
  // }
  // printf("\n");

  return 0;
}
