# ARM

## SUMMARY:
The goal of this project was to implement a visualizer for PGM3D file. The test file was a 64*64*64 representation of the shepplogan phantom.
In order to do so we used QT for the interface with OpenGL to handle the 3D reconstruction.

The first step was to implement a parser to read the PGM3D file (Data::readPGM3D), this function goes through the file and extract the value of each bloc and
store it in an array (rawData) to avoid having to read the file each time we want to update the display.
In a first time we used a volumetric representation by simply going through the raw data array and drawing every faces of every cubes that wasn't black.
By adding transparancy we optained a first valid display of our file.

To improve this implementation we wanted to reduce the work needed to display a frame. So, we tried to display only the face needed (no need to display a
face between two cube of same value). To do this we created two more array (Data::vertices, containing all the vertices with their x,y and z coordinate and
Data::faces containing the indices of the 3 vertices describing the face and the color of the face). To fill these arrays we tried two methods:
    -Data::createObject: We run through our rawData array and for each bloc we compare its color value with three neighbors ([x-1, y, z], [x, y-1,z] and [x,y, z-1])
  If they have differents colors we display the darker one as long as it's not black.
    -Data::createCube:

We also added control to inspect the object, when you move the mouse while keeping the left click down you can rotate the object around it's center, you can also
zoom-in/zoom-out by using the mouse wheel.

When we implemented the first method we added transparancy to be able to see what is inside and not only the border but we observed some issues when we rotate
around the object, we always display the faces in the same order regardless of the orientation of the object, which cause the transparancy to ignore important faces.
To fix it we added a Z-sorting function to sort our faces array from the further to the closest at each frames which resolved the previous issue.

## IMPROVEMENT:
To further improve our visualizer we thought of some improvement. Right now we display each faces separately, but we could create groups of faces which are next
to each other to reduce the number of faces we display. To do so, we should identify two bloc of the same color and merge them in a single and bigger block.
This could easily be added to our method, since we already identify such bloc but we ignore them since their shared face do not interest us. So we only need to
add the idea explained above to this case.

## HOW TO USE:
- Start the project using QT
- Select the PGM3D file in the dialog box
- Rotate using the left click and zoom using the wheel

![result1](https://github.com/Aelly/ARM/blob/master/ARM1.png)
![result2](https://github.com/Aelly/ARM/blob/master/ARM2.png)
