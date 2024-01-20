/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "Graph.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Graph::Graph ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    xtopL = 5;
    ytopL = 5;
    xbotR = 595; //595;
    ybotR = 395;
    borderTop.setStart(xtopL, ytopL);
    borderTop.setEnd(xbotR, ytopL);
    borderBot.setStart(xtopL, ybotR);
    borderBot.setEnd(xbotR, ybotR);
    borderL.setStart(xtopL, ytopL);
    borderL.setEnd(xtopL, ybotR);
    borderR.setStart(xbotR, ytopL);
    borderR.setEnd(xbotR, ybotR);
    gainColorArray[0]   = juce::Colours::blue;
    gainColorArray[1]   = juce::Colours::yellow;
    gainColorArray[2]   = juce::Colours::grey;
    //[/Constructor]
}

Graph::~Graph()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Graph::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    {
        float x = 4.0f, y = 4.0f, width = 592.0f, height = 392.0f;
        juce::Colour fillColour = juce::Colour (0xff100e2e);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    float hmin = xtopL;
    float hmax = xbotR;
    float vmax = ybotR;
    float vmin = ytopL;
    
    g.setColour(juce::Colours::green);
    
    int ind;
    float vloc,hloc;
    for (ind=0; ind<9;ind++){
        vloc=(ind*vmax+(8-ind)*vmin)/8.0;
        gridSegment.setStart(hmin,vloc);
        gridSegment.setEnd(hmax,vloc);
        g.drawLine(gridSegment, 1.0f);
    }
    
    for (ind=0; ind<28; ind++){
        hloc=hmin+log10(kXvals[ind]/20.0)/log10(1000)*(hmax-hmin);
        gridSegment.setStart(hloc,vmin);
        gridSegment.setEnd(hloc,vmax);
        g.drawLine(gridSegment, 1.0f);
    }
    
    
    
    juce::Font  labelFont;
    labelFont.setSizeAndStyle(kLabelHeight, 0, 1.0, 0);
    g.setFont(labelFont);
    
    juce::String gridLabel;
    vloc=vmax*0.9;
    float xpos=10.0;
    gridLabel = juce::String("10");
    hloc=hmin+log10(xpos/10.0)/log10(3000)*(hmax-hmin);
    g.drawText(gridLabel, hloc, vloc, kLabelWidth, kLabelHeight, juce::Justification::topLeft, true);
    xpos=100.0;
    gridLabel = juce::String("100");
    hloc=hmin+log10(xpos/20.0)/log10(1000)*(hmax-hmin);
    g.drawText(gridLabel, hloc, vloc, kLabelWidth, kLabelHeight, juce::Justification::topLeft, true);
    xpos=1000.0;
    gridLabel = juce::String("1k");
    hloc=hmin+log10(xpos/10.0)/log10(3000)*(hmax-hmin);
    g.drawText(gridLabel, hloc, vloc, kLabelWidth, kLabelHeight, juce::Justification::topLeft, true);
    xpos=10000.0;
    gridLabel = juce::String("10k");
    hloc=hmin+log10(xpos/20.0)/log10(1000)*(hmax-hmin);
    g.drawText(gridLabel, hloc, vloc, kLabelWidth, kLabelHeight, juce::Justification::topLeft, true);
    
    hloc=hmax*0.944;
    ind=0;
    vloc=(ind*vmax+(8-ind)*vmin)/8.0;
    gridLabel = juce::String("24");
    g.drawText(gridLabel, hloc, vloc, kLabelWidth, kLabelHeight, juce::Justification::centredTop, true);
    ind=2;
    vloc=(ind*vmax+(8-ind)*vmin)/8.0;
    gridLabel = juce::String("12");
    g.drawText(gridLabel, hloc, vloc, kLabelWidth, kLabelHeight, juce::Justification::centredTop, true);
    ind=4;
    vloc=(ind*vmax+(8-ind)*vmin)/8.0;
    gridLabel = juce::String("0");
    g.drawText(gridLabel, hloc, vloc, kLabelWidth, kLabelHeight, juce::Justification::centredTop, true);
    ind=6;
    vloc=(ind*vmax+(8-ind)*vmin)/8.0;
    gridLabel = juce::String("-12");
    g.drawText(gridLabel, hloc, vloc, kLabelWidth, kLabelHeight, juce::Justification::centredTop, true);
    
    ind=1;
    vloc=(ind*vmax+(8-ind)*vmin)/8.0;
    gridLabel = juce::String("18");
    g.drawText(gridLabel, hloc, vloc, kLabelWidth, kLabelHeight, juce::Justification::centredTop, true);
    ind=3;
    vloc=(ind*vmax+(8-ind)*vmin)/8.0;
    gridLabel = juce::String("6");
    g.drawText(gridLabel, hloc, vloc, kLabelWidth, kLabelHeight, juce::Justification::centredTop, true);
    ind=5;
    vloc=(ind*vmax+(8-ind)*vmin)/8.0;
    gridLabel = juce::String("-6");
    g.drawText(gridLabel, hloc, vloc, kLabelWidth, kLabelHeight, juce::Justification::centredTop, true);
    ind=7;
    vloc=(ind*vmax+(8-ind)*vmin)/8.0;
    gridLabel = juce::String("-18");
    g.drawText(gridLabel, hloc, vloc, kLabelWidth, kLabelHeight, juce::Justification::centredTop, true);
    
    
    plotFreqTrace(g, 0, gainColorArray[0]);


    //[/UserPaint]
}

void Graph::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void Graph::init(MUS424Lab1WahAudioProcessor *p)
{
    pProcessor = p;
    //setupGrid(0);
}


void  Graph::plotTrace(juce::Graphics& g, double* x, double* y, int npt, float xmin, float xmax, float ymin, float ymax)
{
    float hmin = xtopL;
    float hmax = xbotR;
    float vmax = ybotR;
    float vmin = ytopL;
    
    for(int ind = 1; ind < npt; ind++)
    {
        juce::Point<float>  pt1(juce::jmap<float>(x[ind-1], xmin, xmax, hmin, hmax), juce::jmap<float>(y[ind-1], ymax, ymin, vmin, vmax));
        juce::Point<float>  pt2(juce::jmap<float>(x[ind], xmin, xmax, hmin, hmax), juce::jmap<float>(y[ind], ymax, ymin, vmin, vmax));
        
        float x1 = fmin(pt1.getX(), pt2.getX());
        float x2 = fmax(pt1.getX(), pt2.getX());
        float y1 = fmin(pt1.getY(), pt2.getY());
        float y2 = fmax(pt1.getY(), pt2.getY());
        
        juce::Line<float>   seg(pt1, pt2);
        
        if(x1 >= hmin && x2 <= hmax && y1 >= vmin && y2 <= vmax)
        {
            // The two endpoints lie inside window
            g.drawLine(seg);
        }
        else
        {
            // If the segment crosses any of the boundaries draw the portion inside the display window
            juce::Point<float>  pt;
            bool drawLine = false;
            if(seg.intersects(borderL, pt))
            {
                if(pt2.getX() > pt1.getX())
                    seg.setStart(pt);
                else
                    seg.setEnd(pt);
                drawLine = true;
            }
            if(seg.intersects(borderR,  pt))
            {
                if(pt2.getX() > pt1.getX())
                    seg.setEnd(pt);
                else
                    seg.setStart(pt);
                drawLine = true;
            }
            if(seg.intersects(borderBot, pt))
            {
                if(pt2.getY() > pt1.getY())
                    seg.setEnd(pt);
                else
                    seg.setStart(pt);
                drawLine = true;
            }
            if(seg.intersects(borderTop,  pt))
            {
                if(pt2.getY() > pt1.getY())
                    seg.setStart(pt);
                else
                    seg.setEnd(pt);
                drawLine = true;
            }
            if(drawLine)
                g.drawLine(seg);
        }
    }
}

void  Graph::plotFreqTrace(juce::Graphics& g, int index, juce::Colour color)
{
    
    float xmin = log10(20.0);
    float xmax = log10(20000.0);
    
    float ymin = -24.0;
    float ymax = 24.0;
    
    double* freqInpTrace;
    double* magRespTrace;
    
    int freqTraceLen=kNumFreqPoints;
    
    freqInpTrace = pProcessor->getFreqzData();
    magRespTrace = pProcessor->getMagzData();
    
    g.setColour(gainColorArray[1]);
    plotTrace(g, freqInpTrace, magRespTrace, freqTraceLen, xmin, xmax, ymin, ymax);
    
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Graph" componentName="" parentClasses="public juce::Component"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

