# SNEWORK

New science work repository x3 

## Repository structure

```

├── analysis [ Python scripts for data analysis ]
├── header [ Data produce application headers ]
├── infrastructure [ node js scripts, that start/controll data produsing ]
├── interface [ Task triggers handler ]
├── snedata [ Data fordel template ]
├── source [ Data produce application sources ]
└── tool [ Common tools and test solutions ]

```

## Data create application

Program produce .csv data by predefined system of differential equations usgin .bin file, which contains constants. 

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

| Argument | Default | Description |
| --- | --- | --- |
| **output path** | ./res.csv | Specifies output file path |
| **input file** | ./consts.bin | Specifies input file path |
| **mask** | 0x0FFF | Output values mask. Bit set to 1 => vector element will be included in output |
| **step** | 0.01 | RK-4 method step |
| **offset** | 0 | Number of steps that will be skipped |
| **line** | 25 | Number of setps that calculated per iteration |
| **length** | 40000 | Number of iterations |


## Data produce pipeline

Data pipeline controls from ```infrastructure/jobs.js```. Data flow scheme:

```
Job initiation [ interface/main.js ] 
=====> job configuration [ infrastructure/jobs.js ]
=====> consts.bin generation for each case
=====> {application} produce data for each consts.bin  
=====> data analysis with python [ infrastructure/jobs.js ]
=====> output data generation [ analysis/*.py ]
=====> job finished notification (optional) [ interface/main.js ]
```



