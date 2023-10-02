## STADS Algo Testing & OILS Results
This branch consits of recent OILS codes & the individual blocks are tested on 83 testcases of 100 images each. 
OILS codes (in-loop) are tested on 20 constellations and the results are added as plots for Quaternion Errors
## Tuned epsilon_seq_error in Est and TOL in Star Matching
epsilon_seq_error = 0.005 //
TOL = 0.5 but if(10e4* fabs < TOL) instead of (fabs < TOL/100)
15 testcases with q_error > 36 arcsec error
