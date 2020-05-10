# Parallel Divide and Conquer
The purpose of this assignment was to implement a parallel version of the Divide and Conquer skeleton. I started from a given sequential implementation, the one in [this file](DaC_sequential.cpp).

## Challenges
A problem that I faced since the beginning was that a parallel version of the DaC algorithm needed to keep under control the degree of parallelism of the program. 
In fact, being DaC an algorithm that **recurses** untill the base case is reached, letting the concurrency level under no leash would mean to create hundreds, possibly thousands, of threads.  
For this reason I added a parameter called ```cutoff``` used to switch to the sequential version of the DaC algorithm from a certain point on. 
The *user* of the skeleton can then determine a good check to use as a stopping condition in the function ```checkCutoff()```.

## Design choices
I decided to base my implementation of the *parallel DaC* on the **template method** design pattern. 
There basically are two *frozen spots*, that define the general behavior of the parallel DaC framework, and several *hot spots*, abstract methods that users of the framework have to implement in their concrete classes to define the custom behavior of the algorithm.  
The frozen spots are the methods ```run_sequential``` and ```run_parallel``` in the class [DCFramework](DCFramework.hpp). These two methods use abstract declarations of the methods ```baseCase, solve, divide conquer, checkCutoff```.

## Use
To implement a custom version of the algorithm the user has to declare a new class, extending ```DCFramework``` and implementing all the abstract methods (the hot spots).
Then is sufficient to create an object of the concrete class and call ```run_parallel``` on it, passing the input problem as a parameter.  
The method ```run_sequential```, used to run the DaC algorithm sequentially and used by ```run_parallel```, is left available to the user in case she/he wants to try the sequential version of the DaC algorithm for comparison reasons. 


## Example usage
To show a real usage of the algorithm I created the class [MergeSort](MergeSort.hpp). Part of the implementation of the MergeSort is based on the work of [Tiziano de Matteis](https://github.com/TizianoDeMatteis).


## Building
To generate the build system do:  
```
mkdir -p build
cd build
cmake ..
```
in the root of the cloned project.  

Now build the project:
```
cmake --build .
```


## Running
The executable can be found in the ```build/``` directory. Just run it with:

```./build/DivideAndConquer_ParallelFramework``` 


## Acknowledgments
This project was developed for an assignment of the course [Parallel and Distributed Systems](http://didawiki.di.unipi.it/doku.php/magistraleinformaticanetworking/spm/sdpm09support) at University of Pisa under the guide of [Prof. Marco Danelutto](http://calvados.di.unipi.it/paragroup/danelutto/) and [Prof. Massimo Torquati](http://calvados.di.unipi.it/paragroup/torquati/).
