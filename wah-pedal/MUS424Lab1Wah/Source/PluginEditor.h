/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Controls.h"
#include "Graph.h"

//==============================================================================
/**
*/
class MUS424Lab1WahAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MUS424Lab1WahAudioProcessorEditor (MUS424Lab1WahAudioProcessor&);
    ~MUS424Lab1WahAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void UpdateDisplay();
    void resized() override;

    class WahFilterTimer : public juce::Timer
    {
    public:
        WahFilterTimer (MUS424Lab1WahAudioProcessorEditor &);
        virtual void    timerCallback();
        
    private:
        MUS424Lab1WahAudioProcessorEditor&  editor;
    };
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MUS424Lab1WahAudioProcessor& audioProcessor;

    WahFilterTimer  *updateTimer;
    
    Graph     *graphWin;
    Controls      *controlsWin;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MUS424Lab1WahAudioProcessorEditor)
};
