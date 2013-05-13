make:	
	gcc -g simulation.c vector_calc.c -lm -o Test -std=c99

clean:
	rm Test
