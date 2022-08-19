import csv

with open("d:\coding VS code\.vscode\\first1.txt","rt") as myfile:
    list=[]
    for i in range (20649):
        line=myfile.readline()
        list.append(line)
allData=[]
k=1000

for p in range(0,21*k+1,21):
    temp=[]
    temp.append(int(list[p+0][6:]))
    temp.append(int(list[p+1][34:]))
    for k in range(2,15,4):
        temp.append(int(list[p+k+1][30:]))
        temp.append(int(list[p+k+3][28:]))
    temp.append(int(list[p+18][39:]))
    temp.append(int(list[p+19][33:]))
    allData.append(temp)


for i in range(len(allData)):
    print(allData[i])

with open("d:\coding VS code\.vscode\\ans2.csv","w",newline="") as f:
    thewriter =csv.writer(f)
    thewriter.writerow(["Data Set","Number of Scramble","Phase 1 Moves","Phase 1 Time","Phase 2 Moves","Phase 2 Time","Phase 3 Moves","Phase 3 Time","Phase 4 Moves","Phase 4 Time","Total Moves","Total Time"])
    for i in range(len(allData)):
        thewriter.writerow(allData[i])
    
