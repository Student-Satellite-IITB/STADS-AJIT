# This file is to check the outputs of Star Matching


import pandas as pd
for testcase_index in range(1,84):
    filedata =""
    with open(f'./STADS_Tracking_Mode/TM_1..100/out_TM_LISM/out_{testcase_index}.txt', 'r') as in_file:
        lines = in_file.read().splitlines()
        k = 0
        i_line = 0

        for line in lines:  
            k += 1
            # print(line)
            stripped =line.split()

            if len(stripped) == 1:          #for UIS_iter_
                UIS_iter = stripped[0]
                i_line += 2
                strip_line = lines[i_line].split()
                # print(strip_line)

                if (((len(strip_line) != 0) and strip_line[0] == "Total")):
                    while(1):
                        i_line += 1
                        ID_line = lines[i_line].split()
                        if (len(ID_line) == 0): 
                            break
                        else:
                            starID_1 = ID_line[0]
                            starID_2 = ID_line[1]
                            if (starID_1 != starID_2):
                                filedata += UIS_iter +'\n'
                                # print("INCORRECT MATCH in ", UIS_iter)
                                break
        UISname = f'./STADS_Tracking_Mode/TM_1..100/TM_LISM_validate/out_TM_LISM_validate{testcase_index}.txt'
        with open(UISname, 'w') as file :
                file.write(filedata)

