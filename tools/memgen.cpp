#include <fcntl.h>
#include <libelf.h>
#include <unistd.h>
#include <array>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <map>

// -lelf

std::map<uint32_t, std::array<uint8_t, 16>> memory_map;

void map_data(Elf32_Addr addr, Elf_Data* data);
void export_data();

int main(int argc, char* argv[0])
{
    if (argc != 2)
    {
        std::cerr << "Input file name missing" << std::endl;
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY, 0);
    if (fd < 0)
    {
        std::perror(argv[1]);
        exit(1);
    }

    elf_version(EV_CURRENT);
    Elf* elf = elf_begin(fd, ELF_C_READ, nullptr);

    Elf_Scn* section = nullptr;
    while ((section = elf_nextscn(elf, section)) != nullptr)
    {
        Elf32_Shdr* header = elf32_getshdr(section);
        if (header->sh_flags & SHF_ALLOC && header->sh_type == SHT_PROGBITS)
        {
            Elf_Data* data = nullptr;
            while ((data = elf_getdata(section, data)) != nullptr)
            {
                map_data(header->sh_addr, data);
            }
        }
    }

    export_data();
}

void map_data(Elf32_Addr addr, Elf_Data* data)
{
    uint8_t* raw_data = (uint8_t*) data->d_buf;
    for (int i = 0; i < data->d_size; ++i)
    {
        const size_t block_addr = addr & ~0xf;
        const size_t index = addr & 0xf;
        memory_map[block_addr][index] = raw_data[i];
        ++addr;
    }
}

void export_data()
{
    for (auto k : memory_map)
    {
        const size_t col = k.first & 0x3ff;
        const size_t row = (k.first & 0x7FFC00) >> 10;
        const size_t bank = (k.first & ~0x7fffff) >> 23;
        uint32_t* data = (uint32_t*) k.second.data();
        for (int i = 0; i < 4; ++i)
        {
            printf("%08x\n", data[i]);
        }
        //printf("%01lx %04lx %03lx %08x%08x%08x%08x\n", bank, row, col, data[3], data[2], data[1], data[0]);
    }
}