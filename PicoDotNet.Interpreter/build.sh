gcc -lubsan -o "main.o" -c "main.c" -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined

gcc -lubsan -o "PicoDotNet_Interpreter" *.o  -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined

rm "main.o"
./PicoDotNet_Interpreter