/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Initial_delayAudioProcessor::Initial_delayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), mState(*this, &mUndoManager, "Summative", {
                           
             std::make_unique<AudioParameterFloat>("cutoff", "Cutoff", 20.0f, 20000.0f, 600.0f),
             std::make_unique<AudioParameterFloat>("resonance", "Resonance", 1.0f, 5.0f, 1.0f),
             std::make_unique<AudioParameterFloat>("delaylength", "Delaylength", 0.1f, 2.0f, 0.5f),
             std::make_unique<AudioParameterFloat>("feedbackp", "Feedbackp", 0.1f, 1.0f, 0.4f),
             std::make_unique<AudioParameterFloat>("delaydrymix", "Delaydrymix", 0.0f, 1.0f, 0.5f),
             std::make_unique<AudioParameterFloat>("delaywetmix", "Delaywetmix", 0.0f, 1.0f, 0.5f),
         
             
     }), lowPassFilter(dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.1f))

/*delayBuffer(2,1)
{
    // set default values
    delayLength = 0.5;
    dryMix = 0.5;
    wetMix = 0.5;
    feedback = 0.75;
    delayBufferLength = 1;
    
    delayReadPosition = 0;
    delayWritePosition = 0;
    
}*/
                       
#endif

{
    delayLength = 0.5;
    dryMix = 0.5;
    wetMix = 0.5;
    feedback = 0.75;
    delayBufferLength = 1;
    
    delayReadPosition = 0;
    delayWritePosition = 0;
}

Initial_delayAudioProcessor::~Initial_delayAudioProcessor()
{
}

//==============================================================================
const String Initial_delayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int Initial_delayAudioProcessor::getNumParameters()
{
    return numParameters;
}

float Initial_delayAudioProcessor::getParameter (int index)
{
    switch (index) {
        case dryMixParam:
            return dryMix;
        case wetMixParam:
            return wetMix;
        case feedbackParam:
            return feedback;
        case delayLengthParam:
            return delayLength;
        default:
            return 0.0f;
    }
}

void Initial_delayAudioProcessor::setParameter (int index, float newValue)
{
    switch (index) {
        case dryMixParam:
            dryMix = newValue;
            break;
        case wetMixParam:
            wetMix = newValue;
            break;
        case feedbackParam:
            feedback = newValue;
            break;
        case delayLengthParam:
            delayLength = newValue;
            delayReadPosition = (int) (delayWritePosition - (delayLength * getSampleRate()) + delayBufferLength) % delayBufferLength;
            break;
        default:
            break;;
    }
}

const String Initial_delayAudioProcessor::getParameterName (int index)
{
    switch (index) {
        case dryMixParam:
            return "dry mix";
        case wetMixParam:
            return "wet mix";
        case feedbackParam:
            return "feedback";
        case delayLengthParam:
            return "delay";
        default:
            return String::empty;
    }
}

const String Initial_delayAudioProcessor::getParameterText (int index)
{
    return String();
}

const String Initial_delayAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String Initial_delayAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool Initial_delayAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool Initial_delayAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool Initial_delayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Initial_delayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Initial_delayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

bool Initial_delayAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double Initial_delayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Initial_delayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Initial_delayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Initial_delayAudioProcessor::setCurrentProgram (int index)
{
}

const String Initial_delayAudioProcessor::getProgramName (int index)
{
    return {};
}

void Initial_delayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Initial_delayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    currentSampleRate = sampleRate;
    
    //mSampleRate = sampleRate;
    
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    lowPassFilter.prepare(spec);
    lowPassFilter.reset();
    
    delayBufferLength  = (int) 2.0 * sampleRate;
    if (delayBufferLength < 1)
        delayBufferLength = 1;
    
    delayBuffer.setSize(2, delayBufferLength);
    delayBuffer.clear();
    
    delayReadPosition = (int) (delayWritePosition - (delayLength * getSampleRate()) + delayBufferLength) % delayBufferLength;
}

void Initial_delayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Initial_delayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void Initial_delayAudioProcessor::updateFilter()
{
    float freq = *mState.getRawParameterValue("cutoff");
    float res = *mState.getRawParameterValue("resonance");
    
    *lowPassFilter.state = *dsp::IIR::Coefficients<float>::makeLowPass(currentSampleRate, freq, res);
}

void Initial_delayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    
    const int numInputChannels = getNumInputChannels();
    const int numOutputChannels = getNumOutputChannels();
    const int numSamples = buffer.getNumSamples();
    
    int dpr, dpw;
    
    ScopedNoDenormals noDenormals;
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

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    /*dsp::AudioBlock<float> block (buffer);
    
    updateFilter();
    
    lowPassFilter.process(dsp::ProcessContextReplacing <float> (block));*/
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
        
        float* channelData = buffer.getWritePointer(channel);
        float* delayData = delayBuffer.getWritePointer(jmin(channel, delayBuffer.getNumChannels() - 1));
        
        dpr = delayReadPosition;
        dpw = delayWritePosition;
        
        for (int i = 0; i < numSamples; ++i) {
            const float in = channelData[i];
            float out = 0.0;
            
            out = (dryMix * in + wetMix * delayData[dpr]);
            
            delayData[dpw] = in + (delayData[dpr] * feedback);
            
            if (++dpr >= delayBufferLength)
                dpr = 0;
            if (++dpw >= delayBufferLength)
                dpw = 0;
            
            channelData[i] = out;
        }
    }

    delayReadPosition = dpr;
    delayWritePosition = dpw;
    
    dsp::AudioBlock<float> block (buffer);
    
    updateFilter();
    
    lowPassFilter.process(dsp::ProcessContextReplacing <float> (block));
    
    for (int i = numInputChannels; i < numOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

}
    
//==============================================================================
bool Initial_delayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Initial_delayAudioProcessor::createEditor()
{
    return new Initial_delayAudioProcessorEditor (*this);
}

//==============================================================================
void Initial_delayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    MemoryOutputStream stream(destData, false);
    mState.state.writeToStream(stream);
    
}

void Initial_delayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid()) {
        mState.state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Initial_delayAudioProcessor();
}
