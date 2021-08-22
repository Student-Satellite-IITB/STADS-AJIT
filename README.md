[<img src="https://www.aero.iitb.ac.in/satlab/images/IITBSSP2019.png" width="150"/>](image.png) 

## Student Satellite Project - Indian Institude of Technology, Bombay

## AJIT-STADS Collaboration

STADS stands for Star Tracker based Attitude Determination system. Our aim is to build an indigenous star tracker, which will be ground tested, and later flown and tested on the PSLV Stage 4 - Orbital Platform (PS4-OP).
This repository contains relevant codes and documentation of different algorithms used in our system

Conceived in IIT Bombay, AJIT is one of India's first indigenously developed microprocessors.

## Note
 1. Feature Extraction (FE)
 >  * Repo currently has C and C++ codes
 >  * Inputs to Centroid Extraction algorithm are `Image_n.txt` files, hosted in [Feature Extraction/Test_cases](Feature%20Extraction/Test_cases)
 >  * Outputs of the Centroid Extraction algorithm are exported as `st_input_n.txt`. These have been placed under the [Star Matching Test_cases](Star%20Matching/Test_cases) folder. (Output from FE block acts as the input to the ST block)
 >  * There are two different Feature Extraction algorithms - region growth and pixel by pixel
 >  * Remark: Note that "Feature Extraction", "Centroid Extraction" and "Centroiding" are equivalent and may be used interchangeably. At the initial stages of development, "Feature Extraction" was used, however, the latter terms are more descriptive and hence caused a shift in terminology.

2. Star Matching (ST)
> * The algorithm flowchart and reference materials have been added. The C codes will be added soon.

3. Estimation (EST)
> * This folder has C code for QUEST (QUaternion ESTimation).
> * Follow the [`RM_est_Quest.pdf`](Estimation/README/RM_est_Quest.pdf) for further details
