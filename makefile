src_dir = src
bin_dir = bin
err_flags = -Wall -Wextra -Werror
link_files = src/cart.c src/error.c  src/nes.c src/memory.c 
rom = rom/donkey\ kong.nes

run:
	gcc -g $(link_files) $(err_flags) $(src_dir)/nesgirl.c -o $(bin_dir)/nesgirl
	$(bin_dir)/nesgirl -f $(rom)

normal:
	gcc $(link_files) $(src_dir)/nesgirl.c -o $(bin_dir)/nesgirl

debug:
	gcc -g $(link_files) $(err_flags) $(src_dir)/nesgirl.c -o $(bin_dir)/nesgirl