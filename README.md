# compression
A binary compression algorithm. This started as a fun idea for a compression algorithm, and became a way to inflate data instead.

### Idea

Represent each string of 0s and 1s as one giant number.

###

Use ```make``` to compile encode.cc and decode.cc
Run ```./encode <file_name> > output``` to encode the contents of ```file_name``` and store the encoded text in ```output```.
Run ```./decode``` to decode the contents of ```output``` by default. Decoded text will be stored in ```binary_data.bin```.