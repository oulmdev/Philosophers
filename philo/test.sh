
read -p "number_of_philosophers: " num
read -p "time_to_die: " die
read -p "time_to_eat: " eat
read -p "time_to_sleep: " sleep
read -p "number_of_times_each_philosopher_must_eat: " meat

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
	echo "all philosophers eat $meat times"
else
	echo "not all philosophers eat $meat times"
fi

