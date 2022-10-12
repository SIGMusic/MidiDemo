/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <memory>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MidiDemoAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                      public juce::Slider::Listener,
                                      public juce::ToggleButton::Listener
{
public:
    MidiDemoAudioProcessorEditor (MidiDemoAudioProcessor&);
    ~MidiDemoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    virtual void sliderValueChanged(juce::Slider* slider) override;
    virtual void buttonClicked(juce::Button* button) override;

private:
    juce::Label pitchShiftControlLabel;
    juce::Slider pitchShiftControl;
    juce::Label pressureControlLabel;
    juce::Slider pressureControl;
    juce::ToggleButton sustainControl;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidiDemoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiDemoAudioProcessorEditor)
};
