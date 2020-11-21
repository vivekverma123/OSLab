echo -n "Enter the number: "
read x
b=$(($x%2)) 
if [ $b -eq 0 ]; then
echo The given no is even 
else
echo The given no is odd 
fi
