# coding: utf-8
# 讀取 ../input/xxx.in 和 ../output/xxx.out
# 並且檢查是否有 sorting 成功

import sys

if(len(sys.argv) != 2):
    print("Usage: python3 check.py <input_file_name>")
    exit(1)

input_file_name = sys.argv[1]              # "inputs/1000.case1.in" #依照當前執行的路徑，而非python檔的相對路徑
output_file_name =  input_file_name.replace("in","out")                     #"outputs/1000.case1.out"

input_file = open(input_file_name, 'r')
output_file = open( output_file_name, 'r')

input_number = []
output_number = []

while True:
    line = input_file.readline()
    if not line:
        break
    if line[0] == '#':
        continue
    num = int(line.split()[1])
    input_number.append(num)
    #print(line)

while True:
    line = output_file.readline()
    if not line:
        break
    if line[0] == '#':
        continue
    num = int(line.split()[1])
    output_number.append(num)
    #print(line)

input_number.sort() # sort the input number

if input_number == output_number:
    print("Sorting Success!")
else:
    print("Sorting Failed!")
    print("Input file: ", input_file_name)
    # print("Input Number: ", input_number)
    # print("Output Number: ", output_number)
