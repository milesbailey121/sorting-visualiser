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

## src File Structure  

### Root Files  
- **main.cpp**: Entry point of the application.  
- **Constants.h**: Contains global constants used throughout the project.  

### Directories  
- **Algorithms/**:  
  - Contains implementations of sorting algorithms and related utilities.  
  - Files:  
    - `Algorithms.cpp`, `Algorithms.h`: Core algorithm implementations.  
    - `AlgorithmStats.cpp`, `AlgorithmStats.h`: Collect and display statistics (e.g., comparisons, swaps).(Unimplemented)  
    - `SortingState.cpp`, `SortingState.h`: Manages the state of the sorting process (e.g., indices, steps).  

- **Sound/**:  
  - Handles sound generation for sorting values.  
  - Files:  
    - `SoundGenerator.cpp`, `SoundGenerator.h`: Generates tones based on array values.  

- **Window/**:  
  - Manages the graphical interface and visualization.  
  - Files:  
    - `GUI.cpp`, `GUI.h`: Builds predefined user interface elements.  
    - `Visualisation.cpp`, `Visualisation.h`: Responsible for rendering the sorting bars and ending animations.  
    - **Assets/**: Contains resources for the UI.  
      - `RoundedRectangle.cpp`, `RoundedRectangle.h`: Rounded Rectangle that's used for other UI elements.  
      - `Button.cpp`, `Button.h`: Button implementation.  
      - `Slider.cpp`, `Slider.h`: Slider implementation for adjusting array sizing.  
      - `RadioButton.cpp`, `RadioButton.h`: Radio Button implementation.
      - `Segoe UI.ttf`: Font used in the UI.   

## Future Features  

- Add more sorting algorithms (Heap Sort, Radix Sort, etc.).  



