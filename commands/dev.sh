#IO_100
. ../config/dev.config
echo "$_resultPath"
echo "$_testPath"
echo "$_strategyAmount"
echo "$_testAmount"

strategy=0

fileName="test_case_sample"
Folder=""
testFileType=".txt";

resultPath="$_resultPath/$Folder"
testPath="$_testPath/$Folder"

echo "$testPath" "$resultPath"
# ../config/dev.config
# sudo echo "resultPath"

../build/CPU_Scheduling "$strategy" "$fileName" "$testPath" "$resultPath"

