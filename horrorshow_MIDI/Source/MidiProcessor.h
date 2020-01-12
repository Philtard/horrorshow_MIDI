/*
  ==============================================================================

    MidiProcessor.h
    Created: 27 Dec 2019 2:35:46pm
    Author:  phili

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MidiProcessor
{
public:
  explicit MidiProcessor(AudioProcessorValueTreeState& vts);
  ~MidiProcessor();

  void Process(MidiBuffer& midi_messages);

private:
  int getNegHarmNN(int nn, int tonic);

  MidiBuffer p_midi_buffer_;

  AudioProcessorValueTreeState& apvts_;

  std::atomic<float>* is_on_;
  std::atomic<float>* cur_tonic_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiProcessor)
};
