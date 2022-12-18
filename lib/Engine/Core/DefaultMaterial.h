#pragma once
#include"Material.h"
#include"TextureManager.h"
#include"AliceMathUtility.h"

class DefaultMaterial
{
public:

	//�f�t�H���g�̃e�N�X�`��(���F)�����ς��Ȃ�����
	TextureData* DEFAULT_TEXTURE;

	//�f�t�H���g�̃}�e���A�������ς��Ȃ�����
	 std::unique_ptr<Material> DEFAULT_TEXTURE_MATERIAL;

	//�f�t�H���g�̃����o�[�g�}�e���A�������ς��Ȃ�����
	 std::unique_ptr<Material> DEFAULT_LAMBERT_MATERIAL;

	//�f�t�H���g�̃t�H���O�}�e���A�������ς��Ȃ�����
	 std::unique_ptr<Material> DEFAULT_PHONG_MATERIAL;

	//�f�t�H���g�̃p�[�e�B�N���}�e���A�������ς��Ȃ�����
	 std::unique_ptr<Material> DEFAULT_PARTICLE_MATERIAL;

	//�f�t�H���g�̉J�p�[�e�B�N���}�e���A�������ς��Ȃ�����
	 std::unique_ptr<Material> DEFAULT_RAIN_PARTICLE_MATERIAL;

	//�f�t�H���g�̃X�v���C�g2D�}�e���A�������ς��Ȃ�����
	 std::array<std::unique_ptr<Material>, static_cast<size_t>(BlendMode::AX_BLENDMODE_MAX)> DEFAULT_SPRITE2D_MATERIAL;

	//�f�t�H���g�̃X�v���C�g3D�}�e���A�������ς��Ȃ�����
	 std::array<std::unique_ptr<Material>, static_cast<size_t>(BlendMode::AX_BLENDMODE_MAX)> DEFAULT_SPRITE3D_MATERIAL;

	//�f�t�H���g��FBX�}�e���A�������ς��Ȃ�����
	 std::unique_ptr<Material> DEFAULT_FBX_MATERIAL;

	//�f�t�H���g�̃|�X�g�G�t�F�N�g�}�e���A�������ς��Ȃ�����
	 std::unique_ptr<Material> DEFAULT_POST_EFFECT_MATERIAL;

	//�f�t�H���g�̃X���b�V���}�e���A�������ς��Ȃ�����
	 std::array<std::unique_ptr<Material>, static_cast<size_t>(BlendMode::AX_BLENDMODE_MAX)> DEFAULT_MESH_MATERIAL;
	 std::array<std::unique_ptr<Material>, static_cast<size_t>(BlendMode::AX_BLENDMODE_MAX)> DEFAULT_LINE_MATERIAL;

	 void Initialize();

	 static DefaultMaterial* GetDefaultMaterial();

private:

	DefaultMaterial() = default;
	~DefaultMaterial() = default;

	 void CreateDefaultTexture();

	 void CreateDefaultTextureMaterial();

	 void CreateDefaultLambertMaterial();

	 void CreateDefaultPhongMaterial();

	 void CreateDefaultSprite2DMaterial();

	 void CreateDefaultSprite3DMaterial();

	 void CreateDefaultFbxMaterial();

	 void CreateDefaultParticleMaterial();

	 void CreateDefaultMeshMaterial();

	 void CreateDefaultRainParticleMaterial();

	 void CreateDefaultPostEffectMaterial();

	 Material* CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE type, BlendMode mode, Shader* vex, Shader* pix);

	 Material* CreateDefaultSprite2DBlend(BlendMode mode, Shader* vex, Shader* pix);

	 Material* CreateDefaultSprite3DBlend(BlendMode mode, Shader* vex, Shader* pix);

	 D3D12_BLEND_DESC CreateBlend(BlendMode mode);

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	 DefaultMaterial& operator=(const DefaultMaterial&) = delete;
	 DefaultMaterial(const DefaultMaterial&) = delete;
};
