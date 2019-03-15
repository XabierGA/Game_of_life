CFLAGS = -w
LDFLAGS = -lm -fopenmp
generate_with_01:${argument}
	@gcc $(CFLAGS) -O1 -o first_optimization ${argument} $(LDFLAGS)

generate_with_02:${argument}
	@gcc $(CFLAGS) -O2 -o second_optimization ${argument} $(LDFLAGS)

generate_with_03:${argument}
	@gcc $(CFLAGS) -O3 -o third_optimization ${argument} $(LDFLAGS)

generate_with_ffast_math:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o ffast_math ${argument} $(LDFLAGS)

generate_with_ffast_native:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -march=native -o ffast_native ${argument} $(LDFLAGS)

generate_with_ffast_msse4:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -msse4.2 -o ffast_native ${argument} $(LDFLAGS)


clean:
	@rm -f first_optimization
	@rm -f second_optimization
	@rm -f third_optimization
	@rm -f ffast_math
	@rm -f ffast_native
	@rm time.txt
