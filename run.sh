#Run everything
#25 Jul

mkdir -p output
clear && clang ./libraries/*.c ./run/main.c -Wall -Werror -fsanitize=address -o ./output/exec && ./output/exec








