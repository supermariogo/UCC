all:
	mkdir -p bin
	g++ -o bin/UCC -DUNIX src/*.cpp

clean:
	rm -f bin/UCC bin/UCC.exe
	rmdir --ignore-fail-on-non-empty bin
