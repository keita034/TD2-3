#pragma once
#include"ErrorException.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"Transform.h"
#include"Camera.h"
#include"Material.h"

enum BillboardFlag
{
	NonBillboard,//�r���{�[�h�����Ȃ�
	AllBillboard,//���ׂđł�����
	XBillboard,//X����ł�����
	YBillboard,//Y����ł�����
	XYBillboard//Z����ł�����
};

class Sprite2D;
class Sprite3D;

class Sprite
{
protected:
	HRESULT result = S_OK;
	char PADDING[4]={};
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList> cmdList = nullptr;

	//���_�o�b�t�@
	std::unique_ptr<VertexBuffer> vertexBuffer;

	//�C���f�b�N�X�o�b�t�@
	std::unique_ptr<IndexBuffer> indexBuffer;

	//�v���W�F�N�V�����s��
	AliceMathF::Matrix4 matProjection;

	Material* spriteMaterial = nullptr ;

	bool InitializeFlag = true;
	char PADDING2[3]={};

	AliceMathF::Vector2 anchorPoint = { 0.5f, 0.5f };
	char PADDING3[4]={};

	TextureData* texture;

	//�e�N�X�`���؂���͈�{����X,����Y,�E��X,�E��Y}
	AliceMathF::Vector4 trimmingRange = { 0.0f,0.0f,1.0f,1.0f };
	// ���E���]
	bool flipX = false;
	// �㉺���]
	bool flipY = false;
	char PADDING4[6]={};

	AliceMathF::Vector2 spriteSize;

public:

	Sprite()= default;
	virtual ~Sprite() = default;

	//������
	virtual void Initialize(uint32_t handle) = 0;

	//�`��
	virtual void Draw(Transform& transform, BlendMode blend, Material* material)=0;

	//�A�j���[�V�����`��
	virtual void AnimationDraw(Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, BlendMode blend, Material* material) = 0;

	/// <summary>
	/// �A���J�[�|�C���g�̈ʒu�ύX
	/// </summary>
	/// <param name="point">X,Y���W(0.0~1.0)�����l��0.5</param>
	virtual void SetAnchorPoint(const AliceMathF::Vector2& point);

	/// <summary>
	/// �摜�𔽓]���邩
	/// </summary>
	/// <param name="isFlipX">���E���]</param>
	/// <param name="isFlipY">�㉺���]</param>
	virtual void SetFlipFlag(bool isFlipX = false, bool isFlipY = false);

	/// <summary>
	/// �J���[��ݒ�
	/// </summary>
	/// <param name="color">RGBA</param>
	virtual void SetColor(const AliceMathF::Vector4& color);

	/// <summary>
	/// �摜�̐؂���͈͂��w��
	/// </summary>
	/// <param name="leftTop">������W �����l��(0,0)</param>
	/// <param name="rightDown">�E�����W �����l�͉摜�̑傫��</param>
	virtual void SetTextureTrimmingRange(const AliceMathF::Vector2& leftTop, const AliceMathF::Vector2& rightDown);

	/// <summary>
	/// �e�N�X�`����ݒ�
	/// </summary>
	/// <param name="handle">�e�N�X�`���n���h��</param>
	virtual void SetTex(uint32_t handle);

	virtual void SetSize(const AliceMathF::Vector2& size);


	/// <summary>
	/// 2D�X�v���C�g�𐶐�
	/// </summary>
	/// <param name="handle">�e�N�X�`���n���h��</param>
	static Sprite2D* Create2DSprite(uint32_t handle);

	/// <summary>
	/// 3D�X�v���C�g�𐶐�
	/// </summary>
	/// <param name="handle">�e�N�X�`���n���h��</param>
	static Sprite3D* Create3DSprite(uint32_t handle);

protected:

	//������
	virtual void SpriteInitialize();

	//�`��
	virtual void SpriteDraw(Transform& transform, Material* material);


	//���_�o�b�t�@�E�C���f�b�N�X����
	virtual void CreatVertexIndexBuffer();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Sprite& operator=(const Sprite&) = delete;
	Sprite(const Sprite&) = delete;
};