int sumCustom(struct Node **PEList, double threshold1, int nhost){
  int dataSize, i, sisa, slice, *tid, cc, bound;
  unsigned long res, buff;
  char charSlice[6], charLowerBound[7], charUpperBound[7];
  char **args = (char**) malloc(4*sizeof(char*));
  tid = (int*) malloc((nhost+1)*sizeof(int));
  dataSize = 1000000;// jumnlah yang seharusnya
  slice = dataSize/nhost;
  sisa = dataSize%nhost;
  args[3] = NULL;
  bound = 0;
  res = 0;

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
      workHostname = jobMigration(n, PEList[2], PEList[3], threshold1);
    }else{
      workHostname = n->hostname;
    }
    printf("yang mengerjakan adalah: %s\n", workHostname);
    cc = pvm_spawn("./sumSlave", args, 1, workHostname, 1, &tid[i]);
    if(cc != 1){
      printf("can't start sumSlave\n");
      return 0;
    }
    n = n->next;
  }

  if(sisa != 0){
    n = PEList[4];
    sprintf(charSlice,"%d", sisa);
    args[0] = charSlice;
    sprintf(charLowerBound, "%d", (dataSize-sisa));
    args[1] =  charLowerBound;
    sprintf(charUpperBound, "%d", dataSize);
    args[2] =  charUpperBound;
    printf("Yang mengerjakan adalah: %s\n", n->hostname);
    cc = pvm_spawn("./sumSlave", args, 1, n->hostname, 1, &tid[nhost]);
    if(cc != 1){
      printf("can't start sumSlave\n");
      return 0;
    } else{
      cc = pvm_recv(tid[nhost], 1);
      pvm_bufinfo(cc, (int*)0, (int*)0, &tid[nhost]);
      pvm_upkulong(&buff, 1, 1);
      res += buff;
    }
  }

  for(i=0; i<nhost; i++){
    cc = pvm_recv(tid[i], 1);
    pvm_bufinfo(cc, (int*)0, (int*)0, &tid[i]);
    pvm_upkulong(&buff, 1, 1);
    res += buff;
    //printf("Nilai Buff ke-%d = %lu\n", i, buff);
  }

  printf("Hasil penjumlahan : %lu\n", res);
  return 0;
}
