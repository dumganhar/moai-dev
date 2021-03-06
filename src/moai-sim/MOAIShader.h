// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAISHADER_H
#define	MOAISHADER_H

#include <moai-sim/MOAIGfxResource.h>
#include <moai-sim/MOAINode.h>

class MOAIColor;
class MOAITransformBase;
	
#define		OPENGL_PREPROC		"#define LOWP\n #define MEDP\n"
#define		OPENGL_ES_PREPROC	"#define LOWP lowp\n #define MEDP mediump\n"

#define		WEBGL_PREPROC "precision mediump int;\n precision mediump float;\n"

//================================================================//
// MOAIShaderUniform
//================================================================//
class MOAIShaderUniform {
private:

	friend class MOAIShader;

	STLString mName;
	
	u32		mAddr;		// this is resolved when linking the shader
	u32		mType;
	bool	mIsDirty;

	ZLLeanArray < float > mBuffer;	
	
	union {
		float	mFloat;
		int		mInt;
	};

	//----------------------------------------------------------------//
	void		AddValue					( const MOAIAttrOp& attrOp );
	void		Bind						();
	void		BindPenColor				( float r, float g, float b, float a );
	void		BindPipelineTransforms		( const ZLMatrix4x4& world, const ZLMatrix4x4& view, const ZLMatrix4x4& proj );
	void		Clear						();
	void		GetValue					( MOAIAttrOp& attrOp );
	void        SetAttrFlags                ( MOAIAttrOp& attrOp );
    void		SetBuffer					( void* buffer, size_t size );
	void		SetType						( u32 type );
	void		SetValue					( float value );
	void		SetValue					( int value );
	void		SetValue					( const MOAIAttrOp& attrOp );
	void		SetValue					( const ZLColorVec& value );
	void		SetValue					( const ZLAffine3D& value );
	void		SetValue					( const ZLMatrix4x4& value );

public:

	//----------------------------------------------------------------//
	enum {
		UNIFORM_NONE,
		UNIFORM_COLOR,
		UNIFORM_FLOAT,
		UNIFORM_INT,
		UNIFORM_PEN_COLOR,
		UNIFORM_SAMPLER,
		UNIFORM_TRANSFORM,
		UNIFORM_VIEW_PROJ,
		UNIFORM_WORLD,
		UNIFORM_WORLD_VIEW_PROJ,
		UNIFORM_WORLD_VIEW,
	};

				MOAIShaderUniform			();
				~MOAIShaderUniform			();
};

//================================================================//
// MOAIShader
//================================================================//
/**	@name	MOAIShader
	@text	Programmable shader class.
	
	@const	UNIFORM_COLOR
	@const	UNIFORM_FLOAT
	@const	UNIFORM_INT
	@const	UNIFORM_PEN_COLOR
	@const	UNIFORM_SAMPLER
	@const	UNIFORM_TRANSFORM
	@const	UNIFORM_VIEW_PROJ
	@const	UNIFORM_WORLD
	@const	UNIFORM_WORLD_VIEW
	@const	UNIFORM_WORLD_VIEW_PROJ
*/
class MOAIShader :
	public virtual MOAINode,
	public MOAIGfxResource {
protected:
	
	STLString		mVertexShaderSource;
	STLString		mFragmentShaderSource;
	
	u32				mProgram;
	u32				mVertexShader;
	u32				mFragmentShader;
	
	typedef STLMap < u32, STLString >::iterator AttributeMapIt;
	STLMap < u32, STLString > mAttributeMap;
	
	ZLLeanArray < MOAIShaderUniform > mUniforms;
	
	//----------------------------------------------------------------//
	static int		_clearUniform			( lua_State* L );
	static int		_declareUniform			( lua_State* L );
	static int		_declareUniformFloat	( lua_State* L );
	static int		_declareUniformInt		( lua_State* L );
	static int		_declareUniformSampler	( lua_State* L );
	static int		_load					( lua_State* L );
	static int		_reserveUniforms		( lua_State* L );
	static int		_setVertexAttribute		( lua_State* L );
	
	//----------------------------------------------------------------//
	u32				CompileShader				( u32 type, cc8* source );
	bool			IsRenewable					();
	void			PrintProgramLog				( u32 program );
	void			PrintShaderLog				( u32 shader );
	void			OnBind						();
	void			OnClear						();
	void			OnCreate					();
	void			OnDestroy					();
	void			OnInvalidate				();
	void			OnLoad						();
	void			UpdatePenColor				( float r, float g, float b, float a );
	void			UpdatePipelineTransforms	( const ZLMatrix4x4& world, const ZLMatrix4x4& view, const ZLMatrix4x4& proj );
	bool			Validate					();

public:
	
	DECL_LUA_FACTORY ( MOAIShader )
	
	friend class MOAIGfxDevice;
	
	//----------------------------------------------------------------//
	bool			ApplyAttrOp				( u32 attrID, MOAIAttrOp& attrOp, u32 op );
	void			BindUniforms			();
	void			ClearUniform			( u32 idx );
	void			ClearUniforms			();
	void			DeleteShaders			();
	void			DeclareUniform			( u32 idx, cc8* name, u32 type );
	void			DeclareUniform			( u32 idx, cc8* name, u32 type, float value );
	void			DeclareUniform			( u32 idx, cc8* name, u32 type, int value );
	bool			IsValid					();
	bool			LoadGfxState			();
					MOAIShader				();
					~MOAIShader				();
	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
	void			ReserveAttributes		( u32 nAttributes );
	void			ReserveUniforms			( u32 nUniforms );
	void			SetSource				( cc8* vshSource, cc8* fshSource );
	void			SetVertexAttribute		( u32 idx, cc8* attribute );
};

#endif
