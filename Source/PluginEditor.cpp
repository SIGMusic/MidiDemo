/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiDemoAudioProcessorEditor::MidiDemoAudioProcessorEditor (MidiDemoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    pitchShiftControlLabel.setText("Pitch Shift", juce::NotificationType::dontSendNotification);
    pitchShiftControlLabel.attachToComponent(&pitchShiftControl, true);
    pitchShiftControl.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    pitchShiftControl.setTextBoxStyle(juce::Slider::TextBoxRight, true, 25, 10);
    pitchShiftControl.setRange(-24.0, 24.0, 1.0);
    pressureControlLabel.setText("Pressure Control", juce::NotificationType::dontSendNotification);
    pressureControlLabel.attachToComponent(&pressureControl, true);
    pressureControl.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    pressureControl.setTextBoxStyle(juce::Slider::TextBoxRight, true, 25, 10);
    pressureControl.setRange(0.0, 127.0, 1.0);
    sustainControl.setTitle("Sustain");
    sustainControl.setName("Sustain");
    sustainControl.setDescription("Sustain");
    addAndMakeVisible(&pitchShiftControlLabel);
    addAndMakeVisible(&pressureControlLabel);
    addAndMakeVisible(&pitchShiftControl);
    addAndMakeVisible(&pressureControl);
    addAndMakeVisible(&sustainControl);

    pitchShiftControl.addListener(this);
    pressureControl.addListener(this);
    sustainControl.addListener(this);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
}

MidiDemoAudioProcessorEditor::~MidiDemoAudioProcessorEditor()
{
}

//==============================================================================
void MidiDemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MidiDemoAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto rectangle = getLocalBounds();
    sustainControl.setBounds(rectangle.removeFromRight(200).removeFromTop(200));
    pitchShiftControl.setBounds(rectangle.removeFromTop(100).withTrimmedLeft(100));
    pressureControl.setBounds(rectangle.removeFromTop(100).withTrimmedLeft(100));
}

void MidiDemoAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
  auto* logger = juce::Logger::getCurrentLogger();
  if (slider == &pitchShiftControl)
  {
    audioProcessor.pitch_offset = (int) pitchShiftControl.getValue();
    logger->outputDebugString("Changed pitch offset");
  }
  else if (slider == &pressureControl)
  {
    audioProcessor.pressure = (juce::uint8) pressureControl.getValue();
    logger->outputDebugString("Changed pressure");
  }
}

void MidiDemoAudioProcessorEditor::buttonClicked(juce::Button* button)
{
  auto* logger = juce::Logger::getCurrentLogger();
  if (button == &sustainControl)
  {
    juce::ToggleButton* tb = (juce::ToggleButton*) button;
    audioProcessor.sustain = tb->getToggleState();
    audioProcessor.sent_sustain = false;
    logger->outputDebugString("Toggle sustain");
  }
}
