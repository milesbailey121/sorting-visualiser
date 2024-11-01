# Sorting Algorithm Visualization in C++

This project is a visualization tool for sorting algorithms, using the SFML library to render animations and generate sound effects. It displays sorting processes in real-time, showing bar heights that represent values being sorted, and provides auditory feedback with each comparison and swap.

## Features

- **Sorting Algorithms**: Implements Bubble Sort, Selection Sort, and Insertion Sort, each with real-time visualization and auditory feedback.
- **Dynamic Window Sizing**: Automatically scales to fit 80% of the screen's dimensions.
- **Data Visualization**: Bars representing values from 0 to 100 are highlighted during swaps, enhancing understanding of each algorithm's inner workings.
- **Sound Feedback**: Audio tones correlate with bar heights, creating a unique soundscape for each sort.

## Requirements

- **SFML** (Simple and Fast Multimedia Library) for graphics and audio.
- C++ compiler (e.g., `g++`).

### Installing SFML

1. Download SFML from [SFML's official website](https://www.sfml-dev.org/download.php).
2. Follow SFML’s setup guide to link it to your project.

## Setup

1. **Clone the repository**:
   ```bash
   git clone https://github.com/username/sorting-visualization.git
   cd sorting-visualization
   ```

2. **Compile the code**:
   ```bash
   g++ -o sorting_visualization main.cpp -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
   ```

3. **Run the executable**:
   ```bash
   ./sorting_visualization
   ```

## Usage

1. The application opens a window with randomly shuffled bars, representing values from 0 to 100.
2. Choose a sorting algorithm by uncommenting one of the function calls in `main.cpp`:
   ```cpp
   bubbleSort(values, window, soundGen);
   selectionSort(values, window, soundGen);
   insertionSort(values, window, soundGen);
   ```
3. Close the window by pressing the close button in the window frame.

## Code Structure

- **`main.cpp`**: The main application file, which initializes SFML, shuffles values, and runs sorting algorithms.
- **Sorting Functions**: Each algorithm (Bubble Sort, Selection Sort, Insertion Sort) is implemented with visualization and sound.
- **`drawBars` Function**: Utility function that renders bars on the SFML window, highlighting the current elements being compared or swapped.
- **`SoundGenerator` Class**: Custom class to handle sound generation for each value, creating unique tones that match the bar heights.

## Customization

- **Adjust Bar Width**: Modify `BAR_WIDTH` to change the width of each bar in pixels.
- **Adjust Delay**: Modify `MSEC` to increase or decrease the speed of sorting animations.
- **Add New Algorithms**: Add more sorting functions following the template in `main.cpp`, then call them in `main()`.

## Dependencies

- **SFML** (Simple and Fast Multimedia Library)
- **C++ STL Libraries**: `<vector>`, `<iostream>`, `<algorithm>`, `<random>`, `<cmath>`, `<chrono>`, `<thread>`

## License

This project is open-source and available under the MIT License.

---

Enjoy exploring sorting algorithms with a combination of visuals and sound!