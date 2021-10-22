byte ConsecutiveTriesk(byte nTries) {
byte ncount;
byte flag;
  
  if (ncount < nTries) {
    ncount++;
    flag = 0;
  }
  else {
    ncount = 0;
    flag = 1;
  }
  return flag;
}
