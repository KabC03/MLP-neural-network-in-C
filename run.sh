#Run everything
#12 Oct

clear
mkdir -p output
clang ./libraries/*.c ./run/*.c -Werror -Wall -fsanitize=address -o ./output/exec

./output/exec



