#include <fcntl.h>
#include <gelf.h>
#include <libelf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROM_SIZE 8192

uint8_t rom[ROM_SIZE * 4];

int main(int argc, char* argv[]) {
    if (argc != 2)
        return 1;

    if (elf_version(EV_CURRENT) == EV_NONE)
        return 2;

    int fd;
    Elf* elf;
    GElf_Ehdr ehdr;
    GElf_Phdr phdr;

    if ((fd = open(argv[1], O_RDONLY, 0)) < 0)
        return 3;

    if ((elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
        return 4;

    if (gelf_getehdr(elf, &ehdr) != &ehdr)
        return 5;

    for (Elf32_Half i = 0; i < ehdr.e_phnum; ++i) {
        if (gelf_getphdr(elf, i, &phdr) != &phdr)
            return 6;

        if ((phdr.p_type & PT_LOAD) && !(phdr.p_type & PT_LOPROC)) {
            off_t start = lseek(fd, 0, SEEK_CUR);
            lseek(fd, phdr.p_offset, SEEK_SET);
            read(fd, &rom[phdr.p_paddr], phdr.p_filesz);
            lseek(fd, start, SEEK_SET);
        }
    }

    uint32_t* data = (uint32_t*) rom;
    for (int i = 0; i < ROM_SIZE; ++i) {
        printf("%08x\n", data[i]);
    }

    close(fd);

    return 0;
}