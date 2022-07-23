from numpy import double
import pandas as pd

f = open("oils_output.txt", 'r')
lines = f.readlines()

df = pd.DataFrame([], columns=['q_3.x', 'q_3.y', 'q_3.z', 'q_4', 'Time'])

for line in lines:
    line = line.replace('\x00', '')
    if "SIS_iter_" in line:
        idx = int(line[9:])
    if 'quat_3.x = ' in line:
        df.loc[idx - 1, 'q_3.x'] = double(line[11:])
    if 'quat_3.y = ' in line:
        df.loc[idx - 1, 'q_3.y'] = double(line[11:])
    if 'quat_3.z = ' in line:
        df.loc[idx - 1, 'q_3.z'] = double(line[11:])
    if 'quat_4   = ' in line:
        df.loc[idx - 1, 'q_4'] = double(line[11:])


df.to_csv("readings.csv", index=False)