# vars
cmsgl="GCC   :   '"
nmsgl="NASM  :   '"
cmsgm="' -> '"
cmsge="'"
outdir="Bin/Objs/"
cdir="Source"
inf=""
outf=""

kern_cargs="-nostdlib -ffreestanding -Wall -Wextra -fno-exceptions -Wno-write-strings -Wno-unused-parameter -Wno-unused-variable"

# Clear the console
clear

# Setup build directory
rm -r "Bin"
mkdir "Bin"
mkdir "Bin/Objs/"

# Start.asm
cdir="Source/" outdir="Bin/" inf="Start.asm" outf="Start.o"
nasm -felf32 "$cdir$inf" -o "$outdir$outf"
echo "$nmsgl$cdir$inf$cmsgm$outdir$outf$cmsge"

# ----------------------------------------------- KERNEL --------------------------------------------------------------
cdir="Source/"
outdir="Bin/Objs/"
files=$(find $cdir -name "*.c" -print)

for file in $files; do
    inf="$(basename $file)"
    outf="$(echo ${inf%.*}.o)"
    i686-elf-gcc -Iinclude -I../libk/include -c "$file" -o "$outdir$outf" $kern_cargs
    echo "$cmsgl$inf$cmsgm$outdir$outf$cmsge"
done
# Link all files
cd 'Bin/Objs'
i686-elf-ld -T '../../Build/linker.ld' -o '../Kernel.bin' "../Start.o" *.o
cd '../../'

objdump -t -dwarf -Mintel "Bin/Kernel.bin" > "Build/Dumps/Kernel.dump"
