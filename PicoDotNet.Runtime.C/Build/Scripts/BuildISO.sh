# create required directories
mkdir "Bin/iso"
mkdir "Bin/iso/boot"
mkdir "Bin/iso/boot/grub"

# create ISO image
cp 'Bin/Kernel.bin' 'Bin/iso/boot/kernel.bin'
cp 'Build/grub.cfg' 'Bin/iso/boot/grub/grub.cfg'
grub-mkrescue -o 'Images/pico.iso' 'Bin/iso'

# create floppy image
cp 'Images/pico.iso' 'Images/pico_flp.img'