/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Dsp.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   :  public AudioAppComponent, public ComboBoxListener,
                                public SliderListener
{
public:
    //==============================================================================
    MainContentComponent()
    {
        addAndMakeVisible (hpFilter = new ComboBox ("hpFilter"));
        hpFilter->setEditableText (false);
        hpFilter->setJustificationType (Justification::centredLeft);
        hpFilter->setTextWhenNothingSelected (TRANS("Butterworth"));
        hpFilter->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
        hpFilter->addItem (TRANS("Butterworth"), 1);
        hpFilter->addItem (TRANS("Linkwitz & Riley"), 2);
        hpFilter->addItem (TRANS("Bessel"), 3);
        hpFilter->addItem (TRANS("Elliptic"), 4);
        hpFilter->addItem (TRANS("RBJ"), 5);
        hpFilter->addItem (TRANS("Legendre"), 6);
        hpFilter->addSeparator();
        hpFilter->addListener (this);
        
        addAndMakeVisible (lpFilter = new ComboBox ("lpFilter"));
        lpFilter->setEditableText (false);
        lpFilter->setJustificationType (Justification::centredLeft);
        lpFilter->setTextWhenNothingSelected (TRANS("Butterworth"));
        lpFilter->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
        lpFilter->addItem (TRANS("Butterworth"), 1);
        lpFilter->addItem (TRANS("Linkwitz & Riley"), 2);
        lpFilter->addItem (TRANS("Bessel"), 3);
        lpFilter->addItem (TRANS("Elliptic"), 4);
        lpFilter->addItem (TRANS("RBJ"), 5);
        lpFilter->addItem (TRANS("Legendre"), 6);
        lpFilter->addSeparator();
        lpFilter->addListener (this);
        
        addAndMakeVisible (hpOrder = new Slider ("hpOrder"));
        hpOrder->setRange (1, 8, 0);
        hpOrder->setSliderStyle (Slider::LinearHorizontal);
        hpOrder->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
        hpOrder->addListener (this);
        
        addAndMakeVisible (lpOrder = new Slider ("lpOrder"));
        lpOrder->setRange (1, 8, 0);
        lpOrder->setSliderStyle (Slider::LinearHorizontal);
        lpOrder->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
        lpOrder->addListener (this);
        
        addAndMakeVisible (hpFreq = new Slider ("hpFreq"));
        hpFreq->setRange (20, 20000, 0);
        hpFreq->setSliderStyle (Slider::LinearHorizontal);
        hpFreq->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
        hpFreq->addListener (this);
        
        addAndMakeVisible (lpFreq = new Slider ("lpFreq"));
        lpFreq->setRange (20, 20000, 0);
        lpFreq->setSliderStyle (Slider::LinearHorizontal);
        lpFreq->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
        lpFreq->addListener (this);

        setSize (800, 600);

        // specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    ~MainContentComponent()
    {
        hpFilter = nullptr;
        lpFilter = nullptr;
        hpOrder = nullptr;
        lpOrder = nullptr;
        hpFreq = nullptr;
        lpFreq = nullptr;
        
        shutdownAudio();
    }

    //=======================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {

        LP1 = new Dsp::SmoothedFilterDesign
        <Dsp::Butterworth::Design::LowPass<8>, 2, Dsp::DirectFormII<float>> (1024);
    
        HP1 = new Dsp::SmoothedFilterDesign
        <Dsp::Butterworth::Design::HighPass<8>, 2, Dsp::DirectFormII<float>> (1024);
        
        lp1Params[0] = sampleRate; // sample rate
        lp1Params[1] = 8; // order
        lp1Params[2] = 20000; // center frequency
        LP1->setParams (lp1Params);
        
        hp1Params[0] = sampleRate; // sample rate
        hp1Params[1] = 8; // order
        hp1Params[2] = 20; // center frequency
        HP1->setParams (hp1Params);
        //f->process (numSamples, audioData);
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        float numSamples = bufferToFill.numSamples;
        
        LP1->process(numSamples, bufferToFill.buffer->getArrayOfWritePointers());
        HP1->process(numSamples, bufferToFill.buffer->getArrayOfWritePointers());
    }

    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()
    }

    //=======================================================================
    void paint (Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (Colours::black);


        // You can add your drawing code here!
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        hpFilter->setBounds (136, 216, 150, 24);
        lpFilter->setBounds (440, 216, 150, 24);
        hpOrder->setBounds (144, 112, 150, 24);
        lpOrder->setBounds (440, 112, 150, 24);
        hpFreq->setBounds (144, 160, 150, 24);
        lpFreq->setBounds (440, 160, 150, 24);
    }
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged)
    {

        
        if (comboBoxThatHasChanged == hpFilter)
        {
 
        }
        else if (comboBoxThatHasChanged == lpFilter)
        {
            if (lpFilter->getSelectedId() == 1) {
                LP1 = new Dsp::SmoothedFilterDesign
                <Dsp::Butterworth::Design::LowPass<8>, 2, Dsp::DirectFormII<float>> (1024);
            } else if (lpFilter->getSelectedId() == 2) {
                LP1 = new Dsp::SmoothedFilterDesign
                <Dsp::Butterworth::Design::LowPass<8>, 2, Dsp::DirectFormII<float>> (1024);
            } else if (lpFilter->getSelectedId() == 3) {
                LP1 = new Dsp::SmoothedFilterDesign
                <Dsp::Bessel::Design::LowPass<8>, 2, Dsp::DirectFormII<float>> (1024);
            } else if (lpFilter->getSelectedId() == 4) {
                LP1 = new Dsp::SmoothedFilterDesign
                <Dsp::Elliptic::Design::LowPass<8>, 2, Dsp::DirectFormII<float>> (1024);
            } else if (lpFilter->getSelectedId() == 5) {
                LP1 = new Dsp::SmoothedFilterDesign
                <Dsp::RBJ::Design::LowPass, 2, Dsp::DirectFormII<float>> (1024);
            } else if (lpFilter->getSelectedId() == 6) {
                LP1 = new Dsp::SmoothedFilterDesign
                <Dsp::Legendre::Design::LowPass<8>, 2, Dsp::DirectFormII<float>> (1024);
            }

        }
        
        //[UsercomboBoxChanged_Post]
        //[/UsercomboBoxChanged_Post]
    }
    
    void sliderValueChanged (Slider* sliderThatWasMoved)
    {
        //[UsersliderValueChanged_Pre]
        //[/UsersliderValueChanged_Pre]
        
        if (sliderThatWasMoved == hpOrder)
        {
            //[UserSliderCode_hpOrder] -- add your slider handling code here..
            //[/UserSliderCode_hpOrder]
        }
        else if (sliderThatWasMoved == lpOrder)
        {
            //[UserSliderCode_lpOrder] -- add your slider handling code here..
            //[/UserSliderCode_lpOrder]
        }
        else if (sliderThatWasMoved == hpFreq)
        {
            //[UserSliderCode_hpFreq] -- add your slider handling code here..
            //[/UserSliderCode_hpFreq]
        }
        else if (sliderThatWasMoved == lpFreq)
        {
            //[UserSliderCode_lpFreq] -- add your slider handling code here..
            //[/UserSliderCode_lpFreq]
        }
        
        //[UsersliderValueChanged_Post]
        //[/UsersliderValueChanged_Post]
    }
    



private:
    //==============================================================================

    // Your private member variables go here...
    Dsp::Filter* LP1;
    Dsp::Filter* HP1;
    
    Dsp::Params lp1Params;
    Dsp::Params hp1Params;
    
    ScopedPointer<ComboBox> hpFilter;
    ScopedPointer<ComboBox> lpFilter;
    ScopedPointer<Slider> hpOrder;
    ScopedPointer<Slider> lpOrder;
    ScopedPointer<Slider> hpFreq;
    ScopedPointer<Slider> lpFreq;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
