char **getHostnameTxt(char *hostFile, int nhost){
  FILE *filePointer;
  char **hostname = malloc(nhost*sizeof(hostname));

  if((filePointer = fopen(hostFile, "r")) == NULL){
    printf("file %s tidak bisa dibuka!\n", hostFile);
    return NULL;
  } else{
    int i;
    for(i=0; i<nhost; i++){
      hostname[i] = malloc(25*sizeof(char));
      if(fscanf(filePointer, "%s", hostname[i]) == -1){
        printf("hostname pada file %s kurang !\n", hostFile);
        return NULL;
      }
    }
    fclose(filePointer);
  }

  return hostname;
}
