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
    N_i = []
    for i in range(1,101):
        filepath = f"./Centroids/Testcase_{testcase_index}/txt/UIS_{i}.txt"
        # temp = open("C:/Users/DELL/Downloads/Centroids/Testcase_2/txt/UIS_" + str(i)+".txt", "r")
        temp = open(filepath, "r")
        temp_list = []
        for j in temp.readlines():
            for k in j.split():
                temp_list.append(k)
        kvec.append(temp_list)        


    for i in range(len(kvec)):
        N_i.append(len(kvec[i]))
    for i in range(len(kvec)):
        filedata = "#include <cortos.h>\n" 
        filedata+=f"//CORTOS_N_i_{i+1} - Number of input centroids\n#define CORTOS_N_i_{i+1} {N_i[i]}\n"
        UIS ="{"
        for j in range(N_i[i]):
            UIS+="{"
            UIS+= kvec[i][j]+"},\n"
            # UIS+=kvec[i][3*j]+","
            # UIS+=kvec[i][3*j+1]+","
            # UIS+=kvec[i][3*j+2]+"},\n"
            
        UIS=UIS.rstrip(UIS[-1])
        UIS+="}"
        filedata+=f'double UIS_{i+1}[CORTOS_N_i_{i+1}][3]={UIS};\n'
        # ./Centroids/Testcase_2/txt/UIS_{i}.txt
        # UISname = f'./TM_1..100/TM_{testcase_index}/UIS_{i+1}.h'
        UISname = f'.UIS_{i+1}.h'
        with open(UISname, 'w') as file :
            file.write(filedata)
    #try:
    #    os.system('touch -m main.c')

