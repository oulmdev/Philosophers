
read -p "Please enter the number of philos: " num
read -p "Please enter time to die: " die
read -p "Please enter time to eat: " eat
read -p "Please enter time to sleep: " sleep
read -p "Please enter most eat: " meat

./philo $num $die $eat $sleep $meat > test

var="good"

for i in $(seq 1 $num)
do
	result=$(cat test | grep "$i is eating" | wc -l)
	if [ $result != $meat ];then
		var="bad"
	else
		var="good"
	fi
done

if [ $var = "good" ];then
	echo "good"
else
	echo "bad"
fi

