//mendapatkan total task yang dikerjakan pada setiap PE (rumus 7)
//input dari Algoritma 2
int *getTasks(char **hostname,int nhost){
  int cc, i, tid[nhost];
  int *tasks = malloc(nhost*sizeof(tasks));
  char buff[5];

  for(i=0; i<nhost; i++){
    cc = pvm_spawn("./updateTasksSlave", (char**) 0, 1, hostname[i], 1, &tid[i]);
    if(cc != 1){
      printf("can't start updateTasksSlave\n");
      return 0;
    }
  }
  for(i=0; i<nhost; i++){
    cc = pvm_recv(tid[i], 5);
    pvm_bufinfo(cc, (int*)0, (int*)0, &tid[i]);
    pvm_upkstr(buff);
    tasks[i] = atoi(buff);
  }
  return tasks;
}

// Rata - rata load untuk setiap PE (rumus 8)
double avg_load(int *tasks, int nhost){
  int currLoad,i;
  double avgLoad;
  currLoad = 0;
  for(i=0; i<nhost; i++){
    currLoad = currLoad+tasks[i];
  }
  avgLoad = (double)currLoad/(double)nhost;
  return avgLoad;
}

//menghitung MIPS untuk Rating pada rumus 9
double *getMips(char **hostname, int nhost){
  int cc, i, tid[nhost];
  double *mips = malloc(nhost*sizeof(mips));

  for(i=0; i<nhost; i++){
    cc = pvm_spawn("./mipsSlave", (char**) 0, 1, hostname[i], 1, &tid[i]);
    if(cc != 1){
      printf("can't start mipsSlave\n");
      exit(0);
    }
  }
  for(i=0; i<nhost; i++){
    cc = pvm_recv(tid[i], 1);
    pvm_bufinfo(cc, (int*)0, (int*)0, &tid[i]);
    pvm_upkdouble(&mips[i], 1, 1);
  }
  return mips;
}

//untuk menghitung Load pada setiap PE (rumus 9)
//Output dari Algortima 2
double *getPELoad(int *tasks, double *mips, double avgLoad, int nhost){
  int i;
  double *PELoad = malloc(nhost*sizeof(PELoad));
  for(i=0; i<nhost; i++){
    PELoad[i] = fabs(((double)tasks[i]- avgLoad)/mips[i]);
  }
  return PELoad;
}
