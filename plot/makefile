CFLAGS = -w
LDFLAGS = -lm -fopenmp -lpthread
generate_cores_1:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o one_core ${argument} $(LDFLAGS)
generate_cores_2:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o two_core ${argument} $(LDFLAGS)
generate_cores_3:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o third_core ${argument} $(LDFLAGS)
generate_cores_4:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o fourth_core ${argument} $(LDFLAGS)
generate_cores_5:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o fifth_core ${argument} $(LDFLAGS)
generate_cores_6:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o six_core ${argument} $(LDFLAGS)
generate_cores_7:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o seven_core ${argument} $(LDFLAGS)
generate_cores_8:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o eigth_core ${argument} $(LDFLAGS)
generate_cores_9:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o nine_core ${argument} $(LDFLAGS)
generate_cores_10:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o ten_core ${argument} $(LDFLAGS)
generate_cores_11:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o eleven_core ${argument} $(LDFLAGS)
generate_cores_12:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o twelve_core ${argument} $(LDFLAGS)
generate_cores_13:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o thirteen_core ${argument} $(LDFLAGS)
generate_cores_14:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o fourteen_core ${argument} $(LDFLAGS)


clean:
	@rm -f one_core
	@rm -f two_core
	@rm -f third_core
	@rm -f fourth_core
	@rm -f fifth_core
	@rm -f six_core
	@rm -f seven_core
	@rm -f eigth_core
	@rm -f nine_core
	@rm -f ten_core
	@rm -f eleven_core
	@rm -f twelve_core
	@rm -f thirteen_core
	@rm -f fourteen_core
	@rm time.txt
