/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Distortion.h"
#include "Clippings/HardClipping.h"
#include "Clippings/ArcTanSoftClipping.h"
#include "Clippings/HomographicSoftClipping.h"
#include "Clippings/HyperbolicTangentSoftClipping.h"
#include "Clippings/SinusoidalSoftClipping.h"
#include "Clippings/ExponentialSoftClipping.h"
#include "Clippings/TwoStageQuadraticSoftClipping.h"
#include "Clippings/CubicSoftClipping.h"
#include "Clippings/ReciprocalSoftClipping.h"

//==============================================================================
/**
*/
class BevyDistortionAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    BevyDistortionAudioProcessor();
    ~BevyDistortionAudioProcessor() override;

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

    //==============================================================================
    Clipping& chosenDistortion();

private:
	juce::AudioProcessorValueTreeState parameters;
    std::atomic<float>* driveParameter;
	std::atomic<float>* levelParameter;
    std::atomic<float>* factorParameter;
    std::atomic<float>* typeParameter;

    // Distortion 
    Distortion distortion;

    HardClipping hardClipping;
    ArcTanSoftClipping arcTanSoftClipping;
    HomographicSoftClipping homographicSoftClipping;
    HyperbolicTangentSoftClipping hyperbolicTangentSoftClipping;
    SinusoidalSoftClipping sinusoidalSoftClipping;
    ExponentialSoftClipping exponentialSoftClipping;
    TwoStageQuadraticSoftClipping twoStageQuadraticSoftClipping;
    CubicSoftClipping cubicSoftClipping;
    ReciprocalSoftClipping reciprocalSoftClipping;



    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BevyDistortionAudioProcessor)
};
