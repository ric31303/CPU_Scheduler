#No_IO_100

. ../config/dev.config
echo "$_resultPath"
echo "$_testPath"
echo "$_strategyAmount"
echo "$_testAmount"

strategyAmount=$(($_strategyAmount+1))

strategy=0

fileName="t1000"
Folder="t1000/"
testFileType=".txt";

resultPath="$_resultPath/$Folder"
testPath="$_testPath/$Folder"

echo "$testPath" "$resultPath"
# ../config/dev.config
# sudo echo "resultPath"

while [ "$strategy" -lt "$strategyAmount" ]
do
  ../build/CPU_Scheduling "$strategy" "$fileName" "$testPath" "$resultPath"
  strategy=$(($strategy+1))
done