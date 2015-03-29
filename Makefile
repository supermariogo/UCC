CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

UCC: $(OBJ_FILES)
	g++ -DUNIX -o $@ $^

obj/%.o: src/%.cpp
	g++ -DUNIX -c -o $@ $<

clean:
	rm -f bin/UCC bin/UCC.exe
	rmdir --ignore-fail-on-non-empty bin
