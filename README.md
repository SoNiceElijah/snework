# snework

New science work repository x3 

## Data create application

Program produce .csv data for analysis

### Build application instructions

1. Create build folder
```
mkdir build
```
2. Navigate to build folder
```
cd build
```
3. Configure cmake
```
cmake ..
```
4. Build 
```
cmake --build . --target sneapp --parallel 4 --config Release
```

### Use application instructions

```
./sneapp <output .cvs file path> <input constants .bin file path> <output mask> <step> <offset> <line> <length>
```


