char **gethostname(int nhost){
  int cc, tid, i;
  char **hostname = malloc(nhost*sizeof(hostname));
  //mengirimkan perintah ke slave untuk mendapatkan jumlah task masing - masing
  for(i=0; i<nhost; i++){
    cc = pvm_spawn("./setHostnameSlave", (char**) 0, 0, "", 1, &tid);
    if(cc == 1){
      hostname[i] = malloc(15*sizeof(hostname[i]));
      cc = pvm_recv(tid, 2);
      pvm_bufinfo(cc, (int*)0, (int*)0, &tid);
      pvm_upkstr(hostname[i]);
    }
    else printf("can't start setHostnameSlave\n");
  }
  return hostname;
}
