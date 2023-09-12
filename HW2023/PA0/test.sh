# 用來自動化執行測試程式(我自己寫的，以此加速測試程式，就不用一個個輸入指令)
cd src
#make demo_opt
make demo_dbg
cd ../bin
#./demo_dbg ../inputs/1000.case1.in ../outputs/1000.case1.out
# run 程式
./demo_dbg ../inputs/5.case1.in ../outputs/5.case1.out

#回到原處
cd .. 

