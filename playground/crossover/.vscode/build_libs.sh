if [ $# != 1 ]; then
	exit 1
fi

for file in "$PWD/"*.c; do
	[ -f "$file" ] || break
	file_no_extensions="`realpath \"$file\" --relative-to=\"$PWD\"`"

	# gcc -std=c11 -fPIC -c $file
	gcc -fPIC -c "$file" -o "${file_no_extensions%.*}.o"
done

gcc *.o -shared -o "$1".so
rm *.o

# gcc -rdynamic -shared "$PWD/"*.o -o ../simple/bin/libsimple.so
