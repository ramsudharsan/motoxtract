A program to read and extract the partition details in Motorola Bootloader File (motoboot.img)


Installation and Usage:

Step 1: gcc motoxtract.c -o motoxtract

Step 2: chmod a+wx motoxtract

Step 3: ./motoxtract image-name.img


Example: Motorola Moto E XT1022

./motoxtract motoboot.img

Output:

reading file /home/ramsudharsan/workspace/bootloader/motoboot.img

found 6 partititions

dumping partition 0 (        tz), starting offset in file 0x00000400

dumping partition 1 (       rpm), starting offset in file 0x00064400

dumping partition 2 (       sdi), starting offset in file 0x00096400

dumping partition 3 (     aboot), starting offset in file 0x0009E400

dumping partition 4 (      sbl1), starting offset in file 0x0011E400

dumping partition 5 (      sbl1), starting offset in file 0x0015FC00
