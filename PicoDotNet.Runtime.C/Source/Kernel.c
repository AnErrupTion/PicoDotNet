
void main(void* mboot)
{
    char* vram = (char*)0xB8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2)
    {
        vram[i]     = 'X';
        vram[i + 1] = 0x1E;
    }
}