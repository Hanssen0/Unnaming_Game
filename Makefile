obj_path = obj/
objs = $(obj_path)main.o $(obj_path)GameMap.o
Unnaming.out : $(objs)
	g++ -o Unnaming.out $(objs)

source_path = src/
necessary_headers = $(source_path)ConstValue.h $(source_path)CPP.h
$(obj_path)main.o : $(source_path)main.cc $(source_path)main.h $(source_path)Map/GameMap.h $(necessary_headers)
	g++ -c -o $(obj_path)main.o $(source_path)main.cc

$(obj_path)GameMap.o : $(source_path)Map/GameMap.cc $(source_path)Map/GameMap.h $(necessary_headers)
	g++ -c -o $(obj_path)GameMap.o $(source_path)Map/GameMap.cc
