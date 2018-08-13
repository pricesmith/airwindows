/*
*	File:		VariMu.cpp
*	
*	Version:	1.0
* 
*	Created:	10/2/10
*	
*	Copyright:  Copyright � 2010 Airwindows, All Rights Reserved
* 
*	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc. ("Apple") in 
*				consideration of your agreement to the following terms, and your use, installation, modification 
*				or redistribution of this Apple software constitutes acceptance of these terms.  If you do 
*				not agree with these terms, please do not use, install, modify or redistribute this Apple 
*				software.
*
*				In consideration of your agreement to abide by the following terms, and subject to these terms, 
*				Apple grants you a personal, non-exclusive license, under Apple's copyrights in this 
*				original Apple software (the "Apple Software"), to use, reproduce, modify and redistribute the 
*				Apple Software, with or without modifications, in source and/or binary forms; provided that if you 
*				redistribute the Apple Software in its entirety and without modifications, you must retain this 
*				notice and the following text and disclaimers in all such redistributions of the Apple Software. 
*				Neither the name, trademarks, service marks or logos of Apple Computer, Inc. may be used to 
*				endorse or promote products derived from the Apple Software without specific prior written 
*				permission from Apple.  Except as expressly stated in this notice, no other rights or 
*				licenses, express or implied, are granted by Apple herein, including but not limited to any 
*				patent rights that may be infringed by your derivative works or by other works in which the 
*				Apple Software may be incorporated.
*
*				The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO WARRANTIES, EXPRESS OR 
*				IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY 
*				AND FITNESS FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE 
*				OR IN COMBINATION WITH YOUR PRODUCTS.
*
*				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR CONSEQUENTIAL 
*				DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
*				OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, 
*				REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER 
*				UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN 
*				IF APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
/*=============================================================================
	VariMu.h
	
=============================================================================*/
#include "VariMu.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

COMPONENT_ENTRY(VariMu)


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	VariMu::VariMu
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
VariMu::VariMu(AudioUnit component)
	: AUEffectBase(component)
{
	CreateElements();
	Globals()->UseIndexedParameters(kNumberOfParameters);
	SetParameter(kParam_One, kDefaultValue_ParamOne );
	SetParameter(kParam_Two, kDefaultValue_ParamTwo );
	SetParameter(kParam_Three, kDefaultValue_ParamThree );
	SetParameter(kParam_Four, kDefaultValue_ParamFour );
        
#if AU_DEBUG_DISPATCHER
	mDebugDispatcher = new AUDebugDispatcher (this);
#endif
	
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	VariMu::GetParameterValueStrings
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult		VariMu::GetParameterValueStrings(AudioUnitScope		inScope,
                                                                AudioUnitParameterID	inParameterID,
                                                                CFArrayRef *		outStrings)
{
        
    return kAudioUnitErr_InvalidProperty;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	VariMu::GetParameterInfo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult		VariMu::GetParameterInfo(AudioUnitScope		inScope,
                                                        AudioUnitParameterID	inParameterID,
                                                        AudioUnitParameterInfo	&outParameterInfo )
{
	ComponentResult result = noErr;

	outParameterInfo.flags = 	kAudioUnitParameterFlag_IsWritable
						|		kAudioUnitParameterFlag_IsReadable;
    
    if (inScope == kAudioUnitScope_Global) {
        switch(inParameterID)
        {
			case kParam_One:
                AUBase::FillInParameterName (outParameterInfo, kParameterOneName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamOne;
                break;
            case kParam_Two:
                AUBase::FillInParameterName (outParameterInfo, kParameterTwoName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamTwo;
                break;
           case kParam_Three:
                AUBase::FillInParameterName (outParameterInfo, kParameterThreeName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamThree;
                break;
            case kParam_Four:
                AUBase::FillInParameterName (outParameterInfo, kParameterFourName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamFour;
                break;
			default:
                result = kAudioUnitErr_InvalidParameter;
                break;
            }
	} else {
        result = kAudioUnitErr_InvalidParameter;
    }
    


	return result;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	VariMu::GetPropertyInfo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult		VariMu::GetPropertyInfo (AudioUnitPropertyID	inID,
                                                        AudioUnitScope		inScope,
                                                        AudioUnitElement	inElement,
                                                        UInt32 &		outDataSize,
                                                        Boolean &		outWritable)
{
	return AUEffectBase::GetPropertyInfo (inID, inScope, inElement, outDataSize, outWritable);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	VariMu::GetProperty
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult		VariMu::GetProperty(	AudioUnitPropertyID inID,
                                                        AudioUnitScope 		inScope,
                                                        AudioUnitElement 	inElement,
                                                        void *			outData )
{
	return AUEffectBase::GetProperty (inID, inScope, inElement, outData);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	VariMu::Initialize
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult VariMu::Initialize()
{
    ComponentResult result = AUEffectBase::Initialize();
    if (result == noErr)
        Reset(kAudioUnitScope_Global, 0);
    return result;
}

#pragma mark ____VariMuEffectKernel


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	VariMu::VariMuKernel::Reset()
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void		VariMu::VariMuKernel::Reset()
{
	muSpeedA = 10000;
	muSpeedB = 10000;
	muCoefficientA = 1;
	muCoefficientB = 1;
	muVary = 1;
	flip = false;
	previous = 0.0;
	fpNShape = 0.0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	VariMu::VariMuKernel::Process
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void		VariMu::VariMuKernel::Process(	const Float32 	*inSourceP,
                                                    Float32		 	*inDestP,
                                                    UInt32 			inFramesToProcess,
                                                    UInt32			inNumChannels,
                                                    bool			&ioSilence )
{
	UInt32 nSampleFrames = inFramesToProcess;
	const Float32 *sourceP = inSourceP;
	Float32 *destP = inDestP;
	Float64 overallscale = 2.0;
	overallscale /= 44100.0;
	overallscale *= GetSampleRate();
	Float64 threshold = 1.001 - (1.0-pow(1.0-GetParameter( kParam_One ),3));
	Float64 muMakeupGain = sqrt(1.0 / threshold);
	muMakeupGain = (muMakeupGain + sqrt(muMakeupGain))/2.0;
	muMakeupGain = sqrt(muMakeupGain);
	Float64 outGain = sqrt(muMakeupGain);
	//gain settings around threshold
	Float64 release = pow((1.15-GetParameter( kParam_Two )),5)*32768.0;
	release /= overallscale;
	Float64 fastest = sqrt(release);
	//speed settings around release
	Float64 coefficient;
	Float64 output = outGain * GetParameter( kParam_Three );
	Float64 wet = GetParameter( kParam_Four );
	long double squaredSample;

	// � � � � � � � � � � � � is the kitten song o/~
	
	while (nSampleFrames-- > 0) {
		long double inputSample = *sourceP;
		static int noisesource = 0;
		int residue;
		double applyresidue;
		noisesource = noisesource % 1700021; noisesource++;
		residue = noisesource * noisesource;
		residue = residue % 170003; residue *= residue;
		residue = residue % 17011; residue *= residue;
		residue = residue % 1709; residue *= residue;
		residue = residue % 173; residue *= residue;
		residue = residue % 17;
		applyresidue = residue;
		applyresidue *= 0.00000001;
		applyresidue *= 0.00000001;
		inputSample += applyresidue;
		if (inputSample<1.2e-38 && -inputSample<1.2e-38) {
			inputSample -= applyresidue;
		}
		//for live air, we always apply the dither noise. Then, if our result is 
		//effectively digital black, we'll subtract it again. We want a 'air' hiss
		long double drySample = inputSample;
		
		if (fabs(inputSample) > fabs(previous)) squaredSample = previous * previous;
		else squaredSample = inputSample * inputSample;
		previous = inputSample;
		inputSample *= muMakeupGain;
		
		if (flip)
			{
				if (fabs(squaredSample) > threshold)
					{
						muVary = threshold / fabs(squaredSample);
						muAttack = sqrt(fabs(muSpeedA));
						muCoefficientA = muCoefficientA * (muAttack-1.0);
						if (muVary < threshold)
							{
								muCoefficientA = muCoefficientA + threshold;
							}
						else
							{
								muCoefficientA = muCoefficientA + muVary;
							}
						muCoefficientA = muCoefficientA / muAttack;
					}
				else
					{
						muCoefficientA = muCoefficientA * ((muSpeedA * muSpeedA)-1.0);
						muCoefficientA = muCoefficientA + 1.0;
						muCoefficientA = muCoefficientA / (muSpeedA * muSpeedA);
					}
				muNewSpeed = muSpeedA * (muSpeedA-1);
				muNewSpeed = muNewSpeed + fabs(squaredSample*release)+fastest;
				muSpeedA = muNewSpeed / muSpeedA;
			}
		else
			{
				if (fabs(squaredSample) > threshold)
					{
						muVary = threshold / fabs(squaredSample);
						muAttack = sqrt(fabs(muSpeedB));
						muCoefficientB = muCoefficientB * (muAttack-1);
						if (muVary < threshold)
							{
								muCoefficientB = muCoefficientB + threshold;
							}
						else
							{
								muCoefficientB = muCoefficientB + muVary;
							}
						muCoefficientB = muCoefficientB / muAttack;
					}
				else
					{
						muCoefficientB = muCoefficientB * ((muSpeedB * muSpeedB)-1.0);
						muCoefficientB = muCoefficientB + 1.0;
						muCoefficientB = muCoefficientB / (muSpeedB * muSpeedB);
					}
				muNewSpeed = muSpeedB * (muSpeedB-1);
				muNewSpeed = muNewSpeed + fabs(squaredSample*release)+fastest;
				muSpeedB = muNewSpeed / muSpeedB;
			}
		//got coefficients, adjusted speeds

		if (flip)
			{
			coefficient = (muCoefficientA + pow(muCoefficientA,2))/2.0;
			inputSample *= coefficient;
			}
		else
			{
			coefficient = (muCoefficientB + pow(muCoefficientB,2))/2.0;
			inputSample *= coefficient;
			}
		//applied compression with vari-vari-�-�-�-�-�-�-is-the-kitten-song o/~
		//applied gain correction to control output level- tends to constrain sound rather than inflate it
		flip = !flip;		

		if (output < 1.0) {
			inputSample *= output;
		}
		if (wet < 1.0) {
			inputSample = (drySample * (1.0-wet)) + (inputSample * wet);
		}
		//nice little output stage template: if we have another scale of floating point
		//number, we really don't want to meaninglessly multiply that by 1.0.
		
		//noise shaping to 32-bit floating point
		Float32 fpTemp = inputSample;
		fpNShape += (inputSample-fpTemp);
		inputSample += fpNShape;
		//for deeper space and warmth, we try a non-oscillating noise shaping
		//that is kind of ruthless: it will forever retain the rounding errors
		//except we'll dial it back a hair at the end of every buffer processed
		//end noise shaping on 32 bit output
		
		*destP = inputSample;
		
		sourceP += inNumChannels; destP += inNumChannels;
	}
}

