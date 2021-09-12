for data_structure in set list sorted_vector unsorted_vector
    do
        for key_max in 64 128 256 1024 4096
            do
                echo $data_structure $key_max $iterations
                ./obj64/Main.exe -a 10000000 -b $data_structure -c 0 -d $key_max 
            done
    done