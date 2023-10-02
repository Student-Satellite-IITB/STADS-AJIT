# for testcase_index in range(81,84):
#     for index in range(1,101):
#         print(f'python3 preprocess_image.py -f ../SIS_images/Testcase_{testcase_index}/txt/image_{index}.txt -m rga -i {index} -l 808 -b 608 -o ../SIS_images/Testcase_{testcase_index}/image_{index}.h')
# for i in range(1,84):
#     print(f'mv ../FE_MILS/MILS_FE_output/FE_Testcase_{i}/MILS_iter_''{1..100}.mat ../FE_MILS/MILS_FE_output/FE_Testcase_'f'{i}/RGA/')

# for i in range(1, 84):
#     # print(f'mkdir ../FE_OILS/out_FE_csv/out_FE_{i}')
#     print('sudo sh -c '"""'"""'echo WELL DONE >> ../FE_OILS/Outputs_FE_1..83/out_FE_'f'{i}.txt'"""'""")

# for i in range(1, 84):
#     print(f'cp functions.h ../EST_OILS_1..83/Est_{i}')
#     print(f'cp quat_est.c ../EST_OILS_1..83/Est_{i}')

# for i in range(1,84):
#     print(f'cd ../Est_{i}')
#     print('gcc -o exe quat_est.c -lm')
#     print(f'./exe > out_quest_{i}.txt')

for i in range(1, 84):
    print(f'cd ../Est_{i}')
    print(f'cp out_quest_{i}.txt ../out_Quest')
