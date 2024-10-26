<h1>Fdf</h1>


<h2>Description</h2>

FDF is a simple wireframe model renderer designed to represent 3D landscapes. The program reads <code>.fdf</code> files that store a grid of coordinates (x, y, z) and renders the corresponding 3D model using line segments. This project demonstrates basic 3D rendering techniques, specifically isometric projections, using the MiniLibX library (a small graphics library, developed by 42 school, designed for use with the X Window System).

<h2>Features</h2>
<ul>
  <li><strong>Projection:</strong> The 3D map model is rendered in isometric view.</li>
  <li><strong>File Input:</strong> Accepts <code>.fdf</code> files as input, where each number represents a point in 3D space (x, y are positions on the map grid, and z represents the altitude)</li>
  <li><strong>Smooth window management</strong>: The graphical window supports minimization, focus switching, and clean exit using ESC or the window close button.</li>
</ul>

<h2>Understanding the <code>.fdf</code> File Format</h2>

  <p>The <code>.fdf</code> file contains the data that describes the 3D coordinates of a landscape. Each number in the file represents a point in space and corresponds to specific coordinates along the x, y, and z axes. The format is designed to be simple, and each value represents the altitude of a point in a grid, while the position of the value itself corresponds to the x and y coordinates.</p>

  <h3>File structure</h3>
  <ul>
    <li>Each line in the file corresponds to a row of points along the y-axis.</li>
    <li>Each number within a row represents a point along the x-axis.</li>
    <li>The value of each number represents the altitude (z-axis) at that specific x and y coordinate.</li>
  </ul>

  <p>For example, consider the following <code>.fdf</code> file:</p>
  <pre><code>  0 0 0 0
  0 1 1 0
  0 1 0 0
  0 0 0 0</code></pre>

  <p>In this case:</p>
  <ul>
    <li>The first row (<code>0 0 0 0</code>) corresponds to the first line of the grid, with four points all at zero altitude.</li>
    <li>The second row (<code>0 1 1 0</code>) corresponds to the second line of the grid, where two middle points have an altitude of 1.</li>
    <li>This pattern continues for the rest of the file.</li>
  </ul>

  <h3>How It Works</h3>
  <p>When the <code>.fdf</code> file is loaded into the <code>fdf</code> program:</p>
  <ol>
    <li>Each number is read and interpreted as the altitude (z) at that specific (x, y) position.</li>
    <li>The program creates a 3D wireframe model by connecting each point using line segments (edges) based on the coordinates and altitude values.</li>
    <li>The final result is a 3D landscape that is displayed in an isometric projection.</li>
  </ol>

  <p>This simple file format allows you to define and visualize landscapes using just a grid of numbers, making it easy to create 3D models based on elevation data.</p>

 
 <h2>Controls</h2>
  <table>
    <thead>
      <tr>
        <th>Action</th>
        <th>Key Control</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>Zoom</td>
        <td>Mouse Scroll</td>
      </tr>
      <tr>
        <td>Change Altitude</td>
        <td>+ / -</td>
      </tr>
      <tr>
        <td>X-Axis Rotation</td>
        <td>Q / E</td>
      </tr>
      <tr>
        <td>Y-Axis Rotation</td>
        <td>A / D</td>
      </tr>
      <tr>
        <td>Z-Axis Rotation</td>
        <td>Z / C</td>
      </tr>
      <tr>
        <td>Change Projection (Isometric/Parallel)</td>
        <td>I / P</td>
      </tr>
      <tr>
        <td>Generate a Random Gradient Color</td>
        <td>J</td>
      </tr>
    </tbody>
  </table>

 <h2>Usage (linux systems)</h2>
 <ol>
   <li>Go into the minilibx_linux folder and type <code>make</code> to compile the minilibx library</li>
   <li>Go back to the previous folder and type <code>make</code> to generate the <code>fdf</code> executable file</li>
   <li>After compiling, execute the program by passing the path to your <code>.fdf</code> file as an argument. For example:</li>
    <pre><code>./fdf path/to/your_file.fdf</code></pre>
 </ol>
 



README WIP...
