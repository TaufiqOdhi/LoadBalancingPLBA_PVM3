//untuk mendapatkan rata2 PELoad (rumus 10)
double ALC(double *PELoad, int nhost){
  double alc = 0;
  int i;
  for(i=0; i<nhost; i++){
    alc = alc+PELoad[i];
  }
  alc = alc/nhost;

  return alc;
}

//untuk mendapatkan rata2 dari rata2 PELoad (rumus 11)
double ALM(double *alc, int ncluster, int part){
  double alm = 0;
  int i;
  for(i=part-ncluster; i<part; i++){
    alm = alm+alc[i];
  }
  alm = alm/ncluster;

  return alm;
}

//digunakan untuk menghitung nilai threshold (rumus 13)
double standar_deviasi(double *alc, double alm, int ncluster, int part){
  double std_dvs = 0;
  int i;
  for(i=part-ncluster; i<part; i++){
    std_dvs = std_dvs + pow((alc[i] - alm), 2);
  }
  std_dvs = std_dvs/ncluster;

  return std_dvs;
}

//threshold rumus 12
double getThreshold1(double alm, double std_dvs){
  return (double) alm+std_dvs;
}
