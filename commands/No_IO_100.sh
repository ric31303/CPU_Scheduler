#No_IO_100

. ../config/dev.config
echo "$_resultPath"
echo "$_testPath"
echo "$_strategyAmount"
echo "$_testAmount"

strategyAmount=$(($_strategyAmount+1))
testAmount=$(($_testAmount+1))

strategy=0

fileName="test_threads_100_v"
Folder="No_IO/threads_100/"
testFileType=".txt";

resultPath="$_resultPath/$Folder"
testPath="$_testPath/$Folder"

echo "$testPath" "$resultPath"
# ../config/dev.config
# sudo echo "resultPath"

while [ "$strategy" -lt "$strategyAmount" ]
do
  testNum=1
  while [ "$testNum" -lt "$testAmount" ]
  do
    file="$fileName$testNum"
    ../build/CPU_Scheduling "$strategy" "$file" "$testPath" "$resultPath"
    # echo "$strategy" "$file"
    testNum=$(($testNum+1))
  done
  strategy=$(($strategy+1))
done