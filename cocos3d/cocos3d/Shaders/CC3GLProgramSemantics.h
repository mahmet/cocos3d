/*
 * CC3GLProgramSemantics.h
 *
 * cocos3d 2.0.0
 * Author: Bill Hollings
 * Copyright (c) 2011-2013 The Brenwill Workshop Ltd. All rights reserved.
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


@class CC3GLSLVariable, CC3GLSLUniform, CC3NodeDrawingVisitor;


/** Maximum number of texture units permitted. */
#define kCC3MaxTextureUnits		8

#pragma mark Semantic enumerations

/**
 * Indicates the semantic usage for scene content.
 *
 * Under OpenGL ES 2, these values are used to match an GLSL program variable to its semantic
 * usage within a GLSL shader.
 *
 * The semantic value kCC3SemanticAppBase and kCC3SemanticMax define a range of values that
 * can be used by the application to define and match custom app-specific semantics. The
 * framework will not automatically assign or use values within this range, so it can be
 * used by the app to indicate an app-specific semantic usage.
 */
typedef enum {
	kCC3SemanticNone = 0,						/**< No defined semantic usage. */

	// VERTEX CONTENT --------------
	kCC3SemanticVertexLocations,				/**< Vertex locations. */
	kCC3SemanticVertexNormals,					/**< Vertex normals. */
	kCC3SemanticVertexColors,					/**< Vertex colors. */
	kCC3SemanticVertexPointSizes,				/**< Vertex point sizes. */
	kCC3SemanticVertexWeights,					/**< Vertex skinning weights. */
	kCC3SemanticVertexMatrices,					/**< Vertex skinning matrices. */
	kCC3SemanticVertexTexture,					/**< Vertex texture coordinates for one texture unit. */
	
	kCC3SemanticHasVertexNormal,				/**< Whether the vertex normal is available. */
	kCC3SemanticShouldNormalizeVertexNormal,	/**< Whether vertex normals should be normalized. */
	kCC3SemanticShouldRescaleVertexNormal,		/**< Whether vertex normals should be rescaled. */
	kCC3SemanticHasVertexColor,					/**< Whether the vertex color is available. */
	kCC3SemanticHasVertexTextureCoordinate,		/**< Whether the vertex texture coordinate is available. */
	kCC3SemanticHasVertexPointSize,				/**< Whether the vertex point size is available. */
	kCC3SemanticIsDrawingPoints,				/**< Whether the vertices are being drawn as points. */
	
	// ENVIRONMENT MATRICES --------------
	kCC3SemanticModelMatrix,					/**< Current model-to-world matrix. */
	kCC3SemanticModelMatrixInv,					/**< Inverse of current model-to-world matrix. */
	kCC3SemanticModelMatrixInvTran,				/**< Inverse-transpose of current model-to-world matrix. */
	kCC3SemanticViewMatrix,						/**< Camera view matrix. */
	kCC3SemanticViewMatrixInv,					/**< Inverse of camera view matrix. */
	kCC3SemanticViewMatrixInvTran,				/**< Inverse-transpose of camera view matrix. */
	kCC3SemanticModelViewMatrix,				/**< Current modelview matrix. */
	kCC3SemanticModelViewMatrixInv,				/**< Inverse of current modelview matrix. */
	kCC3SemanticModelViewMatrixInvTran,			/**< Inverse-transpose of current modelview matrix. */
	kCC3SemanticProjMatrix,						/**< Camera projection matrix. */
	kCC3SemanticProjMatrixInv,					/**< Inverse of camera projection matrix. */
	kCC3SemanticProjMatrixInvTran,				/**< Inverse-transpose of camera projection matrix. */
	kCC3SemanticModelViewProjMatrix,			/**< Current modelview-projection matrix. */
	kCC3SemanticModelViewProjMatrixInv,			/**< Inverse of current modelview-projection matrix. */
	kCC3SemanticModelViewProjMatrixInvTran,		/**< Inverse-transpose of current modelview-projection matrix. */
	
	// CAMERA -----------------
	kCC3SemanticCameraPosition,					/**< Global position of the camera. */
	
	// MATERIALS --------------
	kCC3SemanticColor,							/**< Color when lighting & materials are not in use. */
	kCC3SemanticMaterialColorAmbient,			/**< Ambient color of the material. */
	kCC3SemanticMaterialColorDiffuse,			/**< Diffuse color of the material. */
	kCC3SemanticMaterialColorSpecular,			/**< Specular color of the material. */
	kCC3SemanticMaterialColorEmission,			/**< Emission color of the material. */
	kCC3SemanticMaterialOpacity,				/**< Opacity of the material. */
	kCC3SemanticMaterialShininess,				/**< Shininess of the material. */
	kCC3SemanticMinimumDrawnAlpha,				/**< Minimum alpha value to be drawn, otherwise will be discarded. */

	// LIGHTING
	kCC3SemanticIsUsingLighting,				/**< Whether any lighting is enabled. */
	kCC3SemanticSceneLightColorAmbient,			/**< Ambient light color of the scene. */

	kCC3SemanticLightIsEnabled,					/**< Whether a light is enabled. */
	kCC3SemanticLightPosition,					/**< Position of a light. */
	kCC3SemanticLightColorAmbient,				/**< Ambient color of a light. */
	kCC3SemanticLightColorDiffuse,				/**< Diffuse color of a light. */
	kCC3SemanticLightColorSpecular,				/**< Specular color of the light. */
	kCC3SemanticLightAttenuation,				/**< Distance attenuation coefficients for a light. */
	kCC3SemanticLightSpotDirection,				/**< Direction of a spotlight. */
	kCC3SemanticLightSpotExponent,				/**< Fade-off exponent of a spotlight. */
	kCC3SemanticLightSpotCutoffAngle,			/**< Cutoff angle of a spotlight. */
	kCC3SemanticLightSpotCutoffAngleCosine,		/**< Cosine of cutoff angle of a spotlight. */

	// TEXTURES
	kCC3SemanticTextureCount,					/**< Number of active textures. */
	kCC3SemanticTextureSamplers,				/**< Array of texture samplers of length kCC3SemanticTextureCount. */
	
	// The semantics below mimic OpenGL ES 1.1 configuration functionality for combining texture units.
	// In most shaders, these will be left unused in favor of customized the texture combining in code.
	kCC3SemanticTexUnitMode,					/**< Environment mode of a texture unit. */
	kCC3SemanticTexUnitConstantColor,			/**< The constant color of a texture unit. */
	kCC3SemanticTexUnitCombineRGBFunction,		/**< RBG combiner function of a texture unit. */
	kCC3SemanticTexUnitSource0RGB,				/**< The RGB of source 0 of a texture unit. */
	kCC3SemanticTexUnitSource1RGB,				/**< The RGB source 1 of a texture unit. */
	kCC3SemanticTexUnitSource2RGB,				/**< The RGB source 2 of a texture unit. */
	kCC3SemanticTexUnitOperand0RGB,				/**< The RGB combining operand of source 0 of a texture unit. */
	kCC3SemanticTexUnitOperand1RGB,				/**< The RGB combining operand of source 1 of a texture unit. */
	kCC3SemanticTexUnitOperand2RGB,				/**< The RGB combining operand of source 2 of a texture unit. */
	kCC3SemanticTexUnitCombineAlphaFunction,	/**< Alpha combiner function of a texture unit. */
	kCC3SemanticTexUnitSource0Alpha,			/**< The alpha of source 0 of a texture unit. */
	kCC3SemanticTexUnitSource1Alpha,			/**< The alpha of source 1 of a texture unit. */
	kCC3SemanticTexUnitSource2Alpha,			/**< The alpha of source 2 of a texture unit. */
	kCC3SemanticTexUnitOperand0Alpha,			/**< The alpha combining operand of source 0 of a texture unit. */
	kCC3SemanticTexUnitOperand1Alpha,			/**< The alpha combining operand of source 1 of a texture unit. */
	kCC3SemanticTexUnitOperand2Alpha,			/**< The alpha combining operand of source 2 of a texture unit. */

	// PARTICLES ------------
	kCC3SemanticPointSize,						/**< Default size of points, if not specified per-vertex in a vertex attribute array. */
	kCC3SemanticPointSizeAttenuation,			/**< Point size distance attenuation coefficients. */
	kCC3SemanticPointSizeMinimum,				/**< Minimum size points will be allowed to shrink to. */
	kCC3SemanticPointSizeMaximum,				/**< Maximum size points will be allowed to grow to. */
	kCC3SemanticPointSizeFadeThreshold,			/**< Points will be allowed to grow to. */
	kCC3SemanticPointSpritesIsEnabled,			/**< Whether points should be interpeted as textured sprites. */
	
	kCC3SemanticAppBase,						/**< First semantic of app-specific custom semantics. */
	kCC3SemanticMax = 0xFFFF					/**< The maximum value for an app-specific custom semantic. */
} CC3Semantic;

/** Returns a string representation of the specified state semantic. */
NSString* NSStringFromCC3Semantic(CC3Semantic semantic);


#pragma mark -
#pragma mark CC3GLProgramSemanticsDelegate protocol

/**
 * Defines the behaviour required for an object that manages the semantics for a CC3GLProgram.
 *
 * Each CC3GLProgram delegates to an object that implements this protocol when it needs to
 * populate the current value of a uniform variable from content within the 3D scene.
 */
@protocol CC3GLProgramSemanticsDelegate <NSObject>

/**
 * Configures the specified GLSL variable.
 *
 * Implementers should attempt to match the specified uniform variable with a semantic and,
 * if found, should set the semantic property on the specified variable, and return YES.
 * If an impementation cannot determine the appropriate semantic, it should avoid setting
 * the semantic property of the uniform and should return NO.
 *
 * In addition, implementers may perform additional configuration behaviour for the specified
 * variable.
 *
 * Returns whether the variable was successfully configured. When delegating to superclasses
 * or other delegates, implementers can use this return code to determine whether or not to
 * continue attempting to configure the specified variable.
 *
 * This method is invoked automatically after the GLSL program has been compiled and linked.
 */
-(BOOL) configureVariable: (CC3GLSLVariable*) variable;

/**
 * Populates the specified uniform, if possible, and returns whether the uniform was populated.
 *
 * The semantic, semanticIndex and size properties of the specified uniform can be used to
 * determine what content is expected by the GLSL program for that uniform. The implementor
 * then retrieves the required content from the GL state caches found via the CC3OpenGLESEngine
 * state machine structures, or from the scene content accessed via the specified visitor.
 *
 * The specified visitor can be used to access content within the scene, and contains several
 * convenience properties for accessing typical content, including currentMeshNode,
 * currentMaterial, textureUnitCount, camera, and scene properties, and a lightAt: method.
 *
 * Implementers of this method can use the various set... methods on the specified uniform
 * to set the content into the specified uniform variable. The implementor does not need to
 * manage the current value of the uniform, as it is managed automatically, and the GL engine
 * is only updated if the value has changed.
 *
 * Implementers should return YES if a value was set into the specified uniform variable,
 * and NO if otherwise. When delegating to superclasses or other delegates, implementers
 * can use this return value to determine whether or not to continue attempting to determine
 * and set the value of the uniform variable.
 *
 * This method is invoked automatically on every rendering loop. Keep it tight.
 */
-(BOOL) populateUniform: (CC3GLSLUniform*) uniform withVisitor: (CC3NodeDrawingVisitor*) visitor;

/** Returns a string description of the specified semantic. */
-(NSString*) nameOfSemantic: (GLenum) semantic;

@end


#pragma mark -
#pragma mark CC3GLSLVariableConfiguration

/**
 * A CC3GLSLVariableConfiguration carries information for configuring a single CC3GLSLVariable.
 *
 * An implementation of the CC3GLProgramSemanticsDelegate protocol will typically contain a
 * collection of instances of this class, or a subclass, to configure the variables associated
 * with a CC3GLProgram.
 *
 * This base implementation maps a variable name to a semantic value. Subclasses may add
 * additional variable configuration information.
 */
@interface CC3GLSLVariableConfiguration : NSObject {
	NSString* _name;
	GLenum _semantic : 16;
	GLuint _semanticIndex : 8;
}

/**
 * The name of the variable.
 *
 * Typically this is the name of the variable as declared in the GLSL program source code.
 */
@property(nonatomic, retain) NSString* name;

/**
 * A symbolic constant indicating the semantic meaning of this variable. See the description
 * of the same property on the CC3GLSLVariable class for a full description.
 *
 * The initial value of this property is kCC3SemanticNone.
 */
@property(nonatomic, assign) GLenum semantic;

/**
 * When the semantic refers to an element of a structure that may have multiple instances,
 * this property indicates to which instance this variable refers. See the description of
 * the same property on the CC3GLSLVariable class for a full description.
 *
 * The initial value of this property is zero.
 */
@property(nonatomic, assign) GLuint semanticIndex;

@end


#pragma mark -
#pragma mark CC3GLProgramSemanticsBase

/**
 * CC3GLProgramSemanticsBase is an abstract implementation of the CC3GLProgramSemanticsDelegate
 * protocol, that retrieves common uniform values from the scene based on those semantics.
 *
 * This implementation can be used as a superclass for other implementations. Semantic assigment
 * heuristics may be radically different across implementations, but there is much commonality in
 * the retrieval and assignment of uniform variables using the populateUniform:withVisitor: method.
 * In many cases, subclassing this implementation, and using the inherited populateUniform:withVisitor:
 * method, possibly overriding to provide additional variable assignment behaviour, can provide
 * significant useful functionality.
 *
 * This implementation does not provide any behaviour for the configureVariable: method, which
 * simply returns NO.
 *
 * The nameOfSemantic: method returns a name for each standard semantics defined in the CC3Semantic
 * enumeration. If a subclass adds additional semantic definitions of its own, it should override
 * that method to provide a string representation of the semantic value.
 */
@interface CC3GLProgramSemanticsBase : NSObject<CC3GLProgramSemanticsDelegate> {}

/** Allocates and initializes an autoreleased instance. */
+(id) semanticsDelegate;

/**
 * Populates the specified uniform from standard content extracted from the scene.
 *
 * This implementation provides significant standard behaviour for most standard semantics.
 * Subclasses can use this as a starting point, and add content extraction for customized
 * semantics, or can override the behaviour of this method for specific uniforms or semantics.
 */
-(BOOL) populateUniform: (CC3GLSLUniform*) uniform withVisitor: (CC3NodeDrawingVisitor*) visitor;

/**
 * This implementation does not provide any configuration behaviour, and simply returns NO.
 *
 * Subclasses will add behaviour to configure variables according to customized semantic mapping.
 */
-(BOOL) configureVariable: (CC3GLSLVariable*) variable;

/**
 * Returns a string description of the specified semantic.
 *
 * This implementation calls the NSStringFromCC3Semantic method to return a name for each of
 * the standard semantics defined in the CC3Semantic enumeration. If a subclass adds additional
 * semantic definitions of its own, it should override this method to provide a string
 * representation of any new semantic values.
 */
-(NSString*) nameOfSemantic: (GLenum) semantic;

@end


#pragma mark -
#pragma mark CC3GLProgramSemanticsByVarName

/**
 * CC3GLProgramSemanticsByVarName extends CC3GLProgramSemanticsBase to add the assignment of
 * semantics to uniform and attribute variables based on matching specific variable names
 * within the GLSL source code.
 *
 * Since the semantics are determined by GLSL variable name, it is critical that the GLSL
 * shader code use very specific attribute and uniform variable names.
 */
@interface CC3GLProgramSemanticsByVarName : CC3GLProgramSemanticsBase {
	NSMutableDictionary* _varConfigsByName;
}

/**
 * This implementation uses the name property of the specified variable to look up a
 * configuration, and sets the semantic property of the specified variable to that of
 * the retrieved configuration.
 *
 * Returns YES if a configuration was found and the semantic was assigned, or NO if
 * a configuration could not be found for the variable.
 */
-(BOOL) configureVariable: (CC3GLSLVariable*) variable;

/**
 * Adds the specified variable configuration to the configuration lookup.
 *
 * Configurations added via this method are used to configure the variables submitted
 * to the configureVariable: method.
 *
 * Configurations are added to the lookup by name. If a configuration with the same name
 * already exists in the lookup, it is replaced with the specified configuration.
 */
-(void) addVariableConfiguration: (CC3GLSLVariableConfiguration*) varConfig;

/**
 * Adds a variable configruation that maps the specified variable name to the specified semantic
 * and semantic index.
 *
 * This implementation creates an instance of CC3GLSLVariableConfiguration configured with the
 * specified name, semantic and semantic index, and invokes the addVariableConfiguration: method.
 *
 * The value of the semantic parameter is typically one of values in the CC3Semantic enumeration,
 * but an application can define and use additional semantics beyond the values defined by
 * CC3Semantic. Additional semantics defined by the application should fall with the range
 * defined by the kCC3SemanticAppBase and kCC3SemanticMax constants, inclusively.
 */
-(void) mapVarName: (NSString*) name toSemantic: (GLenum) semantic at: (GLuint) semanticIndex;

/**
 * Adds a variable configruation that maps the specified variable name to the specified semantic
 * at semantic index zero.
 *
 * This is a convenience method that invokes the mapVarName:toSemantic:at: method, passing a value
 * of zero for the semanticIndex argument. See the description of that method for more info.
 */
-(void) mapVarName: (NSString*) name toSemantic: (GLenum) semantic;

@end


#pragma mark -
#pragma mark CC3GLProgramSemanticsByVarName default mappings extension

/**
 * This extension to CC3GLProgramSemanticsByVarName establishes a cocos3d default
 * mappings between variable names and semantics.
 *
 * An application can use the mappings defined in this extension as the basis for its own mappings
 * and add or change a few of its own additional mappings, or an application may ignore this
 * extension and may instead provide its own extensions to populate completely different mappings.
 */
@interface CC3GLProgramSemanticsByVarName (DefaultMappings)

/**
 * Populates this instance with the default cocos3d mappings between variable names and semantics.
 *
 * An application wishing to add additional semantic mappings, or override any of the default
 * mappings can invoke this method, and then invoke the mapVarName:toSemantic: or
 * addVariableConfiguration: methods to add or change any of the mappings.
 *
 * An application wishing to define a completely different semantic mapping may instantiate
 * an instance of this class, will avoid invoking this method, and will typically add its
 * own population methods in a class extension category.
 *
 * Memory consumption is minorly affected (~10-20 KB) by the number of mappings defined for
 * the lights and texture units. You may use the maxDefaultMappingLightVariables and
 * maxDefaultMappingTextureUnitVariables class-side properties to balance the number of available
 * mappings to conserve memory or increase shader flexibility. You must set those properties prior
 * to the first access of the sharedDefaultDelegate property (typically on the loading of the
 * default shaders).
 */
-(void) populateWithDefaultVariableNameMappings;

/**
 * Determines the number of mappings available for the lights. This determines the maximum
 * number of lights that can be automatically mapped in the shaders.
 *
 * The initial value of this property is 4. You can adjust this property prior to the first access
 * of the sharedDefaultDelegate property (typically on the loading of the default shaders).
 */
+(NSUInteger) maxDefaultMappingLightVariables;

/**
 * Determines the number of mappings available for the lights. This determines the maximum
 * number of lights that can be automatically mapped in the shaders.
 *
 * The initial value of this property is 4. You can adjust this property prior to the first access
 * of the sharedDefaultDelegate property (typically on the loading of the default shaders).
 */
+(void) setMaxDefaultMappingLightVariables: (NSUInteger) maxLights;

/**
 * Determines the number of mappings available for the texture units. This determines the maximum
 * number of configurable texture units that can be automatically mapped in the shaders.
 *
 * The initial value of this property is 4. You can adjust this property prior to the first access
 * of the sharedDefaultDelegate property (typically on the loading of the default shaders).
 *
 * If none of your shaders make use of configurable texture unit variables, set this property
 * to zero to save some memory.
 */
+(NSUInteger) maxDefaultMappingTextureUnitVariables;

/**
 * Determines the number of mappings available for the texture units. This determines the maximum
 * number of configurable texture units that can be automatically mapped in the shaders.
 *
 * The initial value of this property is 4. You can adjust this property prior to the first access
 * of the sharedDefaultDelegate property (typically on the loading of the default shaders).
 *
 * If none of your shaders make use of configurable texture unit variables, set this property
 * to zero to save some memory.
 */
+(void) setMaxDefaultMappingTextureUnitVariables: (NSUInteger) maxTexUnits;


#pragma mark Allocation and initialization

/**
 * Returns a shared default semantic delegate, that can be used to map the standard variable names
 * to their default semantics.
 *
 * The delegate returned by this property is lazily created and automatically populated using
 * the populateWithDefaultVariableNameMappings method to create the standard default mappings.
 *
 * The default CC3ConfigurableWithDefaultVarNames.vsh and CC3ConfigurableWithDefaultVarNames.fsh shaders
 * are designed to use the standard default mappings provided by the delegate returned by this property.
 *
 * This property returns a shared instance. Making changes to the delegate returned by this
 * property will affect all CC3GLPrograms that have been assigned this delegate. Handle with care.
 *
 * Memory consumption is minorly affected (~10-20 KB) by the number of mappings defined for
 * the lights and texture units. You may use the maxDefaultMappingLightVariables and
 * maxDefaultMappingTextureUnitVariables class-side properties to balance the number of available
 * mappings to conserve memory or increase shader flexibility. You must set those property prior
 * to the first access of this property (typically on the loading of the default shaders).
 */
+(CC3GLProgramSemanticsByVarName*) sharedDefaultDelegate;

@end

