# -*- coding: utf-8 -*-
"""
Created on Sun Aug 28 16:10:47 2022

@author: PNP
"""
 #%%
import pandas as pd
for testcase in range(2,84):
    lines = []
    j = 0
    with open(f'./STADS_Tracking_Mode/TM_1..100/out_LISM/out_LISM_{testcase}.txt', 'r') as in_file:
        lines = in_file.read().splitlines()
        k=0
        t=0
        for line in lines:
            k+=1
            stripped =line.replace(","," ").split()
            if len(stripped)==1:
                t+=1
                a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17=[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]
                c=0
                for j in range(k-1,k+80):
                    stripped =lines[j].replace(","," ").split()
                    if len(stripped)==1 and c==0:
                        a1=[stripped]

                    # if len(stripped)==3 and stripped[1]!='=':   #fe_id cent_x cent_y    not "FE_time = 123456"
                    #     c=1
                        # a2+=[stripped[0]]
                        # a3+=[stripped[1]]
                        # a4+=[stripped[2]]

                    if len(stripped)==5:    # Total Matched Stars = 8
                        a5+=stripped[4]
                    if len(stripped)==8:    # feID starID gcX gcY gcZ body_x body_y body_z
                        c=1
                        a6+=[stripped[0]]
                        a7+=[stripped[1]]
                        a8+=[stripped[2]]
                        a9+=[stripped[3]]
                        a10+=[stripped[4]]
                        a11+=[stripped[5]]
                        a12+=[stripped[6]]
                        a13+=[stripped[7]]
                    # if len(stripped)>0:
                    #     if stripped[0]=='quat_3.x':
                    #         a14+=[stripped[2]]
                    #     if stripped[0]=='quat_3.y':
                    #         a15+=[stripped[2]]
                    #     if stripped[0]=='quat_3.z':
                    #         a16+=[stripped[2]]
                    #     if stripped[0]=='quat_4':
                    #         a17+=[stripped[2]]
                    if len(stripped)==1 and c!=0:
                        break
                length=0
                tlist=[a1,a5,a6,a7,a8,a9,a10,a11,a12,a13]
                for i in range(10):
                    if len(tlist[i])>length:
                        length=len(tlist[i])
                for j in range(10):
                    for i in range(length-len(tlist[j])):
                        tlist[j]+=['0']
                list_dict = {'test case no.':tlist[0],'matched SID':tlist[1],'matched input SID':tlist[2],'SSP ID':tlist[3],'ix':tlist[4],'iy':tlist[5],'iz':tlist[6],'bx':tlist[7],'by':tlist[8],'bz':tlist[9]} 
                df = pd.DataFrame(list_dict)
                df.to_csv(f'./STADS_Tracking_Mode/out_CSV/out_LISM_csv/out_LISM_{testcase}/OILS_iter_info_'+str(t)+'.csv',index=None)
    #%%     