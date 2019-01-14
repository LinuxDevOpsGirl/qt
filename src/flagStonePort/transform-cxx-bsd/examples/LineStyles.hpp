/*
 *  LineStyles.cpp
 *  Transform Examples
 *
 *  Created by smackay on Thu May 08 2003.
 *  Copyright (c) 2001-2004 Flagstone Software Ltd. All rights reserved.
 *
 *  This code is distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 *  EXPRESS OR IMPLIED, AND Flagstone HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING
 *  WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 *  PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
 */

/*
 * LineStyles illustrates how to set the style when drawing lines using the FSSolidLine
 * class. This example also illustrates the rounded line end and join styles displayed 
 * when a line is rendered by the Flash Player and how the styles can be changed by
 * drawing thin rectangles to represent line segments.
 *
 * To run this example, type the following on a command line:
 *
 * examples --example LineStyles [--resultDir path]
 *
 * where
 *
 *     resultDir is the directory where the Flash file generated by the example 
 *     is written to.
 */
class LineStyles
{
public:
    LineStyles(map<string, string>& options)
    {
        FSMovie movie;
        FSShape shape;

        FSVector<FSLineStyle*> lineStyles;
        FSVector<FSFillStyle*> fillStyles;
        
        /*
        * Obtain a unique identifier for the shape definition.
        */
        int identifier = movie.newIdentifier();

        /*
        * Define the size (600 by 600 twips) and coordinate range for the bounding box
        * enclosing the shape.
        */
        FSBounds bounds(-300, -300, 300, 300);

        /*
        * Define the line styles used to draw the background square. For lines a line
        * width of 1 pixel is set (20 twips = 1 pixel). To draw the line segments a width of 
        * 1 twip is specified.
        */
        lineStyles.push_back(new FSSolidLine(20, FSColorTable::black()));
        lineStyles.push_back(new FSSolidLine(1, FSColorTable::black()));

        /*
        * Define the the solid black fill style for the rectangle segments so they match
        * the line color.
        */
        fillStyles.push_back(new FSSolidFill(FSColorTable::black()));

        /*
        * The first object in any shape is an instance of the FSShapeStyle class
        * which selects the line and fill styles. The initial drawing point is
        * located at (0,0) so the FSShapeStyle object also specifies a relative
        * move to change the location of the drawing point.
        *
        * Indices into the array of line and fill styles start at 1. An index of 0
        * indicates that no current style is selected.
        */
        shape.add(new FSShapeStyle(1, 0, 0, -300, -300));

        /*
        * Draw a single line then show how the line end style can be changed by
        * drawing an equivalent sized rectangle.
        */
        shape.add(new FSLine(540, 0));

        /*
        * Select the 1 twip wide line style and the solid colour to fill the rectangle.
        */
        shape.add(new FSShapeStyle(2, 1, 0, -300, -260));

        shape.add(new FSLine(540, 0));
        shape.add(new FSLine(0, 20));
        shape.add(new FSLine(-540, 0));
        shape.add(new FSLine(0, -20));
        
        /*
        * Draw a dashed line. Setting the line style to zero allows a line to be
        * drawn that is not rendered. This is simpler to use that specifying a
        * move using the FSShapeStyle class as the coordinates are absolute rather
        * than relative to the end of the last line drawn.
        */
        shape.add(new FSShapeStyle(-300, -100));

        for (int i=0; i<5; i++)
        {
            shape.add(new FSShapeStyle(1, 0, 0));
            shape.add(new FSLine(60, 0));

            /*
            * Set the line style to zero - no line will be drawn allowing a
            * relative more to be specified.
            */
            shape.add(new FSShapeStyle(0, 0, 0));
            shape.add(new FSLine(60, 0));
        }

        /*
        * Draw a dashed line by drawing small rectangles simulating each
        * line segment.
        */
        shape.add(new FSShapeStyle(-300, -60));
        
        for (int i=0; i<5; i++)
        {
            shape.add(new FSShapeStyle(2, 1, 0));
            shape.add(new FSLine(60, 0));
            shape.add(new FSLine(0, 20));
            shape.add(new FSLine(-60, 0));
            shape.add(new FSLine(0, -20));
            
            /*
            * Set the line style to zero. Since no line will be drawn a rectangle
            * need not be created.
            */
            shape.add(new FSShapeStyle(0, 0, 0));
            shape.add(new FSLine(120, 0));
        }

        /*
        * The Flash Player displayed line joins with rounded corners. Displaying
        * line segments using rectangles allows the corners of line segments to
        * be mitred.
        */
        shape.add(new FSShapeStyle(1, 0, 0, -300, 240));

        shape.add(new FSLine(0, -140));
        shape.add(new FSLine(540, 0));

        shape.add(new FSShapeStyle(2, 1, 0, -260, 240));

        shape.add(new FSLine(0, -100));
        shape.add(new FSLine(20, 0));
        shape.add(new FSLine(0, 100));
        shape.add(new FSLine(-20, 0));

        shape.add(new FSShapeStyle(-240, 140));
        shape.add(new FSLine(480, 0));
        shape.add(new FSLine(0, 20));
        shape.add(new FSLine(-480, 0));
        shape.add(new FSLine(0, -20));

        /*
        * Bevelled line joins can be simulated by drawing a slightly more
        * complex shape.
        */
        shape.add(new FSShapeStyle(2, 1, 0, -200, 240));

        shape.add(new FSLine(0, -30));
        shape.add(new FSLine(10, -10));
        shape.add(new FSLine(10, 0));
        shape.add(new FSLine(0, 40));
        shape.add(new FSLine(-20, 0));

        shape.add(new FSShapeStyle(-180, 200));
        shape.add(new FSLine(420, 0));
        shape.add(new FSLine(0, 20));
        shape.add(new FSLine(-420, 0));
        shape.add(new FSLine(0, -20));

        /*
        * Define the shape containing the lines. 
        */
        FSDefineShape* defineShape = new FSDefineShape(identifier, bounds, fillStyles, lineStyles, shape);

        /*
        * Add all the remaining objects required to create the movie. The coordinate range
        * is set so the center of the screen in at coordinates (0,0).
        */
        movie.setFrameSize(FSBounds(-400, -400, 400, 400));

        // Set the number of frames per second that the movie is played at.
        
        movie.setFrameRate(1.0f);

        /*
        * Set the background colour for the movie. This colour is displayed in
        * every frame. Once set it cannot be changed.
        */
        movie.add(new FSSetBackgroundColor(FSColorTable::lightblue()));

        /*
        * Add the definition of the shape to the movie. An object must be defined
        * before it can be placed on the display list.
        */
        movie.add(defineShape);

        // Place the shape on the display list located in the centre of the screen.
        
        movie.add(new FSPlaceObject(identifier, 1, 0, 0));

        // Show the contents of the display list.
        
        movie.add(new FSShowFrame());

        saveMovie(movie, stringOption(options, "resultDir"), "LineStyles.swf");
    }
};

