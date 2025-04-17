#!/bin/bash

set -e
make clean
make


dd if=/dev/random bs=1024 count=1 of=random.bin

python3 -c "import base64; open('random.a85', 'wb').write(base64.a85encode(open('random.bin', 'rb').read()))"

./ascii85 -e < random.bin > encoded.a85
./ascii85 -d < random.a85 > decoded.bin

if ! cmp -s random.a85 encoded.a85; then
    echo "encoding failure"
    exit 1
fi

if ! cmp -s random.bin decoded.bin; then
    echo "decoding failure"
    exit 1
fi

echo "all tests passed"

make clean
