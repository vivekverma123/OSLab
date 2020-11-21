count=1 
f1=1 
f2=1 
k=0
n=0
echo -n "Enter the value of n: "
read n
if [ $n -ge 1 ] 
then
	echo $f1
fi

if [ $n -ge 2 ] 
then 
	echo $f2
fi

if [ $n -gt 2 ] 
then
	while [ $count -le $(($n-2)) ]
	do
		k=$(($f1+$f2)) 
		echo $k
		f1=$f2 
		f2=$k
		count=$(($count+1)) 
	done
fi
