import pandas as pd
import numpy as np

"""
l = np.arange(1000, 10100, 100)
print(l)

for i in l:
    print("gcc -o randomwalk.exe randomwalk.c -DN="+str(i)) 
    print("./randomwalk.exe >> result.csv")
"""

df = pd.read_csv("./result.csv",header=None)
df = df.rename(columns={0:"N",1:"result"})
print(len(df))
for i in range(len(df)):
    print(str(df.loc[i,"N"])+",",end='')
print("\n")
for i in range(len(df)):
    print(str(round(df.loc[i,"result"],5))+",",end='')
print("\n")