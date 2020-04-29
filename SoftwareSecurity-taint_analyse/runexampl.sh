# set the eviroment varible pin
# there must be space if()[()$1==1()]
echo $1
if [ $1 -eq 1 ]
then 
    echo pin -t ./obj-intel64/taint_example_1.so -- ./app/test
    pin -t ./obj-intel64/taint_example_1.so -- ./app/test
elif [ $1 -eq 2 ]
then 
    echo pin -t ./obj-intel64/taint_example_2.so -- ./app/test2
    pin -t ./obj-intel64/taint_example_2.so -- ./app/test2
else 
    echo enter number to choose example
fi