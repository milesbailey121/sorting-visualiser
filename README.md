# Sorting Algorithm Visualiser

A **Sorting Algorithm Visualiser** built in **C++** using **SFML**. This project allows users to visualise how different sorting algorithms work step-by-step in an interactive and visually appealing interface.  

![Alt text](demo.gif)
## Features  

- **Visualisation of Sorting Algorithms**  
  - Bubble Sort  
  - Insertion Sort  
  - Selection Sort  
  - Merge Sort  
  - Quick Sort  

- **Interactive User Interface**  
  - Select sorting algorithms to visualise.  
  - Pause, reset, and replay sorting animations.  
  - Adjust the size of sorting arrays using a slider.  

- **Custom Elements**  
  - Buttons and sliders designed to resemble native Windows UI components.  
  - Sound Generator to generate unique sounds based on array values

## Technologies  

- **Programming Language**: C++  
- **Graphics Library**: SFML  

## Installation  

### Prerequisites  
- Install SFML (Simple and Fast Multimedia Library).  
- Ensure you have a C++ compiler (e.g., MinGW, g++) and CMake installed.  

### Steps  
1. Clone the repository:  
   ```bash  
   git clone https://github.com/milesbailey121/sorting-Visualiser.git  
   cd sorting-Visualiser  
   ```  

2. Build the project:  
   ```bash  
   mkdir build  
   cd build  
   cmake ..  
   cmake --build .  
   ```  

3. Run the application:  
   ```bash  
   ./bin/main.exe  
   ```  

## File Structure  

- **Algorithms/**: Contains the implementations of sorting algorithms.  
- **Window/**: Contains code for UI elements such as buttons, sliders, and window management.  
  - **Assets/**: Includes textures, fonts, and button state configurations.  
- **Sound/**: (Optional) Placeholder for sound effects.  
- **SortingState**: Manages the state of the Visualisation, such as sorting steps and indices.  

## Future Features  

- Add more sorting algorithms (Heap Sort, Radix Sort, etc.).  
