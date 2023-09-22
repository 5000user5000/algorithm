# coding: utf-8
# plot data.txt 的數據

import matplotlib.pyplot as plt
import numpy as np



file = open("data.txt", 'r')
modes = ["-MS","-QS","-HS","-IS","-RQS"]
# MS_time = []
# QS_time = []
# HS_time = []
# IS_time = []
# RQS_time = []

class DataRecord:
    def __init__(self, size, mode, cpu_time,case):
        self.size = size
        self.mode = mode
        self.cpu_time = cpu_time
        self.case = case



# 判斷是哪種 case
def check_case(line):
    if "case1" in line:
        return 1
    elif "case2" in line:
        return 2
    elif "case3" in line:
        return 3

records = []

while True:
    line = file.readline()
    if not line:
        break
    if "mode" in line:
        mode = line.split()[1]
        line = file.readline()
        case_type = check_case(line)
        size_raw = line.split('/')[1]
        size = int(size_raw.split('.')[0])
        line = file.readline()
        cpu_time = float(line.split(': ')[1].replace('ms',''))
        #type_app(mode,cpu_time)
        DataRecord(size, mode , cpu_time,case_type)
        records.append(DataRecord(size, mode , cpu_time,case_type))
        continue

# 做圖，共有3個圖，每個圖有5條線，每條線有7-8個點。x軸是size(log scale)，y軸是cpu time(log scale)



# 創建三張圖
fig1, ax1 = plt.subplots()
fig2, ax2 = plt.subplots()
fig3, ax3 = plt.subplots()

# 設置圖標題和軸標籤
ax1.set_title("Average Case (Case1)")
ax1.set_xlabel("Size (log scale)")
ax1.set_ylabel("CPU Time (log scale)")

ax2.set_title("Best Case (Case2)")
ax2.set_xlabel("Size (log scale)")
ax2.set_ylabel("CPU Time (log scale)")

ax3.set_title("Worst Case (Case3)")
ax3.set_xlabel("Size (log scale)")
ax3.set_ylabel("CPU Time (log scale)")

# 定義不同的 case 顏色
case_colors = {1: 'b', 2: 'g', 3: 'r'}

# 對每個 case 類型繪製五條線
for case_type in range(1, 4):
    case_data = [record for record in records if record.case == case_type]
    
    for mode in modes:
        mode_data = [record for record in case_data if record.mode == mode]
        sizes = [np.log10(record.size) for record in mode_data if record.mode == mode]
        cpu_times = [np.log10(record.cpu_time) for record in mode_data if record.mode == mode]
        label = "{mode}, Case {case_type}".format(mode=mode, case_type=case_type)
        if case_type == 1:
            ax1.plot(sizes, cpu_times, label=label, marker='o')
        elif case_type == 2:
            ax2.plot(sizes, cpu_times, label=label, marker='o')
        elif case_type == 3:
            ax3.plot(sizes, cpu_times, label=label, marker='o')

# 添加圖例
ax1.legend()
ax2.legend()
ax3.legend()

# 設置 y 軸為對數刻度
ax1.set_yscale("log")
ax2.set_yscale("log")
ax3.set_yscale("log")

# 顯示圖
plt.show()



    