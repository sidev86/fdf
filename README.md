<h1>Fdf</h1>


<h2>Description</h2>

FDF is a simple wireframe model renderer designed to represent 3D landscapes. The program reads <code>.fdf</code> files that store a grid of coordinates (x, y, z) and renders the corresponding 3D model using line segments. This project demonstrates basic 3D rendering techniques, specifically isometric projections, using the MiniLibX library (a small graphics library, developed by 42 school, designed for use with the X Window System).

<h2>Features</h2>
<ul>
  <li><strong>Projection:</strong> The 3D map model is rendered in isometric view.</li>
  <li><strong>File Input:</strong> Accepts <code>.fdf</code> files as input, where each number represents a point in 3D space (x, y are positions on the map grid, and z represents the altitude)</li>
  <li><strong>Smooth window management</strong>: The graphical window supports minimization, focus switching, and clean exit using ESC or the window close button.</li>
</ul>

 <h2>The <code>.fdf</code> File Format </h2>
  <p>The <code>.fdf</code> file is basically the map representation in the form of a grid of points where:</p>
  <ul>
    <li>Horizontal position corresponds to the x-axis.</li>
    <li>Vertical position corresponds to the y-axis.</li>
    <li>Altitude corresponds to the z-value.</li>
  </ul>
  <p>Example of a <code>.fdf</code> file:</p>
  <pre><code>0 0 0 0
0 1 1 0
0 1 0 0
0 0 0 0</code></pre>





README WIP...
