[<img src="https://www.aero.iitb.ac.in/satlab/images/IITBSSP2019.png" width="150"/>](image.png) 

## Student Satellite Project - Indian Institude of Technology, Bombay

### Ajit-STADS proposal

STADS stands for Star Tracker based Attitude Determination system. Our aim is build an indegeneous star tracker, ground test it and later test it on PS4-OP platform.
This repository contains relevant codes and documentation of different algorithms used in our system


## Note
 1. Centroid extraction (Feature Extraction)
 >   * Repo currently has C and C++ codes
 >  *  Inputs to Centroid extraction code are Image_n.txt files, added in FE_test cases folder
>  *  Outputs to Centroid extraction code are st_input_n.txt files, added in Star matching test cases folder. (Output from CE block is input to the star matching block)
>  * **Remark**: To test both the functions(region_growth, pixel_by_pixel), put image files from FE_Test_cases folder and the codes in the same directory. Follow respective READMEs to understand output files.

2. Star Matching
> * Documentaion and resources are added, C-codes will be added soon

2. Estimation
> * This folder has C-code for QUEST(estimation algorithm).
> * Follow "Quest_Readme.pdf" for more details
