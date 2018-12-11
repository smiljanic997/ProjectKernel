[global get_second]
get_second:
	cli
	mov al, 0x00
	out 0x70, al
	in al, 0x71
	sti
	ret

[global get_minute]
get_minute:
	cli
	mov al, 0x02
	out 0x70, al
	in al, 0x71
	sti
	ret
	
[global get_hour]
get_hour:
	cli
	mov al, 0x04
	out 0x70, al
	in al, 0x71
	sti
	ret

[global get_update_in_progress_flag]
get_update_in_progress_flag:
	cli
	mov al, 0x0A
	out 0x70, al
	in al, 0x71
	sti
	ret
