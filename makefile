all: run

build: clean
	@mkdir -p build

	
	@for f in src/asm/*.asm; do \
		echo "   $$f → build/$$(basename $$f .asm).o"; \
		nasm -f elf64 "$$f" -o "build/$$(basename $$f .asm).o"; \
	done

	@for f in src/cpp/*.cpp; do \
		echo "   $$f → build/$$(basename $$f .cpp).o"; \
		g++ -c -Isrc/cpp/headers "$$f" -o "build/$$(basename $$f .cpp).o"; \
	done

	@g++ -no-pie build/*.o -lraylib -lm -ldl -lpthread -lGL -lX11 -o build/output


run: build
	@./build/output

clean:
	@rm -rf build
