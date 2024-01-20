/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MUS424Lab1WahAudioProcessorEditor::MUS424Lab1WahAudioProcessorEditor (MUS424Lab1WahAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    updateTimer = new WahFilterTimer(*this);
    
    controlsWin = new Controls();
    controlsWin->init(&p);
    addAndMakeVisible (controlsWin);
    controlsWin->setBounds (0, 0, controlsWin->getWidth(), controlsWin->getHeight());
    
    graphWin = new Graph();
    graphWin->init(&p);
    addAndMakeVisible (graphWin);
    graphWin->setBounds (0, controlsWin->getHeight(), graphWin->getWidth(), graphWin->getHeight());
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(controlsWin->getWidth(), controlsWin->getHeight()+graphWin->getHeight());
    // Start timer
    updateTimer->startTimer(20);
    
}

MUS424Lab1WahAudioProcessorEditor::~MUS424Lab1WahAudioProcessorEditor()
{
    delete updateTimer;
    delete controlsWin;
    delete graphWin;
}

//==============================================================================
void MUS424Lab1WahAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    controlsWin->paint(g);
    graphWin->paint(g);

//    g.setColour (juce::Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void MUS424Lab1WahAudioProcessorEditor::UpdateDisplay()
{
    controlsWin->displayFreq(audioProcessor.freqParam->get());
}

void MUS424Lab1WahAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

//==============================================================================
MUS424Lab1WahAudioProcessorEditor::WahFilterTimer::WahFilterTimer(MUS424Lab1WahAudioProcessorEditor &p)
: editor(p)
{
}

void    MUS424Lab1WahAudioProcessorEditor::WahFilterTimer::timerCallback()
{
    editor.UpdateDisplay();
    editor.repaint();
}
