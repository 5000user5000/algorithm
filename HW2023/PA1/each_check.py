# coding: utf-8
# 用來檢查每個case的結果是否正確

import os

os.system("make")
os.system("ulimit -s 242144")
size = [5,1000,2000,4000,8000,16000,32000,1000000]
modes = ["-MS","-QS","-HS","-IS","-RQS"]
for mode in modes:
  print(mode)
  for i in size:
    for j in range(1,4):
       command1 = "./bin/NTU_sort {mode} inputs/{i}.case{j}.in outputs/{i}.case{j}.out".format(mode=mode,i=i,j=j)
       command2 = "python3 ./src/check.py inputs/{i}.case{j}.in".format(i=i,j=j)
       #print(command2)
       print("mode:{mode} size:{i} case:{j}".format(mode=mode,i=i,j=j))
       os.system(command1)
       os.system(command2)
       
       if(i==5):
            break
print("Done")


# os.system("./bin/NTU_sort -MS inputs/1000.case1.in outputs/1000.case1.out")
# os.system("python3 ./src/check.py inputs/1000.case1.in")
