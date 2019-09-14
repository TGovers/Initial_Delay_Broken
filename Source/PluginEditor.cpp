/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "JuceHeader.h"

//==============================================================================
Initial_delayAudioProcessorEditor::Initial_delayAudioProcessorEditor (Initial_delayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setOpaque(true);
    setSize (540, 450);
    
    delayLengthSlider.setSliderStyle(Slider::Rotary);
    delayLengthSlider.addListener(this);
    //delayLengthSlider.setRange(0.01, 2.0, 0.01);
    delayLengthSlider.setSize(150, 100);
    addAndMakeVisible(&delayLengthSlider);
    
    feedbackSlider.setSliderStyle(Slider::Rotary);
    feedbackSlider.addListener(this);
    //feedbackSlider.setRange(0.0, 0.995, 0.005);
    feedbackSlider.setSize(150, 100);
    addAndMakeVisible(&feedbackSlider);
    
    /*dryMixSlider.setSliderStyle(Slider::Rotary);
    dryMixSlider.addListener(this);
    //dryMixSlider.setRange(0.0, 1.0, 0.01);
    dryMixSlider.setSize(150, 100);
    addAndMakeVisible(&dryMixSlider);

    wetMixSlider.setSliderStyle(Slider::Rotary);
    wetMixSlider.addListener(this);
    //wetMixSlider.setRange(0.0, 1.0, 0.01);
    wetMixSlider.setSize(150, 100);
    addAndMakeVisible(&wetMixSlider);*/
    
    delayLengthSlider.setLookAndFeel(&otherLookAndFeel3);
    feedbackSlider.setLookAndFeel(&otherLookAndFeel3);
    dryMixSlider.setLookAndFeel(&otherLookAndFeel3);
    wetMixSlider.setLookAndFeel(&otherLookAndFeel3);
    
    //startTimer(50);
    
    filterCutoffDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxAbove, true, 55, 30);
    filterCutoffDial.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    filterCutoffDial.setColour(Slider::ColourIds::textBoxOutlineColourId, Colour());
    filterCutoffDial.setSliderStyle(Slider::SliderStyle::Rotary);
    filterCutoffDial.setNumDecimalPlacesToDisplay(0);
    filterCutoffDial.setSize(150, 100);
    //filterCutoffDial.setRange(20.0, 20000.0);
    filterCutoffDial.setTextValueSuffix("hz");
    //filterCutoffDial.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::yellowgreen);
    
    // dont change these two
    filterCutoffDial.addListener(this);
    addAndMakeVisible(filterCutoffDial);
    
    filterResDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxAbove, true, 50,30);
    filterResDial.setColour(Slider::ColourIds::textBoxOutlineColourId, Colour());
    filterResDial.setSliderStyle(Slider::SliderStyle::Rotary);
    filterResDial.setSize(150, 100);
    //filterResDial.setRange(1.0, 5.0);
    filterResDial.setTextValueSuffix("Q");
    //filterResDial.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::yellowgreen);
    filterResDial.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    
    // dont change these two
    filterResDial.addListener(this);
    addAndMakeVisible(filterResDial);
    
    // dont change these two
    filterCutoffValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "cutoff", filterCutoffDial);
    filterResValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "resonance", filterResDial);
    
    delayLengthValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "delaylength", delayLengthSlider);
    feedbackValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "feedbackp", feedbackSlider);
    //delayDryValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "delaydrymix", dryMixSlider);
    //delayWetValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "delaywetmix", wetMixSlider);
    
    filterCutoffDial.setSkewFactorFromMidPoint(1000.0f);
    
    filterCutoffDial.setLookAndFeel(&otherLookAndFeel2);
    filterResDial.setLookAndFeel(&otherLookAndFeel2);
    
    addAndMakeVisible(filterCutoffLabel);
    filterCutoffLabel.attachToComponent(&filterCutoffDial, false);
    //mixLabel.attachToComponent(&filterCutoffDial, false);
    
    addAndMakeVisible(filterResLabel);
    //filterResLabel.setText("Q", dontSendNotification);
    filterResLabel.attachToComponent(&filterResDial, false);
}

Initial_delayAudioProcessorEditor::~Initial_delayAudioProcessorEditor()
{
}

//==============================================================================
/*void Initial_delayAudioProcessorEditor::timerCallback()
{
   Initial_delayAudioProcessor* ourProcessor = getProcessor();
    
    delayLengthSlider.setValue(ourProcessor->delayLength, dontSendNotification);
    feedbackSlider.setValue(ourProcessor->feedback, dontSendNotification);
    dryMixSlider.setValue(ourProcessor->dryMix, dontSendNotification);
    wetMixSlider.setValue(ourProcessor->wetMix, dontSendNotification);
}

void Initial_delayAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &delayLengthSlider) {
        getProcessor()->setParameterNotifyingHost(Initial_delayAudioProcessor::delayLengthParam, (float) delayLengthSlider.getValue());
    } else if (slider == &feedbackSlider) {
        getProcessor()->setParameterNotifyingHost(Initial_delayAudioProcessor::feedbackParam, (float) feedbackSlider.getValue());
    } else if (slider == &dryMixSlider) {
        getProcessor()->setParameterNotifyingHost(Initial_delayAudioProcessor::dryMixParam, (float) dryMixSlider.getValue());
    } else if (slider == &wetMixSlider) {
        getProcessor()->setParameterNotifyingHost(Initial_delayAudioProcessor::wetMixParam, (float) wetMixSlider.getValue());
    } 
}*/

void Initial_delayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
    //Image background = ImageCache::getFromMemory(BinaryData::ayaya7_png, BinaryData::ayaya7_pngSize);
    //g.drawImageAt(background, 0, 0);
    
    g.fillAll (Colours::darkorchid);
    
    // g.setColour (Colours::aqua);
    //g.setFont (15.0f);
    // g.drawFittedText ("GOVERSA2 PLUGIN", getLocalBounds(), Justification::centred, 1);
    
    g.setColour(Colours::black);
    g.setFont(Font ("Arial", 20.0f, Font::italic));
    //g.drawFittedText("Random Test Font! Hi There!", 10, 10, getWidth(), 50,
    //                 Justification::left, 1);
}

void Initial_delayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    filterCutoffDial.setBounds(0, getHeight()-130, 80, 80);
    filterResDial.setBounds(100, getHeight()-130, 80, 80);
    
    delayLengthSlider.setBounds(0, getHeight()-280, 80, 80);
    feedbackSlider.setBounds(100, getHeight()-280, 80, 80);
    //dryMixSlider.setBounds(0, getHeight()-450, 80, 80);
    //wetMixSlider.setBounds(100, getHeight()-450, 80, 80);
}

void Initial_delayAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &mixSlider)
    {
        // dont change any of this void function
        // get the value on the current slider, pass to audio processor
        processor.mixLevel.setTargetValue(mixSlider.getValue());
        
    }
    
    /*if (slider == &filterCutoffDial)
     {
     
     // get the value on the current slider, pass to audio processor
     processor.freqLevel.setTargetValue(filterCutoffDial.getValue());
     
     }
     
     if (slider == &filterResDial)
     {
     
     // get the value on the current slider, pass to audio processor
     processor.resLevel.setTargetValue(filterResDial.getValue());
     
     }*/
    
}
