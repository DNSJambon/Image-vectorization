# Image-vectorization
PBM to EPS image vectorization project done alone as part of the "MAP401" teaching unit at the Université Grenoble Alpes


## Compilation

Compile all:
```
cd Image-vectorization/
make
```

# User Manual


#### **Program for extracting the contours of a PBM image in EPS format**:

  - File: `contours_en_eps.c`
  
  - To compile:  
    ```bash
    make contours_en_eps
    ```
  
  - To execute:  
    ```bash
    ./contours_en_eps <input_file.pbm> <output_file.eps>
    ```

#### **Program that generates an EPS file representing a simplification by segments from a PBM image and a threshold distance:**

  - Files: `simplification_seg.c`, `simplification_seg.h`
  
  - To compile:  
    ```bash
    make simplification_seg
    ```
  
  - To execute:  
    ```bash
    ./simplification_seg <image_file.pbm> <threshold_distance> <output.eps>
    ```

#### **Program that generates an EPS file representing a simplification by degree-2 Bézier curves from a PBM image and a threshold distance:** 

  - Files: `simplification_courbe2.c`, `simplification_courbe2.h`
  
  - To compile:  
    ```bash
    make simplification_courbe2
    ```
  
  - To execute:  
    ```bash
    ./simplification_courbe2 <image_file.pbm> <threshold_distance> <output.eps>
    ```

#### **Program that generates an EPS file representing a simplification by degree-3 Bézier curves from a PBM image and a threshold distance:**

  - Files: `simplification_courbe3.c`, `simplification_courbe3.h`
  
  - To compile:  
    ```bash
    make simplification_courbe3
    ```
  
  - To execute:  
    ```bash
    ./simplification_courbe3 <image_file.pbm> <threshold_distance> <output.eps>
    ```



