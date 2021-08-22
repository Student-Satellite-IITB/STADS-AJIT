# Feature Extraction - Tagging Algorithm

> In some contexts, referred to as the 'pixel_by_pixel' algorithm

`fe_pixel_by_pixel` and `fe_tagging` refer to the same algorithm. 
The function broadly has two subfunctions, `tag_2()` and `merge_tag()`, the README for which can be found [here](README/README%20MATLAB%20Functions)

The flowcharts for the two subfunctions can be found under the flowcharts subdirectory
while the C and C++ codes can be found in the current directory. 

['RM_fe_pixel_by_pixel_c.pdf'](README/RM_fe_pixel_by_pixel_c.pdf) explains the I/O flow of this algorithm

The constant parameters are set as the following based on results from the now former Sensor Model: `THRESHOLD`=14, `STAR_MIN_PIXEL`=4. These are subject to change (vastly) based on the results from the Star Image Simulation Model and Model In-Loop Simulation framework
