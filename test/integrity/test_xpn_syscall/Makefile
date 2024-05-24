# Definitions

 MAKE         = make -s
 CC           = /home/lab/bin/mpich/bin/mpicc
 MYHEADER     = -I../../../include/ -I../../../include/base
 MYLIBPATH    = -L../../../src/base
 LIBRARIES    = -lpthread -ldl
 MYFLAGS      = -O2 -Wall -D_REENTRANT -DPOSIX_THREADS -DHAVE_CONFIG_H

# Rules
all: prueba_create create_write_close open_read_close openat_read_close fopen_fread_fclose create_fwrite_fclose open64_read_close create_pwrite_close open_lseek_close open_lseek64_close open_fseek_close open_pread_close create_ftruncate_close __open_2_read_close open_stat_close rename unlink remove mkdir rmdir open_ftell_close access dup_read_close chdir chmod open_creat_read_close

prueba_create: prueba_create.o
	$(CC) -o prueba_create prueba_create.o $(MYLIBPATH) $(LIBRARIES)

create_write_close: create_write_close.o
	$(CC) -o create_write_close create_write_close.o $(MYLIBPATH) $(LIBRARIES)

open_read_close: open_read_close.o
	$(CC) -o open_read_close open_read_close.o $(MYLIBPATH) $(LIBRARIES)

openat_read_close: openat_read_close.o
	$(CC) -o openat_read_close openat_read_close.o $(MYLIBPATH) $(LIBRARIES)

fopen_fread_fclose: fopen_fread_fclose.o
	$(CC) -o fopen_fread_fclose fopen_fread_fclose.o $(MYLIBPATH) $(LIBRARIES)

create_fwrite_fclose: create_fwrite_fclose.o
	$(CC) -o create_fwrite_fclose create_fwrite_fclose.o $(MYLIBPATH) $(LIBRARIES)

open64_read_close: open64_read_close.o
	$(CC) -o open64_read_close open64_read_close.o $(MYLIBPATH) $(LIBRARIES)

create_pwrite_close: create_pwrite_close.o
	$(CC) -o create_pwrite_close create_pwrite_close.o $(MYLIBPATH) $(LIBRARIES)

open_lseek_close: open_lseek_close.o
	$(CC) -o open_lseek_close open_lseek_close.o $(MYLIBPATH) $(LIBRARIES)

open_lseek64_close: open_lseek64_close.o
	$(CC) -o open_lseek64_close open_lseek64_close.o $(MYLIBPATH) $(LIBRARIES)

open_fseek_close: open_fseek_close.o
	$(CC) -o open_fseek_close open_fseek_close.o $(MYLIBPATH) $(LIBRARIES)

open_pread_close: open_pread_close.o
	$(CC) -o open_pread_close open_pread_close.o $(MYLIBPATH) $(LIBRARIES)

create_ftruncate_close: create_ftruncate_close.o
	$(CC) -o create_ftruncate_close create_ftruncate_close.o $(MYLIBPATH) $(LIBRARIES)

__open_2_read_close: __open_2_read_close.o
	$(CC) -o __open_2_read_close __open_2_read_close.o $(MYLIBPATH) $(LIBRARIES)

open_stat_close: open_stat_close.o
	$(CC) -o open_stat_close open_stat_close.o $(MYLIBPATH) $(LIBRARIES)

rename: rename.o
	$(CC) -o rename rename.o $(MYLIBPATH) $(LIBRARIES)

unlink: unlink.o
	$(CC) -o unlink unlink.o $(MYLIBPATH) $(LIBRARIES)

remove: remove.o
	$(CC) -o remove remove.o $(MYLIBPATH) $(LIBRARIES)

mkdir: mkdir.o
	$(CC) -o mkdir mkdir.o $(MYLIBPATH) $(LIBRARIES)

rmdir: rmdir.o
	$(CC) -o rmdir rmdir.o $(MYLIBPATH) $(LIBRARIES)

open_ftell_close: open_ftell_close.o
	$(CC) -o open_ftell_close open_ftell_close.o $(MYLIBPATH) $(LIBRARIES)

access: access.o
	$(CC) -o access access.o $(MYLIBPATH) $(LIBRARIES)

dup_read_close: dup_read_close.o
	$(CC) -o dup_read_close dup_read_close.o $(MYLIBPATH) $(LIBRARIES)

chdir: chdir.o
	$(CC) -o chdir chdir.o $(MYLIBPATH) $(LIBRARIES)

chmod: chmod.o
	$(CC) -o chmod chmod.o $(MYLIBPATH) $(LIBRARIES)

open_creat_read_close: open_creat_read_close.o
	$(CC) -o open_creat_read_close open_creat_read_close.o $(MYLIBPATH) $(LIBRARIES)

%.o: %.c
	$(CC) $(CFLAGS) $(MYFLAGS) $(MYHEADER) -c $< -o $@

clean:
	rm -f ./*.o
	rm -f ./prueba_create ./create_write_close ./open_read_close ./openat_read_close ./fopen_fread_fclose ./create_fwrite_fclose ./open64_read_close ./create_pwrite_close ./open_lseek_close ./open_lseek64_close ./open_fseek_close ./open_pread_close ./create_ftruncate_close ./__open_2_read_close ./open_stat_read_close ./rename ./unlink ./remove ./mkdir ./rmdir ./open_ftell_close ./access ./dup_read_close ./chdir ./chmod ./open_creat_read_close