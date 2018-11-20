# compilation

Compile this program as follows:

```
gcc -I./ ply_io.c obj_to_ply.c -o obj_to_ply -lm
```

# usage

Convert the obj file to the ply file:

```
cat obj.file | obj_to_ply > ply.file
```

