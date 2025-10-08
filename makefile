all: run

build: clean
	@mkdir -p build
	@echo "🧩 Compilando C++..."
	# compila todos los cpp en objetos individuales
	@for f in src/cpp/*.cpp; do \
		echo "   $$f → build/$$(basename $$f .cpp).o"; \
		g++ -c -Isrc/cpp/headers "$$f" -o "build/$$(basename $$f .cpp).o"; \
	done

	@echo "🧱 Ensamblando ASM..."
	@for f in src/asm/*.asm; do \
		echo "   $$f → build/$$(basename $$f .asm).o"; \
		nasm -f elf64 "$$f" -o "build/$$(basename $$f .asm).o"; \
	done

	@echo "🔗 Linkeando → build/output"
	@g++ -no-pie build/*.o -lraylib -lm -ldl -lpthread -lGL -lX11 -o build/output


run: build
	@./build/output

clean:
	@rm -rf build
