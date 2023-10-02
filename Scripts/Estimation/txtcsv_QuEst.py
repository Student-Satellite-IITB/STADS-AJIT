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
    with open(f'../EST_OILS_1..83/out_Quest/out_quest_{testcase}.txt', 'r') as in_file:
    # with open ('out_quest2.txt', 'r') as in_file:
        a1, a2, a3, a4, a5 = [], [], [], [], []
        lines = in_file.read().splitlines()
        k=0
        t=0
        for line in lines:
            k+=1
            stripped =line.replace(","," ").split()
            if len(stripped)==1:
                t+=1

            if len(stripped)==8:    # feID starID gcX gcY gcZ body_x body_y body_z
                if(stripped[0] == "Time"):
                    break

            if len(stripped)==3:
                if stripped[0]=='quat_3.x':
                    a2+=[stripped[2]]
                if stripped[0]=='quat_3.y':
                    a3+=[stripped[2]]
                if stripped[0]=='quat_3.z':
                    a4+=[stripped[2]]
                if stripped[0]=='quat_4':
                    a5+=[stripped[2]]

        tlist = [a1, a2, a3, a4, a5]

        list_dict = {'q3_x':tlist[1], 'q3_y':tlist[2], 'q3_z':tlist[3], 'q_4':tlist[4]}
        df = pd.DataFrame(list_dict)
        # df.to_csv(f'../STADS_Tracking_Mode/out_CSV/out_TM_LISM_csv/out_TM_LISM_{testcase}/OILS_iter_info_'+str(t)+'.csv',index=None)
        df.to_csv(f'../EST_OILS_1..83/out_Quest_csv/out_quest_{testcase}'+'.csv',index=None)

        # df.to_csv('quest2_100'+'.csv', index = 'none')  