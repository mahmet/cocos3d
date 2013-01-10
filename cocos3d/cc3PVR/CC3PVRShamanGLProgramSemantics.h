/*
 * CC3PVRShamanGLProgramSemantics.h
 *
 * cocos3d 2.0.0
 * Author: Bill Hollings
 * Copyright (c) 2010-2013 The Brenwill Workshop Ltd. All rights reserved.
 * http://www.brenwill.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * http://en.wikipedia.org/wiki/MIT_License
 */

/** @file */	// Doxygen marker


#import "CC3PFXResource.h"


#pragma mark -
#pragma mark CC3PVRShamanGLProgramSemantics

/**
 * CC3PVRShamanGLProgramSemantics provides a mapping from the PVRShaman names declared in a PFX
 * effect within a PFX effects file, and the standard semantics from the CC3Semantic enumeration.
 */
@interface CC3PVRShamanGLProgramSemantics : CC3PFXGLProgramSemantics

/**
 * Returns the semantic value corresponding the the specified PFX semantic name, or returns
 * kCC3SemanticNone if the semantic could not be determined from the PFX semantic name.
 *
 * This implementation simply delegates to the class-side semanticForPVRShamanSemanticName: method.
 */
-(GLenum) semanticForPFXSemanticName: (NSString*) semanticName;

/**
 * Returns the semantic value corresponding the the specified PVRShaman semantic name, or returns
 * kCC3SemanticNone if the semantic could not be determined from the PVRShaman semantic name.
 */
+(GLenum) semanticForPVRShamanSemanticName: (NSString*) semanticName;

/**
 * By default, this class populates the standard mappings between PVRShaman semantic names and semantic
 * values. You can use this method to add an additional mapping, or to change an existing mapping.
 */
+(void) addSemantic: (GLenum) semantic forPVRShamanSemanticName: (NSString*) semanticName;

@end
