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

#include "Controls.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Controls::Controls ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    freq__slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (freq__slider.get());
    freq__slider->setRange (0, 1, 0);
    freq__slider->setSliderStyle (juce::Slider::LinearHorizontal);
    freq__slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    freq__slider->addListener (this);

    freq__slider->setBounds (8, 8, 336, 32);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 200);


    //[Constructor] You can add your own custom stuff here..
    freq__slider->setSkewFactorFromMidPoint (0.5);
    //[/Constructor]
}

Controls::~Controls()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    freq__slider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Controls::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    {
        float x = 4.0f, y = 4.0f, width = 340.0f, height = 44.0f;
        juce::Colour fillColour = juce::Colour (0xff24304a);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Controls::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Controls::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == freq__slider.get())
    {
        //[UserSliderCode_freq__slider] -- add your slider handling code here..
        float fval = freq__slider.get()->getValue();
        *pProcessor->freqParam = fval;
        pProcessor->DesignResonantLPF(fval);    // Lab1_Task: uncomment DesignWahFilter and call instead of
        //pProcessor->DesignWahFilter(fval);    // DesignResonantLPF once you have written DesignWahFilter.
        //[/UserSliderCode_freq__slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void Controls::init(MUS424Lab1WahAudioProcessor *p)
{
    pProcessor = p;
    //setupGrid(0);
}
void Controls::displayFreq(float val1)
{
    freq__slider.get()->setValue(val1);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Controls" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="200">
  <BACKGROUND backgroundColour="ff323e44">
    <ROUNDRECT pos="4 4 340 44" cornerSize="10.0" fill="solid: ff24304a" hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="f93484c83b3937dd" memberName="freq__slider"
          virtualName="" explicitFocusOrder="0" pos="8 8 336 32" min="0.0"
          max="1.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

