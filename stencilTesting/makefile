all: basicSceneSource.cpp objectOutlining.cpp shader_m.h ../glad.c stb_image.h stb_image.cpp camera.h
	g++ -o basicScene basicSceneSource.cpp shader_m.h ../glad.c stb_image.h stb_image.cpp camera.h -lglfw -ldl -std=gnu++0x 
	g++ -o objectOutlining objectOutlining.cpp shader_m.h ../glad.c stb_image.h stb_image.cpp camera.h -lglfw -ldl -std=gnu++0x 
clean: 
	$(RM) basicScene
