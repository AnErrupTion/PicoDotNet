mkdir cmake-build-debug

gcc -lubsan -o "main.o" -c "main.c" -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined

gcc -lubsan -o "cmake-build-debug/PicoDotNet_Interpreter" *.o  -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined

rm "main.o"
./cmake-build-debug/PicoDotNet_Interpreter