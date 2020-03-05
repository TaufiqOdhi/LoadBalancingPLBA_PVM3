//threshold2 (rumus 16)
double getThreshold2(double *alm, int nmachine){
  double alr = 0;
  double std_dvs2 = 0;
  int i;

  //untuk mendapatkan rata2 load pada level resource system (rumus 15)
  for(i=0; i<nmachine; i++){
    alr = alr+alm[i];
  }
  alr = alr/nmachine;

  //standar deviasi untuk nilai threshold2 (rumus 17)
  for(i=0; i<nmachine; i++){
    std_dvs2 = std_dvs2 + pow((alm[i] - alr), 2);
  }
  std_dvs2 = std_dvs2/nmachine;
  printf("Standar Deviasi threshold2 = %.5f\n", std_dvs2);

  return (double) alr+std_dvs2;
}
