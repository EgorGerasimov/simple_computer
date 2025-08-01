
.PRHONY: all style build clean run

all: style build

run: build
	@./console/console

run_font: font
	@./console/font
	@rm -rf console/font

build_sa:
	@make -C myTerm
	@make -C mySimpleComputer 
	@make -C simpleassembler 

font:
	@make -C myTerm
	@make -C mySimpleComputer 
	@make -C myBigChars
	@make -C console font

build: style run_font
	@make -C myReadKey
	@make -C console 

style: 
	@clang-format --style GNU -i */*.c */*.h

clean:
	@rm -rf console/myBigChars console/myTerm console/mySimpleComputer console/myReadKey obj console/font.bin console/console simpleassembler/simpleassembler */*.o