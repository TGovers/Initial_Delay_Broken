/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class Initial_delayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Initial_delayAudioProcessor();
    ~Initial_delayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;
    
    int getNumParameters() override;
    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;
    
    const String getParameterName (int index) override;
    const String getParameterText (int index) override;
    
    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioProcessorValueTreeState& getValueTreeState();
    
    void updateFilter();
    
    AudioProcessorValueTreeState mState;
    
    enum Parameters
    {
        delayLengthParam = 0,
        dryMixParam,
        wetMixParam,
        feedbackParam,
        numParameters
    };
    
    float delayLength;
    float dryMix;
    float wetMix;
    float feedback;
    
    SmoothedValue<float>mixLevel;

private:

    float currentSampleRate;
    
    AudioParameterFloat* cutoff;
    AudioParameterFloat* resonance;
    
    float* cutoffParameter = nullptr;
    float* resParameter = nullptr;
    
    AudioParameterFloat* delaylength;
    AudioParameterFloat* feedbackp;
    AudioParameterFloat* delaydrymix;
    AudioParameterFloat* delaywetmix;
    
    float* delaylengthParameter = nullptr;
    float* feedbackpParameter = nullptr;
    float* delaydrymixParameter = nullptr;
    float* delaywetmixParameter = nullptr;
    
    UndoManager mUndoManager;
    
    Random random;

    AudioSampleBuffer delayBuffer;
    int delayBufferLength;
    int delayReadPosition;
    int delayWritePosition;
    
    dsp::ProcessorDuplicator<dsp::IIR::Filter <float>, dsp::IIR::Coefficients<float>> lowPassFilter;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Initial_delayAudioProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
