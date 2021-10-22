byte ConsecutiveTriesk(byte nTries) {
byte ncount;
byte flag;
  
  if (ncount < nTries) {
    ncount++;
    flag = 0;
  }
  else {
    ncount = 0;
  }
  if (ncount == nTries)
    flag = 1;
  return flag;
}
