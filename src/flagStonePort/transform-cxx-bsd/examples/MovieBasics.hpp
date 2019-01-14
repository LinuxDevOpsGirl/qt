/*
 *  MovieBasics.cpp
 *  Transform Examples
 *
 *  Created by smackay on Tue Mar 04 2003.
 *  Copyright (c) 2001-2004 Flagstone Software Ltd. All rights reserved.
 *
 *  This code is distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 *  EXPRESS OR IMPLIED, AND Flagstone HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING
 *  WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 *  PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
 */

#ifndef __MovieBasics_h__
#define __MovieBasics_h__ 1

/*
 * This example shows some of the basic objects used to create a movie. 
 *
 * To run this example, type the following on a command line:
 *
 * examples --example MovieBasics [--resultDir path]
 *
 * where
 *
 *     resultDir is the directory where the Flash file generated by the example 
 *     is written to.
 */
class MovieBasics
{
public:
    MovieBasics(map<string, string>& options)
    {
        FSMovie movie;

        /*
        * The movie bounds are specified in twips. The bounding rectangle is defined
        * by two points: the lower left corner and the upper right corner of the
        * rectangle that encloses the area.
        *
        * The bounding rectangle also defines the coordinate range for the x and y axes.
        * Here the coordinates for the x and y axes range from -4000 to +4000. A point with
        * the coordinates (0,0) lies in the center of the screen.
        *
        * If the coordinates of the corners were specified as (0,0) and (4000, 4000) the
        * size of the screen is still the same however the center of the screen now
        * lies at (2000,2000)
        */
        int xLower = -4000;
        int yLower = -4000;
        int xUpper = 4000;
        int yUpper = 4000;

        movie.setFrameSize(FSBounds(xLower, yLower, xUpper, yUpper));

        /*
        * Set the frame rate at which the movie will be played.
        */
        float framesPerSecond = 1.0f;

        movie.setFrameRate(framesPerSecond);

        /*
        * Set the movie's background colour to light blue. The background colour
        * only be set once and should be the first object added to a movie. If no
        * background colour is specified then the Flash Player will set it to white.
        */
        movie.add(new FSSetBackgroundColor(FSColorTable::lightblue()));

        /*
        * Define a shape to be displayed. Each object must be assigned a unique identifier
        * which is used to reference the object when adding, updating or removing it from
        * the display list. The movie object keeps track of the identifier to guarantee
        * each is unique.
        */
        int identifier = movie.newIdentifier();

        int width = 4000;
        int height = 4000;

        FSBounds bounds(-2000, -2000, 2000, 2000);

        FSVector<FSLineStyle*> lineStyles(1);
        FSVector<FSFillStyle*> fillStyles(1);

        lineStyles[0] = new FSSolidLine(20, FSColorTable::black());
        fillStyles[0] = new FSSolidFill(FSColorTable::red());

        /*
        * Create the outline of the shape. All drawing is performed using a series
        * of line an curve objects. The FSShapeStyle class is used to select the 
        * current line and fill styles and to perform absolute moves within the 
        * coordinate space of the shape (relative moves can be performed by drawing
        * line when no line style is selected - set the line style to 0).
        */

        FSShape shape;

        shape.add(new FSShapeStyle(1, 1, 0, -width/2, -height/2));
        shape.add(new FSLine(width, 0));
        shape.add(new FSLine(0, height));
        shape.add(new FSLine(-width, 0));
        shape.add(new FSLine(0, -height));

        FSDefineShape* rectangle = new FSDefineShape(identifier, bounds, fillStyles, lineStyles, shape);

        /*
        * Add the rectangle to the movie. All shapes and objects must be defined before
        * they can be placed on the display list and rendered on the Flash Player's
        * screen.
        */
        movie.add(rectangle);

        /*
        * Place the shape on the display list. See the DisplayList example for the set of
        * objects that are used to add, update and remove objects from the display list.
        */      
        movie.add(new FSPlaceObject(identifier, 1, 0, 0));

        /*
        * Show the contents of the display list. Frames are delimited by successive
        * FSShowFrame objects.
        */
        movie.add(new FSShowFrame());

        saveMovie(movie, stringOption(options, "resultDir"), "MovieBasics.swf");
    }
};

#endif