import os
import glob

    # with open('main.c', 'r') as file :
    #   filedata = file.read()




    # for filename in glob.glob('*.txt'):
    #     temp = []
    #     with open(os.path.join(os.getcwd(), filename), 'r') as f:
    #         for readline in f:
    #             for str in readline.split():
    #                 temp.append(str)
    #     kvec.append(temp)

for testcase_index in range(1,84):
    filedata =""
    kvec = []
    stars_filepath = f"../../EST_OILS/Testcase_{testcase_index}/Stars_Est_{testcase_index}.txt"
    s_temp = open(stars_filepath, "r")
    for j in s_temp.readlines():
        N_i = j.replace(",", " ").split()

    for i in range(1,101):
        filepath = f"../../EST_OILS/Testcase_{testcase_index}/UIS_Est_{i}.txt"
        # temp = open("C:/Users/DELL/Downloads/Centroids/Testcase_2/txt/UIS_" + str(i)+".txt", "r")
        temp = open(filepath, "r")
        temp_list = []
        for j in temp.readlines():
            for k in j.split():
                temp_list.append(k)
        kvec.append(temp_list)        

        # stripped =j.replace(","," ").split()
        # N_i.append(len(stripped))

    for i in range(len(kvec)):
        N_i.append(len(kvec[i]))
    for i in range(len(kvec)):
        filedata = "#include <stdio.h>\n" 
        filedata+=f"//N_i_{i+1} - Number of input centroids & stars\n#define N_i_{i+1} {N_i[i]}\n"
        UIS ="{"
        if (N_i[i] != 0):
            for j in range(3):
                UIS+="{"
                UIS+= kvec[i][j]+"},\n"
                # UIS+=kvec[i][3*j]+","
                # UIS+=kvec[i][3*j+1]+","
                # UIS+=kvec[i][3*j+2]+"},\n"
    #  double data[3][52]=       
        UIS=UIS.rstrip(UIS[-1])
        UIS+="}"
        filedata+=f'double UIS_Est_{i+1}[3][50]={UIS};\n'
        # ./Centroids/Testcase_2/txt/UIS_{i}.txt
        UISname = f'../../EST_OILS_1..83/Est_{testcase_index}/UIS_Est_{i+1}.h'
        # UISname = f'.UIS_Est_{i+1}.h'
        with open(UISname, 'w') as file :
            file.write(filedata)
    #try:
    #    os.system('touch -m main.c')

