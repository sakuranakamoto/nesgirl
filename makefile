src_dir = src
bin_dir = bin
err_flags = -Wall -Wextra -Werror
link_files = src/cart.c src/error.c 

normal:
	gcc $(link_files) $(src_dir)/nesgirl.c -o $(bin_dir)/nesgirl

debug:
	gcc -g $(link_files) $(err_flags) $(src_dir)/nesgirl.c -o $(bin_dir)/nesgirl