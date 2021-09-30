function cpplot() {
	echo scp $1/p/*.plot => 192.168.1.11:$2
	echo cd $1
	echo mkdir p
	echo mv *.plot p
	echo cd p
	echo nohup sshpass -p storage scp *.plot 192.168.1.11:$2 >> ./scplog 2>&1 &	
}

srcbase=/mnt/ssd
destbase=/mnt/data
destnum=$2

for ((k=1; k<=$1; k++))
do
	src=$srcbase$k/b345a84c/newchia/data
	dest=$destbase$[$k+$destnum]
	echo $src
	echo $dest
	cpplot $src $dest
done
echo do run finish!
