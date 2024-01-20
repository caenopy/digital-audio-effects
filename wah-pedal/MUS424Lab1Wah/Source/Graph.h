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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"


#define kLabelWidth      45.0
#define kLabelHeight     15.0
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Graph  : public juce::Component
{
public:
    //==============================================================================
    Graph ();
    ~Graph() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void init(MUS424Lab1WahAudioProcessor *);
    void  plotFreqTrace(juce::Graphics& g, int index, juce::Colour color);
    void  plotTrace(juce::Graphics& g, double* x, double* y, int npt, float xmin, float xmax, float ymin, float ymax);
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MUS424Lab1WahAudioProcessor *pProcessor;
    float xtopL, ytopL, xbotR, ybotR;
    juce::Line<float>   borderTop;
    juce::Line<float>   borderBot;
    juce::Line<float>   borderL;
    juce::Line<float>   borderR;
    juce::Line<float>   gridSegment;
    juce::Colour        gainColorArray[3];
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Graph)
};

//[EndFile] You can add extra defines here...
const float kXvals[28]={20.0,30.0,40.0,50.0,60.0,70.0,80.0,90.0,100.0,200.0,300.0,400.0,500.0,600.0,700.0,800.0,
    900.0,1000.0,2000.0,3000.0,4000.0,5000.0,6000.0,7000.0,8000.0,9000.0,10000.0,20000.0};
//[/EndFile]

