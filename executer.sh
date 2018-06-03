N=5

rm res.txt

for i in 1 2 4 8
do
    for j in $(seq 1 $N)
    do
        ./counter $i >> res.txt
    done
echo
done
