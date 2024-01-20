/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define kNumFreqPoints      1024
#define kPi                 3.141592653589793
#define kSmoothingTime      0.05

typedef struct {            //Biquad Struct
    double  b[3];           // Continuous-time numerator
    double  a[3];           // Continuous-time denominator
    double  targetCofs[5];      // Discrete-time target coefficients
    double  cofs[5];            // Discrete-time smoothed coefficients
    double  smoothingFactor;
    double  Omegaz[kNumFreqPoints];  // Points to evaluate frequency response
    double  Hz[kNumFreqPoints];      // Magnitude response
    double  samplingRate;
    double z1L,z2L;                  // filter states for left channel
    double z1R,z2R;                  // filter states for right channel
    void Init(){
        z1R=0.0;z2R=0.0;
        z1L=0.0;z2L=0.0;
        b[0]=1.0;b[1]=0.0;b[2]=0.0;
        a[0]=1.0;a[1]=0.0;a[2]=0.0;
        targetCofs[0]=1.0;targetCofs[1]=0.0;targetCofs[2]=0.0;targetCofs[3]=0.0;targetCofs[4]=0.0;
        SlamCoefs();
    }

    void Bilinear(double warpfreq)
    {
        // Lab1_Task: Place code here for bilinear transform, assuming
        // sampling rate = samplingRate
        // matching discrete-time frequency warpfreq to continuous-time frequency warpfreq
        // assign s -> 2/Td * (1-z^{-1`}) / (1+z^{-1})
        // choosing Td appropriately for the desired warping.
        // Assume continuous-time coefficients are present in b[] and a[], and
        // place discrete time coefficients {bz0, bz1, bz2, az1, az2} in targetCofs[],
        // with az0 normalized to 1.0.
        
        //Default coefficients set to bypass (impulse response h(n) = 1, 0, 0, 0,.....
        double bz0=1.0;
        double bz1=0.0;
        double bz2=0.0;
        double az1=0.0;
        double az2=0.0;

        targetCofs[0]=bz0; targetCofs[1]=bz1; targetCofs[2]=bz2; targetCofs[3]=az1; targetCofs[4]=az2;
    }
    void SetSR(double fs){
        samplingRate=fs;
    }
    void CalculateResponse(){
        int ind;
        double w,H,cosw,cos2w,sinw,sin2w;
        for (ind=0; ind<kNumFreqPoints; ind++){
            w=2.0*kPi*pow(10.0,log10(20.0)+(double (ind))*(log10(20000.0)-log10(20))/(kNumFreqPoints-1.0));
            Omegaz[ind]=log10(w/(2.0*kPi));
            w=w/samplingRate;
            cosw=cos(w); cos2w=cos(2.0*w);
            sinw=sin(w); sin2w=sin(2.0*w);
            H=(pow(targetCofs[0]+targetCofs[1]*cosw+targetCofs[2]*cos2w,2.0)+pow(targetCofs[1]*sinw+targetCofs[2]*sin2w,2.0))/(pow(1.0+targetCofs[3]*cosw+targetCofs[4]*cos2w,2.0)+pow(targetCofs[3]*sinw+targetCofs[4]*sin2w,2.0));
            H=sqrt(H);
            H=20.0*log10(fabs(H));
            Hz[ind]=H;
        }
    }
    double ProcessL(double input){
        double temp;
        temp=z1L+cofs[0]*input;
        z1L=z2L+cofs[1]*input-cofs[3]*temp;
        z2L=cofs[2]*input-cofs[4]*temp;
        return temp;
    }
    double ProcessR(double input){
        double temp;
        temp=z1R+cofs[0]*input;
        z1R=z2R+cofs[1]*input-cofs[3]*temp;
        z2R=cofs[2]*input-cofs[4]*temp;
        return temp;
    }
    void SlamCoefs(){
        cofs[0]=targetCofs[0];
        cofs[1]=targetCofs[1];
        cofs[2]=targetCofs[2];
        cofs[3]=targetCofs[3];
        cofs[4]=targetCofs[4];
    }
    void SmoothCoefs(){
        cofs[0] += (targetCofs[0]-cofs[0])*smoothingFactor;
        cofs[1] += (targetCofs[1]-cofs[1])*smoothingFactor;
        cofs[2] += (targetCofs[2]-cofs[2])*smoothingFactor;
        cofs[3] += (targetCofs[3]-cofs[3])*smoothingFactor;
        cofs[4] += (targetCofs[4]-cofs[4])*smoothingFactor;
    }

    void SetSmoothingFactor(double smoothingTime){
        // Lab1_Task: Calculate smoothingFactor based on samplingRate, smoothingTime
        // This constant determines how much the smoothed coefficients move towards the
        // target coefficiencts each time SmoothCoefs() is called.
        
        // Defaults to an arbitrary smoothing time:
        smoothingFactor=4.535137108518938e-06;
    }
} DirectBiquad;



//==============================================================================
/**
*/
class MUS424Lab1WahAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MUS424Lab1WahAudioProcessor();
    ~MUS424Lab1WahAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    
    double*  getMagzData()      { return &(wahFilter.Hz[0]); }
    double*  getFreqzData()      { return &(wahFilter.Omegaz[0]); }
    
    
    void DesignResonantLPF(double cutoff);
    void DesignWahFilter(double position);
    
    juce::AudioParameterFloat*  freqParam;
    
    DirectBiquad wahFilter;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MUS424Lab1WahAudioProcessor)
    
    const double kQ[11]={10.0, 10.0, 10.0, 10.0, 7.943, 5.623, 4.217, 3.802, 2.985, 2.630, 2.291};
    const double kWc[11]={2513.3, 2513.3, 2513.3, 2513.3, 3078.8, 4121.8, 6157.5, 7376.5, 8928.4, 10687.7, 12208.2};
    const double kGamma[11]={6.309, 6.309, 6.309, 6.309, 7.729, 10.348, 15.458, 18.518, 22.415,  26.831, 30.649};
    
};
