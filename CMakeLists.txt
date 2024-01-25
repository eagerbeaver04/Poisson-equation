cmake_minimum_required(VERSION 3.26)
project(PoissonEquation)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(PoissonEquation
        .gitignore
        List.h
        Node.h
        Source.cpp
        Sparse.h
        Node.cpp
        List.cpp
        Sparse.cpp
        Iterator.cpp
        "Cholesky decomposition/CholeskyDecomposition.cpp"
        PreconditionedConjugateGradientsMethod/PCG.h
        PreconditionedConjugateGradientsMethod/PCG.cpp
        PoissonEquation/PoissonEquation.h
        PoissonEquation/PoissonEquation.cpp
        Matrix.h
        Matrix.cpp
)
