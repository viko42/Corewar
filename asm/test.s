.name "toto"
.comment "jaustryk's algoritm"

	sti	r1, %:live, %42
	and	r1, %0, r1

lol:
live:	live	%1
		zjmp	%:live

label:
	live	%1
