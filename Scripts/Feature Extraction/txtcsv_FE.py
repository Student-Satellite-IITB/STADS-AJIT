# -*- coding: utf-8 -*-
"""
Created on Sun Aug 28 16:10:47 2022

@author: PNP
"""
 #%%
import pandas as pd
for testcase in range(1,84):
    lines = []
    j = 0
    with open(f'../FE_OILS/Outputs_FE_1..83/out_FE_{testcase}.txt', 'r') as in_file:
        lines = in_file.read().splitlines()
        k=0
        t=0
        for line in lines:
            k+=1
            stripped =line.replace(","," ").split()
            if len(stripped)==1:
                t+=1
                # a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17=[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]
                a1, a2, a3, a4 = [], [], [], []
                c=0
                for j in range(k-1,k+80):
                    stripped =lines[j].replace(","," ").split()
                    if len(stripped)==1 and c==0:
                        a1=[stripped]

                    if len(stripped)==3 and stripped[1]!='=':   #fe_id cent_x cent_y    not "FE_time = 123456"
                        c=1
                        a2+=[stripped[0]]
                        a3+=[stripped[1]]
                        a4+=[stripped[2]]

                    # if len(stripped)==5:    # Total Matched Stars = 8
                    #     a5+=stripped[4]
                    # if len(stripped)==8:    # feID starID gcX gcY gcZ body_x body_y body_z
                    #     c=1
                    #     a6+=[stripped[0]]
                    #     a7+=[stripped[1]]
                    #     a8+=[stripped[2]]
                    #     a9+=[stripped[3]]
                    #     a10+=[stripped[4]]
                    #     a11+=[stripped[5]]
                    #     a12+=[stripped[6]]
                    #     a13+=[stripped[7]]
                    # if len(stripped)>0:
                    #     if stripped[0]=='quat_3.x':
                    #         a14+=[stripped[2]]
                    #     if stripped[0]=='quat_3.y':
                    #         a15+=[stripped[2]]
                    #     if stripped[0]=='quat_3.z':
                    #         a16+=[stripped[2]]
                    #     if stripped[0]=='quat_4':
                    #         a17+=[stripped[2]]
                    if len(stripped)==1 and c!=0 :
                        break
                    if len(stripped) == 2:
                        break
                length=0
                tlist=[a1,a2,a3,a4]
                for i in range(4):
                    if len(tlist[i])>length:
                        length=len(tlist[i])
                for j in range(4):
                    for i in range(length-len(tlist[j])):
                        tlist[j]+=['0']
                list_dict = {'test case no.':tlist[0], 'fe_id':tlist[1], 'x':tlist[2], 'y':tlist[3]} 
                df = pd.DataFrame(list_dict)
                df.to_csv(f'../FE_OILS/out_FE_csv/out_FE_{testcase}/FE_O_iter_info_'+str(t)+'.csv',index=None)
    #%%     

    # sudo sh -c 'echo WELL DONE >> ../FE_OILS/Outputs_FE_1..83/out_FE_83.txt'