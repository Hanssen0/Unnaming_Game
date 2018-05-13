obj_path = obj/
objs = $(obj_path)main.o $(obj_path)GameMap.o $(obj_path)LivingThings.o $(obj_path)Renderer.o
Unnaming.out : $(objs)
	g++ -Wall -std=c++11 -o Unnaming.out $(objs)

source_path = src/
$(obj_path)main.o : $(source_path)main.cc $(source_path)Map/GameMap.h $(source_path)Base.h $(source_path)Graphic/Renderer.h $(source_path)Object/LivingThings.h	| $(obj_path)
	g++ -Wall -std=c++11 -c -o $(obj_path)main.o $(source_path)main.cc

$(obj_path)GameMap.o : $(source_path)Map/GameMap.cc $(source_path)Map/GameMap.h $(source_path)Base.h | $(obj_path)
	g++ -Wall -std=c++11 -c -o $(obj_path)GameMap.o $(source_path)Map/GameMap.cc

$(obj_path)LivingThings.o : $(source_path)Object/LivingThings.cc $(source_path)Object/LivingThings.h $(source_path)Map/GameMap.h | $(obj_path)
	g++ -Wall -std=c++11 -c -o $(obj_path)LivingThings.o $(source_path)Object/LivingThings.cc

$(obj_path)Renderer.o : $(source_path)Graphic/Renderer.cc $(source_path)Graphic/Renderer.h $(source_path)Object/LivingThings.h $(source_path)Map/GameMap.h | $(obj_path)
	g++ -Wall -std=c++11 -c -o $(obj_path)Renderer.o $(source_path)Graphic/Renderer.cc

$(obj_path) :
	mkdir $(obj_path)
