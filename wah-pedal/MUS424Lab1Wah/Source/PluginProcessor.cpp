/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MUS424Lab1WahAudioProcessor::MUS424Lab1WahAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(freqParam = new juce::AudioParameterFloat (juce::ParameterID{"frequency", 1}, "Frequency", 0.0f, 1.0f, 0.5f));
    
}

MUS424Lab1WahAudioProcessor::~MUS424Lab1WahAudioProcessor()
{
}

//==============================================================================
const juce::String MUS424Lab1WahAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MUS424Lab1WahAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MUS424Lab1WahAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MUS424Lab1WahAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MUS424Lab1WahAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MUS424Lab1WahAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MUS424Lab1WahAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MUS424Lab1WahAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MUS424Lab1WahAudioProcessor::getProgramName (int index)
{
    return {};
}

void MUS424Lab1WahAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MUS424Lab1WahAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    double fs = getSampleRate();
    wahFilter.SetSR(fs);
    wahFilter.Init();
    wahFilter.SetSmoothingFactor(5.0);
    
}

void MUS424Lab1WahAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MUS424Lab1WahAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MUS424Lab1WahAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto mainInputOutput = getBusBuffer (buffer, true, 0);
    auto numchans = mainInputOutput.getNumChannels();
    float inp0,inp1;
    for (auto j = 0; j < buffer.getNumSamples(); ++j)
    {
        inp0 = mainInputOutput.getReadPointer (0) [j];
        inp1=inp0;
        if(numchans>1)
            inp1= mainInputOutput.getReadPointer (1) [j];
        
        //       inp0=wahFilter.ProcessL(inp0);
        
        //       if(numchans>1){
        //           inp1=wahFilter.ProcessR(inp1);
        //       }
        
        *mainInputOutput.getWritePointer (0, j) = wahFilter.ProcessL(inp0);
        if(numchans>1)
            *mainInputOutput.getWritePointer (1, j) = wahFilter.ProcessR(inp1);
        wahFilter.SmoothCoefs();
    }
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool MUS424Lab1WahAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MUS424Lab1WahAudioProcessor::createEditor()
{
    return new MUS424Lab1WahAudioProcessorEditor (*this);
}

//==============================================================================
void MUS424Lab1WahAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::MemoryOutputStream stream (destData, true);
    stream.writeFloat(*freqParam);
}

void MUS424Lab1WahAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::MemoryInputStream stream (data, static_cast<size_t> (sizeInBytes), false);
    
    float fval, cval;
    int ival;
    bool bval;
    
    fval = stream.readFloat();
    cval = freqParam->convertTo0to1(fval);
    freqParam->setValueNotifyingHost(cval);
}

void MUS424Lab1WahAudioProcessor::DesignResonantLPF(double cutoff)
{
    cutoff=20.0*exp(log(20.0e3/20.0)*cutoff);
    double b0,b1,b2,a0,a1,a2;
    b2=0.0;
    b1=0.0;
    b0=1.0;
    a2=1.0/((2.0*kPi*cutoff)*(2.0*kPi*cutoff));
    a1=sqrt(2.0)/(2.0*kPi*cutoff);
    a0=1.0;
    
    wahFilter.b[0]=b2; wahFilter.b[1]=b1; wahFilter.b[2]=b0;
    wahFilter.a[0]=a2; wahFilter.a[1]=a1; wahFilter.a[2]=a0;
    double fs = getSampleRate();
    wahFilter.SetSR(fs);
    wahFilter.Bilinear(0.0);
    wahFilter.CalculateResponse();
    
}

void MUS424Lab1WahAudioProcessor::DesignWahFilter(double position)
{
    // Lab1_Task: design wah filter here, using measured responses for 11 pedal positions.
    // You must interpolate between the 11 measured filters, based on the continuous
    // input argument "position", which ranges in value from 0.0-1.0.
    // If position = 0.0, the designed filter should correspond to the measured response
    // wahFiltResponse0, and if position = 1.0, the designed filter should model the
    // measured reasponse wahFiltResponse10.
    // Don't forget to change the call to DesignResonantLPF in Controls.cpp to call this function
    // instead once you are finished.
    // NOTE: The coefficient format is as follows:
    // b[] = {b2, b1, b0};
    // a[] = {a2, a1, a0};

    // Default: Design bypass filter with h(n) = 1.0, 0.0, 0.0, ....
    double b0,b1,b2,a0,a1,a2;
//    b2=0.0;
//    b1=0.0;
//    b0=1.0;
//    a2=0.0;
//    a1=0.0;
//    a0=1.0;
    
    // Arrays for filter parameters for each pedal position (0 to 10)
    const int numPositions = 11;
    double gammas[numPositions] = { 0.15, 0.15, 0.15, 0.18, 0.19, 0.28, 0.42, 0.55, 0.63, 0.74, 0.87 };
    double f0s[numPositions] =    { 400,   400,  400,  405,  500,  650, 1010, 1200, 1450, 1750, 2000 };
    double Qs[numPositions] =     { 15.0, 15.0, 15.0, 11.0,  10.0,  7.0, 5.0,  4.0, 3.5,  3.0,  2.6 };
    
    // Interpolate the filter parameters based on position
    int index = static_cast<int>(position * (numPositions - 1));
    double frac = (position * (numPositions - 1)) - index;

    double gamma = gammas[index] * (1 - frac) + gammas[index + 1] * frac;
    double f0 = f0s[index] * (1 - frac) + f0s[index + 1] * frac;
    double Q = Qs[index] * (1 - frac) + Qs[index + 1] * frac;

    // Convert these parameters to filter coefficients
    double w0 = 2 * kPi * f0; //  units of f0? "/ getSampleRate();" ?
    
    //
    //               gamma*s/w0
    // H(s) = __________________________
    //         s^2/w0^2 + s/(w0*Q) + 1
    //

    b0 = 0;
    b1 = gamma/w0;
    b2 = 0;
    a0 = 1;
    a1 = 1/(w0*Q);
    a2 = 1/(w0*w0);

    wahFilter.b[0]=b2; wahFilter.b[1]=b1; wahFilter.b[2]=b0;
    wahFilter.a[0]=a2; wahFilter.a[1]=a1; wahFilter.a[2]=a0;
    double fs = getSampleRate();
    wahFilter.SetSR(fs);            // Get current sampling rate
    wahFilter.Bilinear(0.0);        // Compute discrete-time coefficients
    wahFilter.CalculateResponse();  // Calculate magnitude response to plot on GUI
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MUS424Lab1WahAudioProcessor();
}
