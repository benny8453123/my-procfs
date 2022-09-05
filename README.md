# my-procfs
Learning of using procfs simpily

## how to test?
**First insmod**
**Second sudo -s***

1. `ll /proc | grep my`
```
root@ben-virtual-machine:/home/ben# ll /proc | grep my 
dr-xr-xr-x   3 root             root                           0  九   5 23:26 my-proc-dir/
-rw-r--r--   1 root             root                           0  九   5 23:26 my-proc-seq
-rw-r--r--   1 root             root                           0  九   5 23:22 my-proc-seq-buf
```

2. `cat /proc/my-proc-seq`
```
root@ben-virtual-machine:/home/ben# cat /proc/my-proc-seq
This is my-proc-seq
```

3. `cd /proc/my-proc-dir/; ll`
```
root@ben-virtual-machine:/proc# cd /proc/my-proc-dir/; ll
total 0
dr-xr-xr-x   3 root root 0  九   5 23:26 ./
dr-xr-xr-x 404 root root 0  九   5 22:47 ../
-rw-r--r--   1 root root 0  九   5 23:28 my-data
```

4. `echo "hello" > /proc/my-proc-dir/my-data` than `cat /proc/my-proc-dir/my-data`
```
root@ben-virtual-machine:/# echo "hello" > /proc/my-proc-dir/my-data 
root@ben-virtual-machine:/# cat /proc/my-proc-dir/my-data
hello
```

5. `cat /proc/my-proc-seq-buf`
```
root@ben-virtual-machine:/# cat /proc/my-proc-seq-buf 
0:	This
1:	is
2:	seq buf
```
