## My Radar

### Project Overview

The My Radar project simulates a 2D air traffic control system, showcasing the dynamic interaction between aircraft and control towers. The simulation adheres to specific rules for aircraft movement, collision handling, and control tower functionalities.

### Installation and Setup

**Compile the Project:**
   ```bash
   make
   ```

### Running the Simulation

1. **Start the Simulation:**
   ```bash
   ./my_radar path_to_script
   ```
   Replace `path_to_script` with the path to your custom simulation script.

2. **User Interactions:**
   - `'L' key:** Toggle visibility of hitboxes and control areas.
   - `'S' key:** Toggle visibility of sprites.

### Script Format

- **Aircraft Entry Format:**
  `A x1 y1 x2 y2 speed delay`
- **Control Tower Entry Format:**
  `T x y radius`
- **Example Script Line:**
  `A 800 300 1500 200 4 2`
