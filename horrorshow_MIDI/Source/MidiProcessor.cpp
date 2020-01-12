/*
  ==============================================================================

    MidiProcessor.cpp
    Created: 2 Jan 2020 3:33:19pm
    Author:  phili

  ==============================================================================
*/

#include "MidiProcessor.h"

#include "PluginProcessor.h"

MidiProcessor::MidiProcessor(AudioProcessorValueTreeState& vts) : apvts_(vts)
{
  is_on_ = apvts_.getRawParameterValue(kIdMaxMidiNoteNumber);
  cur_tonic_ = apvts_.getRawParameterValue(kIdMinMidiNoteNumber);
}

MidiProcessor::~MidiProcessor()
= default;

void MidiProcessor::Process(MidiBuffer& midi_messages)
{
  p_midi_buffer_.clear();

  MidiBuffer::Iterator it(midi_messages);
  MidiMessage cur_msg;
  int sample_pos;

  while (it.getNextEvent(cur_msg, sample_pos))
  {
    if (cur_msg.isNoteOnOrOff())
    {
      if(*is_on_)
      {
        auto orig_nn = cur_msg.getNoteNumber();
        auto new_nn = getNegHarmNN(orig_nn, *cur_tonic_);
        DBG("Transformed [" << orig_nn << "] " << MidiMessage::getMidiNoteName(orig_nn, true, true, 3) <<
                              " to [" << new_nn << "] " << MidiMessage::getMidiNoteName(new_nn, true, true, 3));
        cur_msg.setNoteNumber(new_nn);
      }
    }
    p_midi_buffer_.addEvent(cur_msg, sample_pos);
  }
  midi_messages.swapWith(p_midi_buffer_);
}

int MidiProcessor::getNegHarmNN(int nn, int tonic)
{
  return 2*tonic + 7 - nn;
}
