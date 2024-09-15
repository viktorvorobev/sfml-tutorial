[![CI checks](https://github.com/viktorvorobev/sfml-tutorial/actions/workflows/ci.yml/badge.svg)](https://github.com/viktorvorobev/sfml-tutorial/actions/workflows/ci.yml)
[![linkedin](https://img.shields.io/badge/LinkedIn-0077B5?&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/mr-viktor-vorobev/)
[![](https://img.shields.io/badge/My%20CV-00A98F?logo=googledrive&logoColor=white)](https://drive.google.com/file/d/1e45Z14JU7wt4H0zuaQfNd0Xz4Yu0q1h-/view?usp=share_link)


# SFML tutorial

Playing around with code from [this tutorial](https://youtu.be/t0z3RojiKFg?si=n48Uq9axw4pKvF5g)

## Building

1. Clone the repo
2. Prepare to build  
   ```bash
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
   ```
3. Go to build directory
   ```bash
   cd build
   ```
4. Compile:
   ```bash
   make
   ```
5. Run the demo:
   ```bash
   cd bin
   ./sfml-tutorial
   ```

> [!tip]
> To exit demo press ESC

> [!warning]
> Known issue: there is a bug with SFML stuggles to find the star texture.
> That's why it is launched from the `bin` directory.
> Otherwise there will be just squares.
