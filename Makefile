exec = Build/launcher13.exe
stdver = 17
compiler = g++

src =\
	$(wildcard src/*.cpp)

obj = $(src:.cpp=.o)

srch =\
	$(wildcard include/*.hpp)

objh = $(srch:.hpp=.hpp.gch)

inc =\
	-I include\

flags =\
	-Werror\
	-Wall\
	-Wextra\
	-g\
	-std=c++$(stdver)\
	-static-libgcc\
	-static-libstdc++\

obj_command =\
	$(compiler) $(flags) $(inc) -c $< -o $@ -Wl,-Bstatic

link_command =\
	$(compiler) $(flags) $(obj) -o $(exec)

$(exec): $(objh) $(obj)
	$(link_command)

%.o: %.cpp
	$(obj_command)

%.hpp.gch: %.hpp
	$(obj_command)

clean:
	rm $(obj)
	rm $(exec)

full_clean:
	rm $(obj)
	rm $(objh)
	rm $(exec)

clean_headers:
	rm $(objh)

clean_obj:
	rm $(obj)

clean_exec:
	rm $(exec)

re_link:
	rm $(exec)
	$(link_command)